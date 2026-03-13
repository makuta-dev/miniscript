#ifndef MINISCRIPT_PRINTER_H
#define MINISCRIPT_PRINTER_H

#include "miniscript/ASTree.h"

namespace ms {

    class Printer final : public IVisitor {
    public:
        void visit(const ProgramNode &) override;
    };

}

#endif //MINISCRIPT_PRINTER_H