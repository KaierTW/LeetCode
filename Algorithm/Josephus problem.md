# Josephus problem

Wiki : https://zh.wikipedia.org/wiki/%E7%BA%A6%E7%91%9F%E5%A4%AB%E6%96%AF%E9%97%AE%E9%A2%98


影片參考 : https://www.youtube.com/watch?v=Yeh1_2GyS5s
N = 人數 ，K = 每幾個人殺一個

通解f(N , K) = f(N - 1 , K) + K (若這個值>N的話，要減掉N)
N個人剩下的生存者 和殺掉一個變成N-1個人剩下的生存者，應該會是一樣的，因為本質上是同一個遊戲
只是要重新編號。

Ex: N = 8 ， K = 3，

一個人 : f(1 , 3) = 1(生還者)

兩個人 : f(2 , 3) = f(1 , 3) + 3 = 1 + 3 = 4 > N(2) → 4 - 2 = 2

三個人 : f(3 , 3) = f(2 , 3) + 3 = 2 + 3 = 5 > N(3) → 5 - 3 = 2

四個人 : f(4 , 3) = f(3 , 3) + 3 = 2 + 3 = 5 > N(4) → 5 - 4 = 1

五個人 : f(5 , 3) = f(4 , 3) + 3 = 1 + 3 = 4 < N(5)

六個人 : f(6 , 3) = f(5 , 3) + 3 = 4 + 3 = 7 > N(6) → 7 - 6 = 1

七個人 : f(7 , 3) = f(6 , 3) + 3 = 1 + 3 = 4 < N(7)

八個人 : f(8 , 3) = f(7 , 3) + 3 = 4 + 3 = 7 < N(8)

Code :

```C
int findTheWinner(int n, int k) {
    //Here's a solution in C using a mathematical approach (Josephus problem):
    int winner = 1;
    for (int i = 2; i <= n; i++) {
        winner = (winner + k);
        while(winner > i) winner -= i;
        printf("Winner : %d\n" ,winner);
    }
    return winner;
}
```


網頁參考 : https://blog.csdn.net/u011500062/article/details/72855826
通解公式 : 
f(N , K) = (f(N - 1 , K) + K) % N

其實和上面公式一樣，但這個是讓人站在index位置上，所以起始是0，所以可以用取餘數的方式

Ex: N = 8 ， K = 3，

一個人 : f(1 , 3) = 0(生還者) → index是0 實際上是1的位置(Player)

兩個人 : f(2 , 3) = (f(1 , 3) + 3) % 2 = (0 + 3) % 2 = 3 % 2 = 1 → index是1 實際上是2的位置(Player)

三個人 : f(3 , 3) = (f(2 , 3) + 3) % 3 = (1 + 3) % 3 = 4 % 3 = 1 → index是1 實際上是2的位置(Player)

四個人 : f(4 , 3) = (f(3 , 3) + 3) % 4 = (1 + 3) % 4 = 4 % 4 = 0 → index是0 實際上是1的位置(Player)

五個人 : f(5 , 3) = (f(4 , 3) + 3) % 5 = (0 + 3) % 5 = 3 % 5 = 3 → index是3 實際上是4的位置(Player)

六個人 : f(6 , 3) = (f(5 , 3) + 3) % 6 = (3 + 3) % 6 = 6 % 6 = 0 → index是0 實際上是1的位置(Player)

七個人 : f(7 , 3) = (f(6 , 3) + 3) % 7 = (0 + 3) % 7 = 3 % 7 = 3 → index是3 實際上是4的位置(Player)

八個人 : f(8 , 3) = (f(7 , 3) + 3) % 8 = (3 + 3) % 8 = 6 % 8 = 6 → index是6 實際上是7的位置(Player)

Code : 
```C
int findTheWinner(int n, int k) {
   //Here's a solution in C using a mathematical approach (Josephus problem):
    int winner = 0;
    for (int i = 1; i <= n; i++) {
        winner = (winner + k) % i;
    }
    return winner + 1;     
}
```

>[!IMPORTANT]
>其實總的來說就是把生還者的位置一直往後推K個，但要考慮超過N的時候
>
>![image](https://github.com/KaierTW/LeetCode/assets/106085605/865d3fdd-bb4a-4021-a2a8-3fa21213c052)
>
>![image](https://github.com/KaierTW/LeetCode/assets/106085605/c061811e-f9e9-4a6f-a213-4f9063bd15bd)

