#ifndef SEGMENT_LAZY_HPP
#define SEGMENT_LAZY_HPP

#include "my_def.hpp"
#include "CPfunc.hpp"

struct SegmentTree {
    ll *seg, *lazy;
    const ll opval = numeric_limits<ll>::max(); //My nemesis
    ll n;

    explicit SegmentTree(const vector<ll> &inp) {
        n = (ll) inp.size() - 1;
        seg = new ll[2 * CP::round2(n + 1) - 1];
        lazy = new ll[2 * CP::round2(n + 1) - 1]();
        construct_tree(inp, 0, n);
    }

    ll combine(ll a, ll b) {
        return min(a, b);  //Operation that we want
    }

    void construct_tree(const vector<ll> &inp, ll low, ll high, ll pos = 0) {
        if (low == high) {
            seg[pos] = inp[low];
            return;
        }
        ll mid = low + (high - low) / 2;
        construct_tree(inp, low, mid, 2 * pos + 1);
        construct_tree(inp, mid + 1, high, 2 * pos + 2);
        seg[pos] = combine(seg[2 * pos + 1], seg[2 * pos + 2]);
    }

    ll range_query(ll qlow, ll qhigh) {
        return range_query(qlow, qhigh, 0, n);
    }

    ll range_query(ll qlow, ll qhigh, ll low, ll high, ll pos = 0) {
        if (low > high)
            return opval;

        if (lazy[pos] != 0) {
            seg[pos] += lazy[pos];
            if (low != high) {
                lazy[2 * pos + 1] += lazy[pos];
                lazy[2 * pos + 2] += lazy[pos];
            }
            lazy[pos] = 0;
        }

        if (qlow <= low && qhigh >= high) { // Total Overlap
            return seg[pos];
        } else if (qhigh < low || qlow > high) { // No Overlap
            return opval;
        }
        ll mid = low + (high - low) / 2;
        return combine(range_query(qlow, qhigh, low, mid, 2 * pos + 1),
                       range_query(qlow, qhigh, mid + 1, high, 2 * pos + 2));
    }

    void update_lazy(ll delta, ll qlow, ll qhigh) {
        update_lazy(delta, qlow, qhigh, 0, n);
    }

    void update_lazy(ll delta, ll qlow, ll qhigh, ll low, ll high, ll pos = 0) {
        if (low > high)
            return;

        if (lazy[pos] != 0) {
            seg[pos] += lazy[pos];
            if (low != high) {
                lazy[2 * pos + 1] += lazy[pos];
                lazy[2 * pos + 2] += lazy[pos];
            }
            lazy[pos] = 0;
        }

        if (qlow > high || qhigh < low)
            return;
        if (qlow <= low && qhigh >= high) {
            seg[pos] += delta;
            if (low != high) {
                lazy[2 * pos + 1] += delta;
                lazy[2 * pos + 2] += delta;
            }
            return;
        }

        ll mid = low + (high - low) / 2;
        update_lazy(delta, qlow, qhigh, low, mid, 2 * pos + 1);
        update_lazy(delta, qlow, qhigh, mid + 1, high, 2 * pos + 2);
        seg[pos] = combine(seg[2 * pos + 1], seg[2 * pos + 2]);
    }
};

#endif
