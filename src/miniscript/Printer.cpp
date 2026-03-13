#include "Printer.h"

#include <print>

namespace ms {

    void Printer::visit(const ProgramNode &) {
        std::println("Program:");
    }

}
