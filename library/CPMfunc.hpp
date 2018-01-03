#ifndef CPM_FUNC_HPP
#define CPM_FUNC_HPP

#include "my_def.hpp"

namespace CPM {
    // Returns largest power of p that divides n!
    int largestPower(int n, int p) {
        // Initialize result
        int x = 0;
        // Calculate x = n/p + n/(p^2) + n/(p^3) + ....
        while (n) {
            n /= p;
            x += n;
        }
        return x;
    }

    ll phi(ll n) {
        ll result = n;
        for (ll p = 2; p * p <= n; ++p) {
            if (n % p == 0) {
                while (n % p == 0) n /= p;
                result -= result / p;
            }
        }
        if (n > 1)
            result -= result / n;
        return result;
    }

    namespace prv {
        ll ncrp(ll n, ll r, ll p) {
            ll C[r + 1];
            memset(C, 0, sizeof(C));
            C[0] = 1;
            for (ll i = 1; i <= n; i++) {
                for (ll j = min(i, r); j > 0; j--)
                    C[j] = (C[j] + C[j - 1]) % p;
            }
            return C[r];
        }
    }

    ll ncrModp(ll n, ll r, ll p) {
        if (r == 0) return 1;
        int ni = n % p, ri = r % p;
        return (ncrModp(n / p, r / p, p) * prv::ncrp(ni, ri, p)) % p;
    }
}
#endif
