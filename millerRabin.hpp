#include <bits/stdc++.h>
using namespace std;

using u128 = unsigned __int128;
using ull = unsigned long long;

// TODO: モンゴメリ剰余乗算を用いて高速化する
template<class T>
T pow_mod(T a, T n, T m) {
    T res = 1 % m;
    a %= m;
    while (n) {
        if (n & 1) res = (u128(res) * a) % m;
        a = (u128(a) * a) % m;
        n >>= 1;
    }
    return res;
}

// Miller-Rabin法(2026-9-18版)
bool miller_rabin(ull n) {
    vector<ull> A;
    if (n < 4759123141LL) {
        A = {2, 7, 61};
    } else {
        A = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    }
    ull s = 0;
    ull t = n - 1;
    while (t % 2 == 0) {
        ++s;
        t >>= 1;
    }
    for (ull a : A) {
        a %= n;
        if (a == 0) continue;

        ull x = pow_mod<ull>(a, t, n);
        if (x != 1) {
            ull i;
            for (i = 0; i < s; ++i) {
                if (x == n - 1) break;
                x = (u128(x) * x) % n;
            }
            if (i == s) return false;
        }
    }
    return true;
}
