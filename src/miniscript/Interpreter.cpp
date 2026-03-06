#include "miniscript/Interpreter.h"

#include <iostream>

namespace miniscript {

    void debug(const std::string& s) {
        std::cout << "[debug] " << s << std::endl;
    }

    struct ReturnSignal : std::exception {
        ValuePtr value;

        explicit ReturnSignal(ValuePtr val) : value(std::move(val)) {}

        [[nodiscard]] const char* what() const noexcept override {
            return "ReturnSignal: This exception should be caught by a CallNode.";
        }
    };

    void Interpreter::visit(const LiteralNode& l) {
        debug("literal");
        switch (l.token.word) {
            case Word::Identifier:
                m_lastValue = m_scope->get(l.token.value);
                break;
            case Word::String:
                m_lastValue = std::make_shared<StrValue>(l.token.value);
                break;
            case Word::True:
                m_lastValue = std::make_shared<BoolValue>(true);
                break;
            case Word::False:
                m_lastValue = std::make_shared<BoolValue>(false);
                break;
            case Word::Character:
                m_lastValue = std::make_shared<CharValue>(l.token.value[0]);
                break;
            case Word::Number:
                if (l.token.value.contains('.')) {
                    m_lastValue = std::make_shared<RealValue>(std::stod(l.token.value));
                }else {
                    m_lastValue = std::make_shared<IntValue>(std::stoi(l.token.value));
                }
                break;
            case Word::Null:
                m_lastValue = NullValue::instance();
                break;
            default:
                break;
        }
    }

    void Interpreter::visit(const ArrayLiteralNode& a) {
        debug("array literal");
        std::vector<ValuePtr> evaluatedArgs;
        for (const auto& arg : a.items) {
            arg->accept(*this);
            evaluatedArgs.push_back(m_lastValue);
        }
        m_lastValue = std::make_shared<ArrValue>(evaluatedArgs);
    }

    void Interpreter::visit(const DictLiteralNode& d) {
        debug("dict literal");
        DictValue::DictType evaluatedArgs;
        for (const auto& [k, v] : d.pairs) {
            k->accept(*this);
            const auto key = m_lastValue;
            v->accept(*this);
            evaluatedArgs.emplace(key,m_lastValue);
        }
        m_lastValue = std::make_shared<DictValue>(evaluatedArgs);
    }

    void Interpreter::visit(const ArgumentNode &) {

    }

    void Interpreter::visit(const FunctionNode& f) {
        debug("func");
        m_scope->put(f.name, std::make_shared<UFuncValue>(&f,m_scope));
    }

    void Interpreter::visit(const VariableNode& v) {
        v.value->accept(*this);
        m_scope->put(v.name,m_lastValue);
    }

    void Interpreter::visit(const BinaryNode &) {

    }

    void Interpreter::visit(const UnaryNode &) {

    }

    void Interpreter::visit(const CallNode& c) {
        debug("call");
        c.name->accept(*this);
        const ValuePtr callee = m_lastValue;

        if (!callee) {
            throw std::runtime_error("Runtime Error: Attempted to call a null value.");
        }

        std::vector<ValuePtr> evaluatedArgs;
        for (const auto& arg : c.arguments) {
            arg->accept(*this);
            evaluatedArgs.push_back(m_lastValue);
        }

        if (callee->getType() == ValueType::NativeFunc) {
            const auto native = dynamic_cast<FuncValue*>(callee.get());
            m_lastValue = native->getValue()(evaluatedArgs);
            return;
        }

        if (callee->getType() == ValueType::Func) {
            const auto funcValue = dynamic_cast<UFuncValue*>(callee.get());
            const auto& fnAST = funcValue->getValue();

            if (evaluatedArgs.size() < fnAST->arguments.size()) {
                throw std::runtime_error("Runtime Error: Too few arguments for function " + fnAST->name);
            }

            const auto callScope = std::make_shared<Scope>(funcValue->getDefinitionScope());

            for (size_t i = 0; i < fnAST->arguments.size(); ++i) {
                auto argName = dynamic_cast<ArgumentNode*>(fnAST->arguments[i].get())->name;
                callScope->put(argName, evaluatedArgs[i]);
            }

            const auto previousScope = m_scope;
            m_scope = callScope;

            try {
                fnAST->body->accept(*this);
                m_lastValue = std::make_shared<NullValue>();
            } catch (const ReturnSignal& signal) {
                m_lastValue = signal.value;
            }

            m_scope = previousScope;
        } else {
            throw std::runtime_error("Runtime Error: Object is not callable.");
        }
    }

    void Interpreter::visit(const WhileNode &) {

    }

    void Interpreter::visit(const ForNode &) {

    }

    void Interpreter::visit(const AssignNode &) {

    }

    void Interpreter::visit(const ReturnNode& r) {
        ValuePtr result;

        if (r.variable) {
            r.variable->accept(*this);
            result = m_lastValue;
        } else {
            result = std::make_shared<NullValue>();
        }

        throw ReturnSignal{ result };
    }

    void Interpreter::visit(const BreakNode &) {

    }

    void Interpreter::visit(const ContinueNode &) {

    }

    void Interpreter::visit(const IndexNode &) {

    }

    void Interpreter::visit(const BlockNode& b) {
        debug("block");
        auto previousScope = m_scope;
        m_scope = std::make_shared<Scope>(previousScope);

        try {
            for (const auto& item : b.statements) {
                item->accept(*this);
            }
        } catch (...) {
            m_scope = previousScope;
            return;
        }

        m_scope = previousScope;
    }

    void Interpreter::visit(const ImportNode &) {

    }

    void Interpreter::visit(const IfNode&) {

    }

    ValuePtr Interpreter::evaluate(ASTNode* node) {
        if (!node) return NullValue::instance();
        node->accept(*this);
        return m_lastValue;
    }

}
