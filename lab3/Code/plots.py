import numpy as np
import matplotlib.pyplot as plt


array_lengths = [10, 50, 100, 1000, 10000, 100000]

bubble_timestamps = [44.383, 347.821, 13758.153, 629640, 63081037]
heap_timestamps = [128, 568, 5469, 47993, 453011]
radix_timestamps = [2500, 3163, 16008, 140987, 1587590]

ascending_bubble_timestamps = [164, 2135, 7654, 700791, 145235748, 6228532556]
ascending_heap_timestamps = [286, 802, 1126, 8641, 86229, 653278]
ascending_radix_timestamps = [11091, 3064, 3970, 18004, 174965, 1219600]

descending_bubble_timestamps = [163, 2384, 7406, 777547, 76091911, 6125386392]
descending_heap_timestamps = [192, 657, 1056, 8869, 856639, 738298]
descending_radix_timestamps = [2029, 2632, 35692, 18276, 154625, 1874509]


def f(x):
    return x**2*np.exp(-x**2)


fig, ax = plt.subplots()
ax.plot(array_lengths, descending_bubble_timestamps, label='Пузырьковый')
ax.plot(array_lengths, descending_heap_timestamps, label='Пирамидальный')
ax.plot(array_lengths, descending_radix_timestamps, label='Поразрядный')

box = ax.get_position()
ax.set_position([box.x0, box.y0 + box.height * 0.1,
                 box.width, box.height * 0.9])



plt.xlabel("Длина массивов")
plt.ylabel("Время, наносекунд")
ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.05),
          fancybox=True, shadow=True, ncol=5)
plt.show()