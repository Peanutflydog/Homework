# Problem1  
## 1. 解題說明  
Ackermann's funtion $A(m,n)$ 定義如下：  
<img width="636" height="132" alt="image" src="https://github.com/user-attachments/assets/0b1e7100-7286-481c-9ef3-5c1284d3f223" />  
Ackermann 函數是一個成長速度非常快的遞迴函數，即使輸入值不大，也會產生非常大量的函式呼叫。  
**(1) 撰寫一個遞迴函式計算 Ackermann 函數**  

  如果 m=0，回傳 n+1  
  如果 n=0，計算 $A(m-1,1)$  
  其他情況，計算 $A(m−1,A(m,n−1))$  
  
**(2) 撰寫一個非遞迴演算法計算 Ackermann 函數**  

Ackermann's funtion本身有巢狀遞迴  
$A(m−1,A(m,n−1))$  
使用堆疊呼叫函式，利用LIFO特性，保存還未計算的m  
## 2. 程式實作  
**(1)**    
```cpp
#include <iostream>
using namespace std;

int Ackermann(int m, int n)
{
    if (m == 0) {
        return n + 1;
    }
    else if (n == 0) {
        return Ackermann(m - 1, 1);
    }
    else {
        return Ackermann(m - 1, Ackermann(m, n - 1));
    }
}

int main()
{
    int m, n;

    cin >> m >> n;
    cout << Ackermann(m, n) << endl;

    return 0;
}
```
**(2)**
```cpp
#include <iostream>
#include <cstdlib>

using namespace std;

int Ackermann(int m, int n)
{
    int c = 100;
    int top = 0;

    int* stack = new int[c];

    stack[top++] = m;

    while (top > 0)
    {
        m = stack[--top];

        if (m == 0){
            n++;
        }
        else if (n == 0){
            if (top >= c){
                c *= 2;
                int* newStack = new int[c];

                for (int i = 0; i < top; i++) {
                    newStack[i] = stack[i];
                }

                delete[] stack;
                stack = newStack;
            }

            stack[top++] = m - 1;
            n = 1;
        }
        else
        {
            if (top + 2 >= c) {
                c *= 2;

                int* newStack = new int[c];

                for (int i = 0; i < top; i++) {
                    newStack[i] = stack[i];
                }

                delete[] stack;
                stack = newStack;
            }

            stack[top++] = m - 1;
            stack[top++] = m;
            n--;
        }
    }

    int result = n;

    delete[] stack;

    return result;
}

int main()
{
    int m, n;

    cin >> m >> n;
    cout << Ackermann(m, n) << endl;

    return 0;
}
```
## 3. 效能分析
**(1)**
Ackermann's funtion成長速度非常快，因此其時間複雜度也會快速增加  
$T(m,n)$ =  
            $O(1)$  
            $T(m-1, 1)$ + $O(1)$  
            $T(m, n-1)$ + $T(m-1, A(m, n-1))$ +$O(1)$  
計算時間無法簡單表示成一般的函式
時間複雜度 非常快速成長

當m,n增加，遞迴深度也會快速增加
空間複雜度 最大遞迴深度
            
## 3. 效能分析  
  **(1)**  
  一個 n 個元素的集合有 $2^n$ 個子集合  
  每次建立新的 subset 時，還需要複製原本的元素，因此最壞情況下需要額外的 $O(n)$  
  時間複雜度為 $O(n2^n)$  

  **(2)**  
  $n$ 個元素，因此儲存所有結果需要 $O(n2^n)$  
  遞迴本身會產生最多 $O(n)$ 的呼叫堆疊  
  空間複雜度為 $O(n2^n)$  
