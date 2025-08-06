# Segment Tree
當然可以！Segment Tree（線段樹）是一種**高效的資料結構**，適用於解決像是：

* 區間查詢（例如：某個區間的最大值、最小值、總和等）
* 區間更新（進階應用）

---

## 🔧 1. 為什麼要用 Segment Tree？

### 假設情境：

你有一個整數陣列 `A = [5, 2, 8, 6, 3]`，你要不斷回答這樣的問題：

> 請問第 `l` 到第 `r` 項的最小值是什麼？

---

### ✅ 三種方法比較：

| 方法               | 時間複雜度（每次查詢）             |
| ---------------- | ----------------------- |
| 暴力查詢             | O(n)                    |
| 預先處理所有區間         | O(1) 查詢，但 O(n^2) 預處理，太慢 |
| **Segment Tree** | O(log n) 查詢與更新 ✅        |

---

## 🧠 2. Segment Tree 基本概念

### 整體結構：是一顆「完全二元樹」

* 每個節點都代表一個區間 `[l, r]`
* 節點儲存該區間的資訊（如最小值）
* 左子節點 = 左半部區間
* 右子節點 = 右半部區間

---

### 🧱 例子

原始陣列 `A = [5, 2, 8, 6, 3]`
建一棵表示最小值的 Segment Tree：

```
                [0,4]=2
              /         \
         [0,2]=2       [3,4]=3
         /    \         /   \
    [0,1]=2 [2,2]=8 [3,3]=6 [4,4]=3
    /   \
[0,0]=5 [1,1]=2
```

---

## 🔨 3. 操作

### ✅ 查詢（Range Minimum Query）

* 例如查詢 `[1, 4]` 的最小值
* 從 root 開始：

  * 如果節點的區間完全在查詢範圍內 ➜ 回傳該節點值
  * 如果完全不在查詢範圍 ➜ 回傳無效值（如 +∞）
  * 如果部分重疊 ➜ 拆成左右子區間遞迴查詢

時間複雜度是 `O(log n)`。

---

### ✅ 更新某個值

* 例如把 A\[2] = 8 改成 1
* 從 root 開始找到包含 index=2 的所有節點，重新計算最小值

也是 `O(log n)`。

---

## 📦 4. 儲存方式（用陣列模擬）

Segment Tree 通常用一個 `vector<int> tree(4*n)` 來儲存。

* 如果 parent 在 index `i`：

  * left child 是 `2*i`
  * right child 是 `2*i + 1`

---

## 📘 5. C++ 小範例：找區間最小值

```cpp
class SegmentTree {
    vector<int> tree;
    int n;

public:
    SegmentTree(vector<int>& A) {
        n = A.size();
        tree.resize(4 * n);
        build(A, 1, 0, n - 1);
    }

    void build(vector<int>& A, int node, int l, int r) {
        if (l == r) {
            tree[node] = A[l];
        } else {
            int mid = (l + r) / 2;
            build(A, node * 2, l, mid);
            build(A, node * 2 + 1, mid + 1, r);
            tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
        }
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return INT_MAX;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return min(
            query(node * 2, l, mid, ql, qr),
            query(node * 2 + 1, mid + 1, r, ql, qr)
        );
    }

    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};
```

---

## 🏁 總結

| 操作   | 時間複雜度    |
| ---- | -------- |
| 建樹   | O(n)     |
| 區間查詢 | O(log n) |
| 單點更新 | O(log n) |

---

如果你還想了解：

* 怎麼處理 **區間加法 / 區間更新**
* 或是 **Lazy Propagation**

我也可以進一步講解（這些是 Segment Tree 的進階版）。需要的話跟我說！

---

你問得非常好，這些問題正是理解 Segment Tree **內部實作原理** 的關鍵！以下我會從實際需求、為什麼用 `vector`、為什麼大小是 `4 * n`，以及如何實作 `build` 和 `query`，一步步清楚解釋。

---

## 🔸 為什麼 Segment Tree 用 `vector` 儲存？

因為 Segment Tree 是一顆**完全二元樹**（只要資料長度是固定的），我們就可以像處理「heap」一樣，用 **陣列（vector）模擬樹結構**：

* 不用動態配置 TreeNode 結構，效率更高（比 pointer-based tree 快很多）
* 可以透過簡單的數學公式直接存取 parent / child

  * 父節點：`i`
  * 左子節點：`2 * i`
  * 右子節點：`2 * i + 1`

---

