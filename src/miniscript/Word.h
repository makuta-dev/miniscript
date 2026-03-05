#ifndef MINISCRIPT_WORD_H
#define MINISCRIPT_WORD_H

#include <string>

namespace miniscript {

    enum class Word {
        // --- System / Meta ---
        UNKNOWN,
        EndOfFile,

        // --- Keywords ---
        Func,           // func
        Let,            // let
        Ret,            // ret
        If,             // if
        Else,           // else
        While,          // while
        For,            // for
        Break,          // break
        Continue,       // continue
        Import,         // import
        True,           // true
        False,          // false
        Null,           // null

        // --- Literals & Identifiers ---
        Identifier,     // e.g., myVariable
        String,         // "text"
        Number,         // 123, 3.14
        Character,      // 'c'

        // --- Delimiters & Separators ---
        LeftParen,      // (
        RightParen,     // )
        LeftBracket,    // [
        RightBracket,   // ]
        LeftBrace,      // {
        RightBrace,     // }
        Comma,          // ,
        Colon,          // :
        Dot,            // .
        Semicolon,      // ;

        // --- Basic Arithmetic ---
        Plus,           // +
        Minus,          // -
        Asterisk,       // *
        Slash,          // /
        Percent,        // %

        // --- Unary / Increment / Decrement ---
        PlusPlus,       // ++
        MinusMinus,     // --
        Bang,           // !

        // --- Comparison ---
        Assign,         // =
        Equal,          // ==
        NotEqual,       // !=
        Less,           // <
        More,           // >
        LessEqual,      // <=
        MoreEqual,      // >=

        // --- Logical (Boolean) ---
        And,            // &&
        Or,             // ||

        // --- Bitwise & Rotation ---
        BitAnd,         // &
        BitOr,          // |
        BitXor,         // ^
        BitNot,         // ~
        LeftShift,      // <<
        RightShift,     // >>
        RotateLeft,     // <<<
        RotateRight,    // >>>

        // --- Compound Assignment ---
        PlusAssign,     // +=
        MinusAssign,    // -=
        AsteriskAssign, // *=
        SlashAssign,    // /=
        PercentAssign,  // %=
        AndAssign,      // &=
        OrAssign,       // |=
        XorAssign,      // ^=
        LShiftAssign,   // <<=
        RShiftAssign,   // >>=
        RotLAssign,     // <<<=
        RotRAssign,     // >>>=

        // --- Special Syntax ---
        Arrow,              // ->
        InterpolationStart, // Found inside string: " ... {
        InterpolationEnd,   // Found inside string: } ... "
    };

    std::string to_string(Word w);

}

#endif //MINISCRIPT_WORD_H