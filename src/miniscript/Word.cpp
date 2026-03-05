#include "miniscript/Word.h"

namespace miniscript {

    std::string to_string(Word w) {
        switch (w) {
            // --- System ---
            case Word::UNKNOWN:            return "UNKNOWN";
            case Word::EndOfFile:          return "EOF";

                // --- Keywords ---
            case Word::Func:               return "func";
            case Word::Let:                return "let";
            case Word::Ret:                return "ret";
            case Word::If:                 return "if";
            case Word::Else:               return "else";
            case Word::While:              return "while";
            case Word::For:                return "for";
            case Word::Break:              return "break";
            case Word::Continue:           return "continue";
            case Word::Import:             return "import";
            case Word::True:               return "true";
            case Word::False:              return "false";
            case Word::Null:               return "null";

                // --- Literals ---
            case Word::Identifier:         return "IDENTIFIER";
            case Word::String:             return "STRING";
            case Word::Number:             return "NUMBER";
            case Word::Character:          return "CHARACTER";

                // --- Delimiters ---
            case Word::LeftParen:          return "(";
            case Word::RightParen:         return ")";
            case Word::LeftBracket:        return "[";
            case Word::RightBracket:       return "]";
            case Word::LeftBrace:          return "{";
            case Word::RightBrace:         return "}";
            case Word::Comma:              return ",";
            case Word::Colon:              return ":";
            case Word::Dot:                return ".";
            case Word::Semicolon:          return ";";

                // --- Operators ---
            case Word::Plus:               return "+";
            case Word::Minus:              return "-";
            case Word::Asterisk:           return "*";
            case Word::Slash:              return "/";
            case Word::Percent:            return "%";
            case Word::PlusPlus:           return "++";
            case Word::MinusMinus:         return "--";
            case Word::Bang:               return "!";

                // --- Comparison ---
            case Word::Assign:             return "=";
            case Word::Equal:              return "==";
            case Word::NotEqual:           return "!=";
            case Word::Less:               return "<";
            case Word::More:               return ">";
            case Word::LessEqual:          return "<=";
            case Word::MoreEqual:          return ">=";

                // --- Logical ---
            case Word::And:                return "&&";
            case Word::Or:                 return "||";

                // --- Bitwise & Rotation ---
            case Word::BitAnd:             return "&";
            case Word::BitOr:              return "|";
            case Word::BitXor:             return "^";
            case Word::BitNot:             return "~";
            case Word::LeftShift:          return "<<";
            case Word::RightShift:         return ">>";
            case Word::RotateLeft:         return "<<<";
            case Word::RotateRight:        return ">>>";

                // --- Compound Assignment ---
            case Word::PlusAssign:         return "+=";
            case Word::MinusAssign:        return "-=";
            case Word::AsteriskAssign:     return "*=";
            case Word::SlashAssign:        return "/=";
            case Word::PercentAssign:      return "%=";
            case Word::AndAssign:          return "&=";
            case Word::OrAssign:           return "|=";
            case Word::XorAssign:          return "^=";
            case Word::LShiftAssign:       return "<<=";
            case Word::RShiftAssign:       return ">>=";
            case Word::RotLAssign:         return "<<<=";
            case Word::RotRAssign:         return ">>>=";

            default: return "INVALID_TOKEN";
        }
    }

}

