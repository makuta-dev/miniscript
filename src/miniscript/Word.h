#ifndef MINISCRIPT_WORD_H
#define MINISCRIPT_WORD_H

#include <string>

namespace ms {

    enum class Word {
        UNKNOWN,
        EndOfFile,

        Identifier,
        String,
        StringInterpolation,
        Number,

        Function,
        Continue,
        Return,
        Const,
        While,
        Match,
        Break,
        False,
        True,
        Else,
        Null,
        Let,
        For,
        Do,
        In,
        If,

        LeftParen,
        RightParen,
        LeftBracket,
        RightBracket,
        LeftBrace,
        RightBrace,

        Assign,
        Comma,
        Colon,
        Dot,

        Range,
        Arrow,

        And,
        Or,

        BitAnd,
        BitOr,
        BitXor,

        Not,
        Inv,

        Plus,
        Minus,
        Multiply,
        Divide,
        Modulus,

        LeftShift,
        RightShift,
        LeftRotate,
        RightRotate,

        BitAndAssign,
        BitOrAssign,
        BitXorAssign,

        InvAssign,

        PlusAssign,
        MinusAssign,
        MultiplyAssign,
        DivideAssign,
        ModulusAssign,

        LeftShiftAssign,
        RightShiftAssign,
        LeftRotateAssign,
        RightRotateAssign,

        Equals,
        NotEquals,
        Greater,
        GreaterEquals,
        Less,
        LessEquals,

        PlusPlus,
        MinusMinus,
    };

    std::string toString(const Word&);

}

#endif //MINISCRIPT_WORD_H