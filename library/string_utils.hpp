#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include "my_def.hpp"

struct KMP{
    int m;
    string p;
    vector<int> fail;
    knuth_morris_pratt(string p) : p(p), m(p.size()) {
        fail.resize(m+1, -1);
        for (int i = 1, j = -1; i <= m; ++i) {
            while (j >= 0 && p[j] != p[i-1]) j = fail[j];
            fail[i] = ++j;
        }
    }
    vector<int> match(string s) {
        int n = strlen(s);
        vector<int> occur;
        for (int i = 0, k = 0; i < n; ++i) {
            while (k >= 0 && s[i] != p[k]) k = fail[k];
            if (++k == m) {
                /* match at s[i-m+1 ... i] */
                occur.push_back(i-m+1);
            }
        }
        return occur;
    }
};

#endif
