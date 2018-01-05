#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include "my_def.hpp"

struct KMP {
    ll m;
    string p;
    vector<ll> fail;

    explicit KMP(string p) : p(p), m((ll) p.size()) {
        fail.resize(m + 1, -1);
        for (ll i = 1, j = -1; i <= m; ++i) {
            while (j >= 0 && p[j] != p[i - 1]) j = fail[j];
            fail[i] = ++j;
        }
    }

    vector<ll> match(string s) {
        ll n = (ll) s.size();
        vector<ll> occur;
        for (ll i = 0, k = 0; i < n; ++i) {
            while (k >= 0 && s[i] != p[k]) k = fail[k];
            if (++k == m) {
                /* match at s[i-m+1 ... i] */
                occur.push_back(i - m + 1);
            }
        }
        return occur;
    }
};

struct Trie {
    int words;
    int prefixes;
    Trie *edges[256];

    Trie() {
        words = 0;
        prefixes = 0;
        for (int i = 0; i < 256; ++i) {
            edges[i] = nullptr;
        }
    }

    void addWord(Trie *root, const string &word) {
        root->prefixes += 1;
        if (word.empty())
            root->words += 1;
        else {
            if (root->edges[word[0]] == nullptr) {
                root->edges[word[0]] = new Trie();
            }
            addWord(root->edges[word[0]], word.substr(1));
        }
    }

    void addWord(const string &word) {
        if (word.empty())
            return;
        else
            addWord(this, word);
    }

    int countWords(const string &word, Trie *root) {
        if (root == nullptr)
            return 0;
        if (word.empty())
            return root->words;
        return countWords(word.substr(1), root->edges[word[0]]);
    }

    int countPrefixes(const string &word, Trie *root) {
        if (root == nullptr)
            return 0;
        if (word.empty())
            return root->prefixes;
        return countPrefixes(word.substr(1), root->edges[word[0]]);
    }

    int countWords(const string &word) {
        return countWords(word, this);
    }

    int countPrefixes(const string &word) {
        return countPrefixes(word, this);
    }
};

#endif
