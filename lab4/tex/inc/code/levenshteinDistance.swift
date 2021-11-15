func memoize<T1: Hashable, T2: Hashable, U>(_ body: @escaping (@escaping (T1, T2) -> U) -> (T1, T2) -> U) -> ((T1, T2) -> U) {
    var memo = [T1: [T2: U]]()
    var result: ((T1, T2) -> U)!
    result = { value1, value2 in
        if let cached = memo[value1]?[value2] { return cached }
        let toCache = body(result)(value1, value2)
        memo[value1, default: [:]][value2] = toCache
        return toCache
    }
    return result
}

func __levenshteinDistance(_ step: @escaping(Substring, Substring) -> Int) -> (Substring, Substring) -> Int {
    return { s1, s2 in
        if s1.isEmpty { return s2.count }
        if s2.isEmpty { return s1.count }
        
        // drop first letter of each string
        let s1Crop = s1.dropFirst()
        let s2Crop = s2.dropFirst()
        
        // if first characters are equal, continue with both cropped
        if s1.first == s2.first {
            return step(s1Crop, s2Crop)
        }
        
        // otherwise find smallest of the three options
        let (c1, c2, c3) = (step(s1Crop, s2), step(s1, s2Crop), step(s1Crop, s2Crop))
        return 1 + min(c1, c2, c3)
    }
}

let _levenshteinDistance = memoize(__levenshteinDistance)

extension StringProtocol where Self.SubSequence == Substring {
    func levenshteinDistance<S>(from other: S) -> Int
        where S: StringProtocol, S.SubSequence == Substring
    {
        return _levenshteinDistance(self[...], other[...])
    }
}
