#ifndef MINISCRIPT_WORD_H
#define MINISCRIPT_WORD_H

namespace ms {

    enum class Word {
        UNKNOWN,
        EndOfFile,

        Identifier,
        String,
        Number,

        Function,
        Continue,
        Return,
        While,
        Break,
        False,
        True,
        Null,
        Let,
        For,
        Do,
        In,

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

        NotAssign,
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

}

#endif //MINISCRIPT_WORD_H