#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_A"

#include "../../template/template.hpp"
#include "../../graph/topological-sort.hpp"

using namespace Nyaan; void Nyaan::solve() {
  ini(N, M);
  auto g = graph(N, M, true, false);
  auto topo = TopologicalSort<vvi>(g);
  out(topo.size() == 0);
}