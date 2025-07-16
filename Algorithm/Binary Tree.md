# 二元樹遍歷 (Binary Tree Traversal)

假設一個節點 Node，包含：

* `Node.val`（節點值）
* `Node.left`（左子樹）
* `Node.right`（右子樹）

---

## 1. 前序遍歷（Preorder Traversal）

**訪問順序：** 根節點 → 左子樹 → 右子樹

* **流程：**

  1. 訪問當前節點 (root)
  2. 前序遍歷左子樹
  3. 前序遍歷右子樹

* **遞迴寫法（Python示範）**

  ```python
  def preorder(root):
      if root is None:
          return
      print(root.val)          # 訪問根節點
      preorder(root.left)      # 遍歷左子樹
      preorder(root.right)     # 遍歷右子樹
  ```

* **特點：**

  * 根節點最先被訪問。
  * 常用於複製樹或序列化樹。

---

## 2. 中序遍歷（Inorder Traversal）

**訪問順序：** 左子樹 → 根節點 → 右子樹

* **流程：**

  1. 中序遍歷左子樹
  2. 訪問當前節點 (root)
  3. 中序遍歷右子樹

* **遞迴寫法（Python示範）**

  ```python
  def inorder(root):
      if root is None:
          return
      inorder(root.left)       # 遍歷左子樹
      print(root.val)          # 訪問根節點
      inorder(root.right)      # 遍歷右子樹
  ```

* **特點：**

  * 對二元搜尋樹 (BST) 來說，中序遍歷會輸出排序後的節點值（由小到大）。
  * 常用於取得排序結果。

---

## 3. 後序遍歷（Postorder Traversal）

**訪問順序：** 左子樹 → 右子樹 → 根節點

* **流程：**

  1. 後序遍歷左子樹
  2. 後序遍歷右子樹
  3. 訪問當前節點 (root)

* **遞迴寫法（Python示範）**

  ```python
  def postorder(root):
      if root is None:
          return
      postorder(root.left)     # 遍歷左子樹
      postorder(root.right)    # 遍歷右子樹
      print(root.val)          # 訪問根節點
  ```

* **特點：**

  * 根節點最後被訪問。
  * 常用於刪除樹或後序運算（例如計算樹狀結構的值）。

---

# 遍歷總結表

| 遍歷方法         | 訪問順序      | 範例 (對應樹: A 為根，左子 B，右子 C) | 特點                 |
| ------------ | --------- | ------------------------ | ------------------ |
| 前序 Preorder  | 根 → 左 → 右 | A B C                    | 根節點先訪問，序列化樹常用      |
| 中序 Inorder   | 左 → 根 → 右 | B A C                    | 二元搜尋樹會排序輸出         |
| 後序 Postorder | 左 → 右 → 根 | B C A                    | 根節點最後訪問，適合刪除樹或計算結果 |

---

# 範例說明

假設樹結構：

```
    A
   / \
  B   C
```

* 前序：A → B → C
* 中序：B → A → C
* 後序：B → C → A

---

如果你想，我也可以幫你整理**非遞迴版本**的遍歷或其他語言實作喔！你想要嗎？
