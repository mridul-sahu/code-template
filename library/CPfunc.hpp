#ifndef CP_FUNC_HPP
#define CP_FUNC_HPP

#include "my_def.hpp"

namespace CP {
    const ll INF = numeric_limits<ll>::max();

    ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

    ll modPow(ll x, ll y, ll p) {
        ll res = 1 % p;
        x = x % p;
        while (y > 0) {
            if (y & 1)
                res = (res * x) % p;
            y = y / 2;
            x = (x * x) % p;
        }
        return res;
    }

    ll modInverse(ll a, ll b) {
        ll b0 = b, t, q;
        a %= b;
        if (a == 0) return 1;
        ll M = b;
        ll x0 = 0, x1 = 1;
        if (b == 1) return 0;
        while (a > 1) {
            q = a / b;
            t = b;
            b = a % b;
            a = t;
            t = x0;
            x0 = x1 - q * x0;
            x1 = t;
        }
        if (x1 < 0) x1 += b0;
        return x1 % M;
    }

    double quad_eqn(double a, double b, double c) { // assuming a != 0
        double D = b * b - 4 * a * c, x1, x2;
        if (b > 0) x1 = (-b - sqrt(D)) / (2 * a);
        else x1 = (-b + sqrt(D)) / (2 * a);
        x2 = c / (a * x1);
        return max(x1, x2);
    }
    //Dependency : Segment Tree!
    ll round2(ll v) { // 64 bits
        --v;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v |= v >> 32;
        ++v;
        return v;
    }
}
#endif
