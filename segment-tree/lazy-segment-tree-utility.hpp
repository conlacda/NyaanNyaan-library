#pragma once

template <typename T, typename E, T (*f)(T, T), T (*g)(T, E), E (*h)(E, E),
          T (*ti)(), E (*ei)()>
struct LazySegmentTree {
  int n, log;
  vector<T> val;
  vector<E> laz;

  explicit LazySegmentTree() {}
  explicit LazySegmentTree(const vector<T>& vc) { init(vc); }

  void init(const vector<T>& vc) {
    n = 1, log = 0;
    while (n < (int)vc.size()) n <<= 1, log++;
    val.resize(2 * n, ti());
    laz.resize(n, ei());
    for (int i = 0; i < (int)vc.size(); ++i) val[i + n] = vc[i];
    for (int i = n - 1; i; --i) _update(i);
  }

  void update(int l, int r, const E& x) {
    if (l == r) return;
    l += n, r += n;
    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) _push(l >> i);
      if (((r >> i) << i) != r) _push((r - 1) >> i);
    }
    {
      int l2 = l, r2 = r;
      while (l < r) {
        if (l & 1) _apply(l++, x);
        if (r & 1) _apply(--r, x);
        l >>= 1;
        r >>= 1;
      }
      l = l2;
      r = r2;
    }
    for (int i = 1; i <= log; i++) {
      if (((l >> i) << i) != l) _update(l >> i);
      if (((r >> i) << i) != r) _update((r - 1) >> i);
    }
  }

  T query(int l, int r) {
    if (l == r) return ti();
    l += n, r += n;
    T L = ti(), R = ti();
    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) _push(l >> i);
      if (((r >> i) << i) != r) _push((r - 1) >> i);
    }
    while (l < r) {
      if (l & 1) L = f(L, val[l++]);
      if (r & 1) R = f(val[--r], R);
      l >>= 1;
      r >>= 1;
    }
    return f(L, R);
  }

  void set_val(int k, const T& x) {
    k += n;
    for (int i = log; i >= 1; i--) {
      if (((k >> i) << i) != k) _push(k >> i);
    }
    val[k] = x;
    for (int i = 1; i <= log; i++) {
      if (((k >> i) << i) != k) _update(k >> i);
    }
  }

  void update_val(int k, const E& x) {
    k += n;
    for (int i = log; i >= 1; i--) {
      if (((k >> i) << i) != k) _push(k >> i);
    }
    val[k] = g(val[k], x);
    for (int i = 1; i <= log; i++) {
      if (((k >> i) << i) != k) _update(k >> i);
    }
  }

  T get_val(int k) {
    k += n;
    for (int i = log; i >= 1; i--) {
      if (((k >> i) << i) != k) _push(k >> i);
    }
    return val[k];
  }

 private:
  void _push(int i) {
    if (laz[i] != ei()) {
      val[2 * i + 0] = g(val[2 * i + 0], laz[i]);
      val[2 * i + 1] = g(val[2 * i + 1], laz[i]);
      if (2 * i < n) {
        laz[2 * i + 0] = h(laz[i], laz[2 * i + 0]);
        laz[2 * i + 1] = h(laz[i], laz[2 * i + 1]);
      }
      laz[i] = ei();
    }
  }
  void _update(int i) { val[i] = f(val[2 * i + 0], val[2 * i + 1]); }
  void _apply(int i, const E& x) {
    if (x != ei()) {
      val[i] = g(val[i], x);
      if (i < n) laz[i] = h(laz[i], x);
    }
  }
};

