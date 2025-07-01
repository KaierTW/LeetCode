# OS Related

## User Mode vs. Kernel Mode
在作業系統中，**user mode（使用者模式）**和**kernel mode（核心模式）**是兩種不同的執行層級，它們的主要差別在於**權限**和**可存取的資源**。以下是詳細比較：

---

### 🧠 **核心差異**

| 特性 | User Mode（使用者模式） | Kernel Mode（核心模式） |
|------|--------------------------|--------------------------|
| 權限 | 受限 | 完全存取硬體與系統資源 |
| 可存取資源 | 無法直接存取硬體或記憶體 | 可存取所有硬體與記憶體 |
| 安全性 | 高（限制操作以防止錯誤影響系統） | 低（錯誤可能導致系統崩潰） |
| 執行內容 | 應用程式（如 Word、Chrome） | 作業系統核心功能（如記憶體管理、檔案系統） |
| 切換方式 | 需透過系統呼叫（System Call）進入核心模式 | 可直接執行核心程式碼 |

---

### 🔧 **為什麼要區分這兩種模式？**

1. **安全性**：防止應用程式直接操作硬體或系統資源，避免系統崩潰或資料損毀。
2. **穩定性**：核心模式執行的是作業系統的關鍵功能，必須受到嚴格控制。
3. **效率**：透過模式切換，系統可以有效管理資源與權限。

---

### 📌 **實際例子**

- 當你在瀏覽器中打開一個網頁，這是在 **user mode** 執行。
- 當瀏覽器需要存取檔案或網路，它會透過 **system call** 請求作業系統幫忙，這時會切換到 **kernel mode** 來執行相關操作。

---

## System call
System call（系統呼叫）是使用者模式的程式（例如應用程式）與作業系統核心（kernel）溝通的橋樑。它允許應用程式請求作業系統執行某些特權操作，例如讀寫檔案、分配記憶體、建立程序等。

---

### 🧭 **System Call 的完整流程**

以下是從使用者程式發出 system call 到核心執行並返回結果的整個流程：

---

#### 1. **使用者程式發出請求**
使用者程式呼叫一個系統函式，例如：
```c
read(fd, buffer, size);
```
這個函式其實是系統呼叫的包裝（wrapper），它會準備好參數並觸發 system call。

---

#### 2. **切換到核心模式（Mode Switch）**
系統呼叫會透過特殊的 CPU 指令（例如 `int 0x80` 或 `syscall`）觸發中斷或陷阱（trap），這會導致 CPU 從 **user mode** 切換到 **kernel mode**。

---

#### 3. **核心接管控制權**
作業系統核心會根據 system call 編號（通常存在某個暫存器中）來判斷要執行哪一個功能，例如 `read`、`write`、`open` 等。

---

#### 4. **執行核心功能**
核心執行對應的功能，例如從磁碟讀取資料、檢查權限、操作記憶體等。

---

#### 5. **返回結果**
執行完畢後，核心會將結果（例如成功、錯誤碼、讀取的位元組數）放入暫存器或記憶體中。

---

#### 6. **切換回使用者模式**
核心透過 `return from interrupt` 或類似機制，將控制權交還給使用者程式，並切換回 **user mode**。

---

#### 7. **使用者程式繼續執行**
使用者程式取得 system call 的返回值，繼續執行後續邏輯。

---

### 📊 **流程圖簡化版**

```text
[User Program]
     ↓
System Call (e.g., read)
     ↓
[Trap to Kernel Mode]
     ↓
[Kernel: Handle Request]
     ↓
[Return to User Mode]
     ↓
[User Program Continues]
```

---

# Programming Related

## 函數寫法差異
bool x = a();
bool y = b();
if(x || y) {

}
if(a() || b()) {

}
這兩種寫法在**語意上是不同的**，主要差異在於：
**是否會重複呼叫 `a()` 和 `b()` 函式，以及呼叫的時機。**

---

### 🔹 寫法一：

```cpp
bool x = a();
bool y = b();
if(x || y) {

}
```

#### ✅ 特點：

* `a()` 與 `b()` 都**會被呼叫一次**，不論 `a()` 回傳的是 `true` 還是 `false`。
* 結果儲存在變數 `x` 和 `y` 中。
* `if` 判斷的是已經算好的結果，不再呼叫函式。

---

### 🔹 寫法二：

```cpp
if(a() || b()) {

}
```

#### ✅ 特點：