## 🔸 為什麼要 `vector<int> tree(4 * n)`？

### 假設：

* 原始陣列大小為 `n`

### 目標：

* 构建一棵二元樹來儲存每個區間的統計資訊（如 min、sum、max）

### 樹的結構：

若 `n` 是 2 的冪，Segment Tree 會是一顆**滿二元樹（Full Binary Tree）**，有以下特性：

* 葉節點 = 原陣列每個元素，共 `n` 個
* 每層節點數減半，直到 root，所以整棵樹節點總數約為 `2n - 1`

但不是所有 `n` 都是 2 的冪，所以我們保守估算最多可能需要多少空間：

```
安全空間：4 * n
```

### 🧠 為什麼「4n」夠用？

這是因為：

* 樹的高度約為 `log2(n)`
* 每層最多節點數成倍數增加
* 預留多一點空間避免 overflow，實務上 `4 * n` 是常見安全值（甚至會有些空位沒用到）

---

## 🔧 Segment Tree 建立 `build` 詳解

假設我們有這個陣列：

```cpp
A = [5, 2, 8, 6]
```

我們要建出一棵存「最小值」的 segment tree。

### 範例結構如下：

```
              [0,3]
            /       \
        [0,1]       [2,3]
       /     \     /     \
    [0,0] [1,1] [2,2] [3,3]
```

### 🌱 C++ build 函數解釋

```cpp
void build(vector<int>& A, int node, int l, int r) {
    if (l == r) {
        // 葉節點：對應原陣列的元素
        tree[node] = A[l];
        return;
    }

    int mid = (l + r) / 2;

    // 建立左子樹
    build(A, node * 2, l, mid);

    // 建立右子樹
    build(A, node * 2 + 1, mid + 1, r);

    // 匯總：取左右子樹的最小值
    tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}
```

### 範例遞迴流程

```
build(1, 0, 3) → build(2, 0, 1) → build(4, 0, 0) 存 A[0]=5
                                  → build(5, 1, 1) 存 A[1]=2
                   → tree[2] = min(5, 2) = 2

               → build(3, 2, 3) → build(6, 2, 2) 存 A[2]=8
                                  → build(7, 3, 3) 存 A[3]=6
                   → tree[3] = min(8, 6) = 6

→ tree[1] = min(2, 6) = 2
```

---

## 🔍 Segment Tree 區間查詢 `query` 詳解

我們想查詢 A 陣列中某個區間 `[ql, qr]` 的最小值。

### C++ 實作：

```cpp
int query(int node, int l, int r, int ql, int qr) {
    // 完全不重疊：跳過
    if (qr < l || r < ql) return INT_MAX;

    // 完全包含：直接回傳
    if (ql <= l && r <= qr) return tree[node];

    // 部分重疊：分左右遞迴查詢
    int mid = (l + r) / 2;
    int leftMin = query(node * 2, l, mid, ql, qr);
    int rightMin = query(node * 2 + 1, mid + 1, r, ql, qr);

    return min(leftMin, rightMin);
}
```

### 📘 範例：查詢 \[1, 3]

* 先從根節點 \[0,3]
* \[0,3] 有一半區間落在 \[1,3] → 分裂
* 左子樹 \[0,1] → 查 \[1,1]
* 右子樹 \[2,3] → 查 \[2,3]
* 再合併：min(tree\[5], tree\[3])

---

## 📦 總結圖示

用 `vector<int> tree(4 * n)`，整體分布像這樣：

```
tree[1]  => [0,n-1]         ← root
├── tree[2] => [0,mid]
│   ├── tree[4] => [0,mid/2]
│   └── tree[5] => [mid/2+1,mid]
└── tree[3] => [mid+1,n-1]
    ├── tree[6]
    └── tree[7]
```

---

## ✅ 快速總結

| 概念            | 解釋                                                 |
| ------------- | -------------------------------------------------- |
| 為什麼用 `vector` | 因為 Segment Tree 是完全二元樹，可用陣列模擬樹                     |
| 為什麼用 `4 * n`  | 最多只需 2n 節點，但為了保險，實務常用 4n                           |
| `build`       | 遞迴地建左右子樹，最終節點值為區間 min/sum/max                      |
| `query`       | 根據查詢範圍，走訪必要節點，合併回傳值                                |
| 複雜度           | `build: O(n)`，`query: O(log n)`，`update: O(log n)` |

---

如果你想要我畫圖表示 segment tree 運作流程，或是用其他語言（例如 Python），都可以再跟我說～
