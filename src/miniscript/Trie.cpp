#include "miniscript/Trie.h"

namespace miniscript {

    Trie::Trie() : m_root(std::make_unique<TrieNode>()) {
        insert("(",Word::LeftParen);
        insert(")",Word::RightParen);
        insert("[",Word::LeftBracket);
        insert("]",Word::RightBracket);
        insert("{",Word::LeftBrace);
        insert("}",Word::RightBrace);
        insert(",",Word::Comma);
        insert(":",Word::Colon);
        insert(".",Word::Dot);
        insert("+",Word::Plus);
        insert("-",Word::Minus);
        insert("*",Word::Asterisk);
        insert("/",Word::Slash);
        insert("%",Word::Percent);
        insert("++",Word::PlusPlus);
        insert("--",Word::MinusMinus);
        insert("!",Word::Bang);
        insert("=",Word::Assign);
        insert("==",Word::Equal);
        insert("!=",Word::NotEqual);
        insert("<",Word::Less);
        insert(">",Word::More);
        insert("<=",Word::LessEqual);
        insert(">=",Word::MoreEqual);
        insert("&&",Word::And);
        insert("||",Word::Or);
        insert("&",Word::BitAnd);
        insert("|",Word::BitOr);
        insert("^",Word::BitXor);
        insert("~",Word::BitNot);
        insert("<<",Word::LeftShift);
        insert(">>",Word::RightShift);
        insert("<<<",Word::RotateLeft);
        insert(">>>",Word::RotateRight);
        insert("+=",Word::PlusAssign);
        insert("-=",Word::MinusAssign);
        insert("*=",Word::AsteriskAssign);
        insert("/=",Word::SlashAssign);
        insert("%=",Word::PercentAssign);
        insert("&=",Word::AndAssign);
        insert("|=",Word::OrAssign);
        insert("^=",Word::XorAssign);
        insert("<<=",Word::LShiftAssign);
        insert(">>=",Word::RShiftAssign);
        insert("<<<=",Word::RotLAssign);
        insert(">>>=",Word::RotRAssign);
    }

    void Trie::insert(const std::string_view op, const Word w) const {
        TrieNode* current = m_root.get();
        for (char c : op) {
            if (!current->children.contains(c)) {
                current->children[c] = std::make_unique<TrieNode>();
            }
            current = current->children[c].get();
        }
        current->word = w;
    }

    std::pair<Word, int> Trie::find_longest(const std::string_view remaining) const {
        TrieNode* current = m_root.get();
        auto last_found = Word::UNKNOWN;
        int last_len = 0;
        int current_len = 0;

        for (const auto& c : remaining) {
            if (!current->children.contains(c)) break;
            current = current->children[c].get();
            current_len++;
            if (current->word != Word::UNKNOWN) {
                last_found = current->word;
                last_len = current_len;
            }
        }
        return {last_found, last_len};
    }

}