* `a()` 與 `b()` 是**即時運算**。
* 使用 **短路運算（short-circuit evaluation）**：

  * 如果 `a()` 回傳 `true`，則 `b()` **不會被呼叫**，因為 `x || y` 已經成立。
  * 只有在 `a()` 回傳 `false` 的情況下，才會執行 `b()`。

---

### ✅ 比較總結：

| 項目 | 寫法一 `x = a(); y = b();`   | 寫法二 `if(a() \|\| b())` |
|------|-------------|--------------------|
| 是否都會呼叫 `a()` 與 `b()`   | ✅ 一定會     | ❌ 不一定會（看 `a()` 結果）   |
| 是否有短路效果                | ❌ 沒有                        | ✅ 有                          |
| 是否重複呼叫函式              | ❌ 不會                        | ✅ 每次 if 判斷都會再呼叫一次    |
| 是否能重複使用結果變數         | ✅ 可以使用 `x`、`y` 重複使用   | ❌ 不能（除非你額外存起來）      |

---

### 🔸 什麼時候該用哪個？

* 若 `a()` 或 `b()` 有副作用（像是輸出、計數、改變狀態），**需注意呼叫次數差異**。
* 如果你不想 `b()` 被呼叫（除非必要），用第二種。
* 如果你要重複用 `a()`、`b()` 的結果，用第一種（存成變數）。

---

## 十六進位
這是一個 C/C++ 中的\*\*指標與型別轉換（type casting / aliasing）\*\*問題，牽涉到記憶體、資料表示與型別解釋。

我們逐步解析你的問題：

---


### 🔸 原始程式碼：

```cpp
unsigned int N = 0xaabbccdd;
unsigned char* M;
M = (unsigned char*)&N;
```

### 🔹 問題：`*M` 是什麼？

---

### ✅ 解釋：

```cpp
unsigned int N = 0xaabbccdd;
```

這表示 `N` 是一個 32-bit 整數，值為 16 進位的 `0xAABBCCDD`，也就是：

```
0xAA 0xBB 0xCC 0xDD
```

但記住，這是用 **十六進位** 表示一個 `unsigned int` 整數。實際上它會被存在記憶體的 4 個位元組中。

---

### 🔸 重要：記憶體儲存順序（Endian）

這邊會根據電腦架構是 **little-endian** 還是 **big-endian** 而有所不同。

#### ✅ 大部分現代 PC（例如 x86/x64 架構）是 **Little Endian**：

* 在 Little Endian 中，最低位的 byte（0xDD）會放在最前面（低位址）。
* 記憶體排列如下（假設從位址 `M` 開始）：

```
M[0] = 0xDD
M[1] = 0xCC
M[2] = 0xBB
M[3] = 0xAA
```

---

### ✅ 所以 `*M` 是什麼？

```cpp
*M == M[0] == 第一個位元組 == 0xDD
```

### 🔚 結論：

* **在 Little Endian 系統中（如 x86/x64）**，`*M` 的值是 `0xDD`。
* 若是 **Big Endian 系統**，則 `*M` 會是 `0xAA`。

---

### 補充說明

這類問題常出現在以下情況：

* 二進位資料解析（例如：網路封包、影像格式解析）
* 不同位元型別間的指標轉換
* 記憶體對齊與效能問題

---

## 給一個linked list header找出linked list 1/3 node的地方（if list is 3的倍數）

這題其實是在考你如何 **找出一個 linked list 中第 1/3 處的節點**，條件是：

> 如果 linked list 的長度是「3 的倍數」，請找出第 **1/3 處** 的節點（也就是第 n/3 個節點）。

---

### ✅ 問題重點翻譯

假設你的 linked list 有 `n` 個節點：

* 如果 `n` 是 3 的倍數（例如：3、6、9...），那你要找的是第 `n / 3` 個節點（從第 1 個開始算）。
* 如果 `n` 不是 3 的倍數，就**不做任何事**或回傳 null（視題目需求而定）。

---

### 🔍 舉例說明

* linked list: `1 -> 2 -> 3 -> 4 -> 5 -> 6`
* 總長度：6，是 3 的倍數 → 找第 `6 / 3 = 2` 個節點
* 所以回傳節點 `2`（也就是值為 `2` 的節點）

---

### 🔧 實作思路

因為你不知道 list 有多長，所以可以先：

1. 走一次計算長度 `n`
2. 如果 `n % 3 != 0` → 回傳 `nullptr`
3. 否則再走一次，到第 `n / 3` 個節點

---

