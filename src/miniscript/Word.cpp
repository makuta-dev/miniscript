#include "Word.h"

namespace ms {

    std::string toString(const Word& w) {
        switch (w) {
            case Word::EndOfFile:           return "EndOfFile";
            case Word::Identifier:          return "Identifier";
            case Word::String:              return "String";
            case Word::Number:              return "Number";
            case Word::Function:            return "Function";
            case Word::Continue:            return "Continue";
            case Word::Return:              return "Return";
            case Word::While:               return "While";
            case Word::Break:               return "Break";
            case Word::False:               return "False";
            case Word::True:                return "True";
            case Word::Null:                return "Null";
            case Word::Let:                 return "Let";
            case Word::For:                 return "For";
            case Word::Do:                  return "Do";
            case Word::In:                  return "In";
            case Word::LeftParen:           return "LeftParen";
            case Word::RightParen:          return "RightParen";
            case Word::LeftBracket:         return "LeftBracket";
            case Word::RightBracket:        return "RightBracket";
            case Word::LeftBrace:           return "LeftBrace";
            case Word::RightBrace:          return "RightBrace";
            case Word::Assign:              return "Assign";
            case Word::Comma:               return "Comma";
            case Word::Colon:               return "Colon";
            case Word::Dot:                 return "Dot";
            case Word::Range:               return "Range";
            case Word::Arrow:               return "Arrow";
            case Word::And:                 return "And";
            case Word::Or:                  return "Or";
            case Word::BitAnd:              return "BitAnd";
            case Word::BitOr:               return "BitOr";
            case Word::BitXor:              return "BitXor";
            case Word::Not:                 return "Not";
            case Word::Inv:                 return "Inv";
            case Word::Plus:                return "Plus";
            case Word::Minus:               return "Minus";
            case Word::Multiply:            return "Multiply";
            case Word::Divide:              return "Divide";
            case Word::Modulus:             return "Modulus";
            case Word::LeftShift:           return "LeftShift";
            case Word::RightShift:          return "RightShift";
            case Word::LeftRotate:          return "LeftRotate";
            case Word::RightRotate:         return "RightRotate";
            case Word::BitAndAssign:        return "BitAndAssign";
            case Word::BitOrAssign:         return "BitOrAssign";
            case Word::BitXorAssign:        return "BitXorAssign";
            case Word::NotAssign:           return "NotAssign";
            case Word::InvAssign:           return "InvAssign";
            case Word::PlusAssign:          return "PlusAssign";
            case Word::MinusAssign:         return "MinusAssign";
            case Word::MultiplyAssign:      return "MultiplyAssign";
            case Word::DivideAssign:        return "DivideAssign";
            case Word::ModulusAssign:       return "ModulusAssign";
            case Word::LeftShiftAssign:     return "LeftShiftAssign";
            case Word::RightShiftAssign:    return "RightShiftAssign";
            case Word::LeftRotateAssign:    return "LeftRotateAssign";
            case Word::RightRotateAssign:   return "RightRotateAssign";
            case Word::Equals:              return "Equals";
            case Word::NotEquals:           return "NotEquals";
            case Word::Greater:             return "Greater";
            case Word::GreaterEquals:       return "GreaterEquals";
            case Word::Less:                return "Less";
            case Word::LessEquals:          return "LessEquals";
            case Word::PlusPlus:            return "PlusPlus";
            case Word::MinusMinus:          return "MinusMinus";
            default:
                return "UNKNOWN";
        }
    }

}