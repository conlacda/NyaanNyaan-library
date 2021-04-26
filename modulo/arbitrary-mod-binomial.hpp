#pragma once

#include <vector>

#include "../atcoder/math.hpp"
#include "../atcoder/modint.hpp"
using namespace std;

#define PRIME_POWER_BINOMIAL_M_MAX ((1LL << 30) - 1)
#define PRIME_POWER_BINOMIAL_N_MAX 20000000

template <typename mint>
struct prime_power_binomial {
  int p, q, M;
  vector<mint> fac, ifac, inv;
  mint delta;

  prime_power_binomial(int _p, int _q) : p(_p), q(_q) {
    assert(p <= PRIME_POWER_BINOMIAL_M_MAX);
    assert(_q > 0);
    long long m = 1;
    while (_q--) {
      m *= p;
      assert(m <= PRIME_POWER_BINOMIAL_M_MAX);
    }
    M = m;
    mint::set_mod(M);
    enumerate();
    delta = (p == 2 && q >= 3) ? 1 : M - 1;
  }

  void enumerate() {
    int MX = min<int>(M, PRIME_POWER_BINOMIAL_N_MAX + 10);
    fac.resize(MX);
    ifac.resize(MX);
    inv.resize(MX);
    fac[0] = ifac[0] = inv[0] = 1;
    fac[1] = ifac[1] = inv[1] = 1;
    for (int i = 2; i < MX; i++) {
      if (i % p == 0) {
        fac[i] = fac[i - 1];
        fac[i + 1] = fac[i - 1] * (i + 1);
        i++;
      } else {
        fac[i] = fac[i - 1] * i;
      }
    }
    ifac[MX - 1] = fac[MX - 1].inv();
    for (int i = MX - 2; i > 1; --i) {
      if (i % p == 0) {
        ifac[i] = ifac[i + 1] * (i + 1);
        ifac[i - 1] = ifac[i];
        i--;
      } else {
        ifac[i] = ifac[i + 1] * (i + 1);
      }
    }
  }

  long long Lucas(long long n, long long m) {
    mint res = 1;
    while (n) {
      int n0 = n % p, m0 = m % p;
      n /= p, m /= p;
      if (n0 < m0) return 0;
      res *= fac[n0] * ifac[m0] * ifac[n0 - m0];
    }
    return res.val();
  }

  long long C(long long n, long long m) {
    if (n < m || n < 0 || m < 0) return 0;
    if (mint::mod() != M) mint::set_mod(M);
    if (q == 1) return Lucas(n, m);
    long long r = n - m;
    int e0 = 0, eq = 0, i = 0;
    mint res = 1;
    while (n) {
      res *= fac[n % M];
      res *= ifac[m % M];
      res *= ifac[r % M];
      n /= p, m /= p, r /= p;
      int eps = n - m - r;
      e0 += eps;
      if (e0 >= q) return 0;
      if (++i >= q) eq += eps;
    }
    res *= delta.pow(eq) * mint(p).pow(e0);
    return res.val();
  }
};

// constraints:
// (M <= 1e7 and max(N) <= 1e18) or (M < 2^30 and max(N) <= 2e7)
struct arbitrary_mod_binomial {
  using mint = atcoder::dynamic_modint<1333>;

  int mod;
  vector<int> M;
  vector<prime_power_binomial<mint>> cs;

  arbitrary_mod_binomial(long long md) : mod(md) {
    assert(1 <= md);
    assert(md <= PRIME_POWER_BINOMIAL_M_MAX);
    for (int i = 2; i * i <= md; i++) {
      if (md % i == 0) {
        int j = 0, k = 1;
        while (md % i == 0) md /= i, j++, k *= i;
        M.push_back(k);
        cs.emplace_back(i, j);
        assert(M.back() == cs.back().M);
      }
    }
    if (md != 1) {
      M.push_back(md);
      cs.emplace_back(md, 1);
    }
    assert(M.size() == cs.size());
  }

  long long C(long long n, long long m) {
    if (mod == 1) return 0;
    vector<long long> rem, d;
    for (int i = 0; i < (int)cs.size(); i++) {
      rem.push_back(cs[i].C(n, m));
      d.push_back(M[i]);
    }
    return atcoder::crt(rem, d).first;
  }
};

#undef PRIME_POWER_BINOMIAL_M_MAX
#undef PRIME_POWER_BINOMIAL_N_MAX

/**
 * @brief 任意mod二項係数
 * @docs docs/modulo/arbitrary-mod-binomial.md
 */