### ✅ 範例 C++ 程式碼

假設節點結構如下：

```cpp
struct ListNode {
    int val;
    ListNode* next;
};
```

找 1/3 節點的函式：

```cpp
ListNode* oneThirdNode(ListNode* head) {
    if (!head) return nullptr;

    // 第一次：計算長度
    int length = 0;
    ListNode* curr = head;
    while (curr) {
        length++;
        curr = curr->next;
    }

    // 不是 3 的倍數就不處理
    if (length % 3 != 0) return nullptr;

    // 第二次：走到第 length / 3 個節點
    int targetIndex = length / 3; // 第幾個節點（從 1 開始）
    curr = head;
    for (int i = 1; i < targetIndex; ++i) {
        curr = curr->next;
    }

    return curr;
}
```

---

### 🧠 面試常見 follow-up：

* 如果只能走一次 list 怎麼辦？（Hint: 用 slow 指標走 1 步，fast 每次走 3 步）
* 如果要找 1/2（中間）、1/4、2/3 呢？
* 若是循環 linked list？

---

這是一個經典的面試 follow-up 問題：
👉 **「如何只走一遍 linked list，就找出第 1/3 節點（如果長度是 3 的倍數）」**

---

## ✅ 解法：用三倍速的技巧（fast pointer）

### 🎯 核心想法：

* 用兩個指標：`slow` 和 `fast`
* `fast` 每次走 **3 步**
* `slow` 每次走 **1 步**

這樣當 `fast` 走到結尾時，`slow` 就剛好走了 **1/3 的距離**

---

### 🧠 為什麼？

假設 list 長度是 `n = 3k`

* `fast` 每次走 3 步 → 走完需要 k 次
* `slow` 每次走 1 步 → 剛好走了 k 步 → 就是第 `n / 3` 個節點！

---

## ✅ 單遍實作 C++ 範例：

```cpp
struct ListNode {
    int val;
    ListNode* next;
};

ListNode* oneThirdNode(ListNode* head) {
    if (!head || !head->next || !head->next->next) return nullptr;

    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next->next;
    }

    // 檢查是否剛好是 3 的倍數
    // fast == nullptr 表示走到底剛剛好
    if (fast == nullptr)
        return slow;
    else
        return nullptr;
}
```

---

## 🧪 範例：

### Input:

```
1 -> 2 -> 3 -> 4 -> 5 -> 6
```

* `slow`: 最後停在 `2`
* `fast`: 走到 `nullptr`
* 長度為 6（是 3 的倍數）✅ → 回傳 `2`

---

## 🚫 非 3 的倍數情況：

如果 list 是：

```
1 -> 2 -> 3 -> 4 -> 5
```

* `fast` 最後剩一兩格 → 表示不是 3 的倍數 → 回傳 `nullptr`

---

## ✅ 總結：

| 技巧        | 說明                  |
| --------- | ------------------- |
| 兩個指標      | `slow` 一步、`fast` 三步 |
| fast 到尾時  | slow 剛好在 1/3 處      |
| 只走一遍 list | 時間 O(n)，空間 O(1)     |

---

要不要我也幫你轉成 Python、Java 版？或者加上單元測試範例？



## Binary Search Tree (BST)
當然可以！以下是 Binary Search Tree (BST) 的三大函式：search、insert 和 delete 的完整 C++ 範例，包括結構定義與基本操作。

---

✅ 範例：BST 實作 (C++)

