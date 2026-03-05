#ifndef MINISCRIPT_TRIE_H
#define MINISCRIPT_TRIE_H

#include <memory>
#include <unordered_map>

#include "Word.h"

namespace miniscript {

    struct TrieNode final {
        Word word = Word::UNKNOWN;
        std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    };

    class Trie final {
    public:
        Trie();

        void insert(std::string_view op, Word w) const;
        [[nodiscard]] std::pair<Word, int> find_longest(std::string_view remaining) const;

    private:
        std::unique_ptr<TrieNode> m_root;
    };

}

#endif //MINISCRIPT_TRIE_H