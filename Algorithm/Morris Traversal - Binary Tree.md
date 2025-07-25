# Morris Traversal
搭配 [114. Flatten Binary Tree to Linked List](Medium/114.%20Flatten%20Binary%20Tree%20to%20Linked%20List.md)

>[!TIP]
># ✅ 原地修改 Morris Traversal 解法
>
>### 🔧 程式碼：
>
>```cpp
>class Solution {
>public:
>    void flatten(TreeNode* root) {
>        TreeNode* curr = root;
>
>        while (curr) {
>            if (curr->left) {
>                // 找左子樹的最右節點（predecessor）
>                TreeNode* pred = curr->left;
>                while (pred->right) {
>                    pred = pred->right;
>                }
>
>                // 將目前節點的右子樹接到 pred 的右邊
>                pred->right = curr->right;
>
>                // 把左子樹搬到右邊
>                curr->right = curr->left;
>                curr->left = nullptr;
>            }
>
>            // 移動到下一個節點（往右）
>            curr = curr->right;
>        }
>    }
>};
>```
>
>---
>
>## ✅ Morris 解法逐步說明
>
>### 對於每個節點 curr：
>
>1. **如果 curr 有左子樹：**
>
>   * 找 curr 左子樹的 **最右節點 pred**
>   * 把 curr 的右子樹接到 pred->right 上
>   * 然後 curr->right 改成 curr->left（也就是把左子樹搬到右邊）
>   * 清空 curr->left（變成 linked list 的形狀）
>
>2. **然後 curr 往右移動**（下一個節點）
>
>---
>
>### 以這棵樹為例：
>
>```
>    1
>   / \
>  2   5
> / \   \
>3   4   6
>```
>
>* curr = 1，有左子樹 2，找 2 的最右節點是 4
>
>  * 4->right = 5
>  * 1->right = 2，1->left = null
>
>此時變成：
>
>```
>1
> \
>  2
> / \
>3   4
>       \
>        5
>         \
>          6
>```
>
>下一步 curr = 2，繼續做一樣的事…
>
