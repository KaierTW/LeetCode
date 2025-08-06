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
