#ifndef FENWICK_TREE_HPP
#define FENWICK_TREE_HPP

#include "my_def.hpp"

struct FenwickTree {
    ll n;
    vector<ll> BT;

    explicit FenwickTree(const vector<ll> &v) {
        n = (ll) v.size();
        BT = vector<ll>(n + 1, 0);
        for (ll i = 0; i < n; ++i) {
            update(i + 1, v[i]);
        }
    }

    void update(ll indx, ll delta) {
        for (; indx <= n; indx += indx & -indx) {
            BT[indx] += delta;
        }
    }

    ll query(ll indx) {
        ll sum = 0;
        for (; indx > 0; indx -= indx & -indx) {
            sum += BT[indx];
        }
        return sum;
    }
};

#endif