namespace SegmentTreeUtil {

template <typename T>
struct Pair {
  T first, second;
  Pair() = default;
  Pair(const T& f, const T& s) : first(f), second(s) {}
  operator T() const { return first; }
};

template <typename T>
T Max(T a, T b) {
  return max(a, b);
}
template <typename T>
T Min(T a, T b) {
  return min(a, b);
}
template <typename T>
T Update(T, T b) {
  return b;
}
template <typename T>
T Add(T a, T b) {
  return a + b;
}
template <typename T>
Pair<T> Psum(Pair<T> a, Pair<T> b) {
  return Pair<T>(a.first + b.first, a.second + b.second);
}
template <typename T>
Pair<T> Padd(Pair<T> a, T b) {
  return Pair<T>(a.first + a.second * b, a.second);
}
template <typename T>
Pair<T> Pid() {
  return Pair<T>(0, 0);
}
template <typename T>
T Zero() {
  return T(0);
}
template <typename T, T val>
T Const() {
  return val;
}

template <typename T, T MINF>
struct AddMax_LazySegmentTree
    : LazySegmentTree<T, T, Max<T>, Add<T>, Add<T>, Const<T, MINF>, Zero<T>> {
  using base =
      LazySegmentTree<T, T, Max<T>, Add<T>, Add<T>, Const<T, MINF>, Zero<T>>;
  AddMax_LazySegmentTree(const vector<T>& v) : base(v) {}
};

template <typename T, T INF>
struct AddMin_LazySegmentTree
    : LazySegmentTree<T, T, Min<T>, Add<T>, Add<T>, Const<T, INF>, Zero<T>> {
  using base =
      LazySegmentTree<T, T, Min<T>, Add<T>, Add<T>, Const<T, INF>, Zero<T>>;
  AddMin_LazySegmentTree(const vector<T>& v) : base(v) {}
};

template <typename T>
struct AddSum_LazySegmentTree
    : LazySegmentTree<Pair<T>, T, Psum<T>, Padd<T>, Add<T>, Pid<T>, Zero<T>> {
  using base =
      LazySegmentTree<Pair<T>, T, Psum<T>, Padd<T>, Add<T>, Pid<T>, Zero<T>>;
  AddSum_LazySegmentTree(const vector<T>& v) {
    vector<Pair<T>> w(v.size());
    for (int i = 0; i < (int)v.size(); i++) w[i] = Pair<T>(v[i], 1);
    base::init(w);
  }
};

template <typename T, T MINF>
struct UpdateMax_LazySegmentTree
    : LazySegmentTree<T, T, Max<T>, Update<T>, Update<T>, Const<T, MINF>,
                      Const<T, MINF>> {
  using base = LazySegmentTree<T, T, Max<T>, Update<T>, Update<T>,
                               Const<T, MINF>, Const<T, MINF>>;
  UpdateMax_LazySegmentTree(const vector<T>& v) : base(v) {}
};

template <typename T, T INF>
struct UpdateMin_LazySegmentTree
    : LazySegmentTree<T, T, Min<T>, Update<T>, Update<T>, Const<T, INF>,
                      Const<T, INF>> {
  using base = LazySegmentTree<T, T, Min<T>, Update<T>, Update<T>,
                               Const<T, INF>, Const<T, INF>>;
  UpdateMin_LazySegmentTree(const vector<T>& v) : base(v) {}
};

template <typename T, T UNUSED_VALUE>
struct UpdateSum_LazySegmentTree
    : LazySegmentTree<Pair<T>, T, Psum<T>, Padd<T>, Update<T>, Pid<T>,
                      Const<T, UNUSED_VALUE>> {
  using base = LazySegmentTree<Pair<T>, T, Psum<T>, Padd<T>, Update<T>, Pid<T>,
                               Const<T, UNUSED_VALUE>>;
  UpdateSum_LazySegmentTree(const vector<T>& v) {
    vector<Pair<T>> w(v.size());
    for (int i = 0; i < (int)v.size(); i++) w[i] = Pair<T>(v[i], 1);
    base::init(w);
  }
};

}  // namespace SegmentTreeUtil
using SegmentTreeUtil::AddMax_LazySegmentTree;
using SegmentTreeUtil::AddMin_LazySegmentTree;
using SegmentTreeUtil::AddSum_LazySegmentTree;
using SegmentTreeUtil::UpdateMax_LazySegmentTree;
using SegmentTreeUtil::UpdateMin_LazySegmentTree;
using SegmentTreeUtil::UpdateSum_LazySegmentTree;