```CPP
#include <iostream>
using namespace std;

// 節點定義
struct TreeNode {
   int val;
   TreeNode* left;
   TreeNode* right;

   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 1. Insert 函式
TreeNode* insert(TreeNode* root, int key) {
   if (root == nullptr) return new TreeNode(key);

   if (key < root->val)
       root->left = insert(root->left, key);
   else if (key > root->val)
       root->right = insert(root->right, key);

   return root;
}

// 2. Search 函式
TreeNode* search(TreeNode* root, int key) {
   if (root == nullptr || root->val == key) return root;

   if (key < root->val)
       return search(root->left, key);
   else
       return search(root->right, key);
}

// 3. Delete 函式
TreeNode* findMin(TreeNode* root) {
   while (root && root->left) root = root->left;
   return root;
}

TreeNode* deleteNode(TreeNode* root, int key) {
   if (!root) return nullptr;

   if (key < root->val)
       root->left = deleteNode(root->left, key);
   else if (key > root->val)
       root->right = deleteNode(root->right, key);
   else {
       // 找到了要刪的節點
       if (!root->left) {
           TreeNode* temp = root->right;
           delete root;
           return temp;
       }
       else if (!root->right) {
           TreeNode* temp = root->left;
           delete root;
           return temp;
       }
       // 有兩個子節點：找右子樹的最小值來取代
       TreeNode* temp = findMin(root->right);
       root->val = temp->val;
       root->right = deleteNode(root->right, temp->val);
   }

   return root;
}

// 輔助：中序遍歷印出 BST
void inorder(TreeNode* root) {
   if (!root) return;
   inorder(root->left);
   cout << root->val << " ";
   inorder(root->right);
}

// 測試用 main()
int main() {
   TreeNode* root = nullptr;
   root = insert(root, 50);
   insert(root, 30);
   insert(root, 70);
   insert(root, 20);
   insert(root, 40);
   insert(root, 60);
   insert(root, 80);

   cout << "Inorder traversal: ";
   inorder(root);
   cout << endl;

   // Search 範例
   TreeNode* found = search(root, 60);
   if (found) cout << "Found node: " << found->val << endl;
   else cout << "Node not found." << endl;

   // Delete 範例
   root = deleteNode(root, 70);
   cout << "After deleting 70: ";
   inorder(root);
   cout << endl;

   return 0;
}
```

---

✅ 你要注意的點：

|函式 | 要點|
|----|----|
|insert| 遞迴建立左或右子樹|
|search| 找不到就 return nullptr|
|delete| 要處理三種情況：1. 沒子節點（直接刪）2. 一個子節點（接上去）3. 兩個子節點（找右子樹最小值來取代）|


# Concept Related
## Call by Value, Call by Address, Call by Reference
這三個是「參數傳遞方式」的概念，用來控制函式呼叫時**如何傳遞參數**到函式內部。以下是它們的差異：

---

## ✅ 1. Call by Value（值呼叫）

* **意義**：把「參數的值」複製一份傳進函式中。
* **特性**：函式內修改參數，**不會影響原本的變數**。
* **用途**：安全、不會意外改變原資料。

### 範例（C++）：

```cpp
void foo(int x) {
    x = 10; // 修改 x 不影響外部
}

int main() {
    int a = 5;
    foo(a);
    cout << a; // 印出 5
}
```

---

## ✅ 2. Call by Address（位址呼叫 / 指標傳遞）

* **意義**：傳「變數的位址（pointer）」給函式。
* **特性**：函式內部透過指標**可以直接改變原本的變數值**。
* **用途**：希望函式能修改外部資料，或避免複製大量資料。

### 範例（C++）：

```cpp
void foo(int *x) {
    *x = 10; // 修改指標指向的變數
}

int main() {
    int a = 5;
    foo(&a);
    cout << a; // 印出 10
}
```

---

## ✅ 3. Call by Reference（參考呼叫）

* **意義**：傳「變數的別名（reference）」進函式，就像是傳進變數本身。
* **特性**：和 Call by Address 一樣，**可以直接修改原本的變數值**，但語法更簡潔。
* **用途**：C++ 專屬功能，適合想簡化 Call by Address 的語法。

### 範例（C++）：

```cpp
void foo(int &x) {
    x = 10; // 直接改變傳進來的變數
}

int main() {
    int a = 5;
    foo(a);
    cout << a; // 印出 10
}
```

---

## ✅ 差異總整理：

| 傳遞方式              | 是否複製資料   | 是否可改變外部變數 | 常見語言               | 備註            |
| ----------------- | -------- | --------- | ------------------ | ------------- |
| Call by Value     | ✅ 是      | ❌ 否       | C, C++, Java（基本型別） | 安全但無法修改外部變數   |
| Call by Address   | ❌ 否（傳指標） | ✅ 是       | C, C++             | 比較麻煩，要自己處理指標  |
| Call by Reference | ❌ 否      | ✅ 是       | C++ 專用             | 更安全且簡潔，不用指標語法 |

---

如果你想看每一種的實際效果，我可以幫你寫一段完整的比較範例。需要嗎？


# Some Refernce
[C/C++ 常見試題](https://medium.com/@earth875/c-c-%E5%B8%B8%E8%A6%8B%E8%A9%A6%E9%A1%8C-961619b14f88)

[面試 C/C++ 觀念整理](https://skylerz.medium.com/%E9%9D%A2%E8%A9%A6-c-c-%E8%A7%80%E5%BF%B5%E6%95%B4%E7%90%86-3a259b0a09bc)

