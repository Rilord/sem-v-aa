//
// Created by kodor on 10/23/21.
//

#include "matrix.h"

std::ostream &operator<<(std::ostream &os, const matrix &mat) {
    pprint::PrettyPrinter printer(os);
    printer.print("Matrix [");
    printer.indent(2);
    printer.print_inline(mat.mat);
    printer.print("}");
    return os;
}
