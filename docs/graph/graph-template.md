## グラフテンプレート

### 構造体・型エイリアス

| 名前 | 説明 |
| --- | --- |
| `edge<T>` | 型`T`の重みが付いた辺 |
| `Edges<T>` | 型`T`の重みが付いた辺のリスト |
| `WeightedGraph<T>` | 型`T`の重みが付いた(有向/無向)グラフ |
| `UnweightedGraph` | 重みなし(有向/無向)グラフ |

### 入力用関数

- `graph(int N, int M = -1, bool is_directed = false, bool is_1origin = true)`

    重みなしのグラフを標準入力から読み込み、`UnweightedGraph`型で返す。

    | 引数 | 説明 |
    | --- | --- |
    | `N` | グラフの頂点の個数。 |
    | `M` | グラフの辺の個数。$-1$を設定すると$N-1$で置き換えられる。 |
    | `is_directed` | `false`なら、入力された辺の逆辺も追加する。自己ループは$2$回追加されることになる。 |
    | `is_1origin` | `true`なら頂点番号は$1$-indexed、`false`なら$0$-indexedとして入力を読み込む。どちらにしても返り値では頂点番号は$0$-originとする。 |
  
    以下の入力形式に対応する。
  
    > 辺iは、頂点u\[i]から頂点v\[i]へ向かう。
    > ```
    > u[0] v[0]
    > u[1] v[1]
    >  :
    > u[M-1] v[M-1]
    > ```

- `wgraph<T>(int N, int M = -1, bool is_directed = false, bool is_1origin = true)`

    型`T`の重みが付いた辺を持つグラフを標準入力から読み込み、`WeightedGraph`型で返す。

    | 引数 | 説明 |
    | --- | --- |
    | `N` | グラフの頂点の個数。 |
    | `M` | グラフの辺の個数。$-1$を設定すると$N-1$で置き換えられる。 |
    | `is_directed` | `false`なら、入力された辺の逆辺も追加する。自己ループは$2$回追加されることになる。 |
    | `is_1origin` | `true`なら頂点番号は$1$-indexed、`false`なら$0$-indexedとして入力を読み込む。どちらにしても返り値では頂点番号は$0$-originとする。 |

    以下の入力形式に対応する。

    > 辺iは、頂点u\[i]から頂点v\[i]へ向かい、その重みは c\[i] である。
    > ```
    > u[0] v[0] c[0]
    > u[1] v[1] c[1]
    >  :
    > u[M-1] v[M-1] c[M-1]
    > ```

- `esgraph<T>(int N, int M = -1, bool is_weighted = false, bool is_1origin = true)`

    型`T`の重みが付いた辺のリストを標準入力から読み込み、`Edges`型で返す。

    | 引数 | 説明 |
    | --- | --- |
    | `N` | グラフの頂点の個数。 |
    | `M` | グラフの辺の個数。$-1$を設定すると$N-1$で置き換えられる。 |
    | `is_weighted` | `true`のなら、重みを入力する。 |
    | `is_1origin` | `true`なら頂点番号は$1$-indexed、`false`なら$0$-indexedとして入力を読み込む。どちらにしても返り値では頂点番号は$0$-originとする。 |

    以下の入力形式に対応する。

    > 辺iは、頂点u\[i]から頂点v\[i]へ向かい、その重みは c\[i] である。重みなしの場合は c\[i] は空とする。
    > ```
    > u[0] v[0] c[0]
    > u[1] v[1] c[1]
    >  :
    > u[M-1] v[M-1] c[M-1]
    > ```

- `adjgraph<T>(int N, int M, T INF, bool is_weighted = true, bool is_directed = false, bool is_1origin = true)`

    型`T`の重みが付いた辺のリストを標準入力から読み込み、隣接行列として`vector<vector<T>>`型で返す。返り値を`A`とすると、`A[i][j]`は頂点`i`から頂点`j`へ向かう辺の重みである。入力されなかった辺の重みには`INF`が設定される。

    | 引数 | 説明 |
    | --- | --- |
    | `N` | グラフの頂点の個数。 |
    | `M` | グラフの辺の個数。$-1$を設定すると$N-1$で置き換えられる。 |
    | `INF` | 入力されなかった辺に設定される重み。 |
    | `is_directed` | `false`なら、入力された辺の逆辺も追加する。 |
    | `is_weighted` | `true`なら、重みを入力する。`false`なら、入力された辺の重みは1とする。 |
    | `is_1origin` | `true`なら頂点番号は$1$-indexed、`false`なら$0$-indexedとして入力を読み込む。どちらにしても返り値では頂点番号は$0$-originとする。  |

    以下の入力形式に対応する。

    > 辺iは、頂点u\[i]から頂点v\[i]へ向かい、その重みは c\[i] である。重みを入力しない場合は c\[i] は空とする。
    > ```
    > u[0] v[0] c[0]
    > u[1] v[1] c[1]
    >  :
    > u[M-1] v[M-1] c[M-1]
    > ```

    同じ辺が複数回与えらえる場合、後から入力されるもので上書きされる。
