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
**(1)遞迴函式**
Ackermann's funtion成長速度非常快，因此其時間複雜度也會快速增加  
$T(m,n)$ =  
            $O(1)$  
            $T(m-1, 1)$ + $O(1)$  
            $T(m, n-1)$ + $T(m-1, A(m, n-1))$ +$O(1)$  
計算時間無法簡單表示成一般的函式  
時間複雜度 非常快速成長  

當m,n增加，遞迴深度也會快速增加  
空間複雜度 最大遞迴深度  

**(2)非遞迴演算法**
時間複雜度 與 **遞迴函式** 同等級  
空間複雜度 與堆疊最大大小有關

## 4. 測試與驗證  
**(1)遞迴函式**  
  <img width="1101" height="333" alt="image" src="https://github.com/user-attachments/assets/b6a7a105-21a8-4612-8e1b-436ed0cf26c8" />  
  <img width="743" height="211" alt="image" src="https://github.com/user-attachments/assets/a4be7c0f-7258-4842-bff1-5fc22fce1c0a" />  

**(2)非遞迴演算法**  
  <img width="643" height="252" alt="image" src="https://github.com/user-attachments/assets/5cf265b7-6915-4a74-b028-41478bd0d62a" />  
  <img width="458" height="94" alt="image" src="https://github.com/user-attachments/assets/63643e7d-9e6f-4baf-acff-357c3517f18e" />  

## 5. 申論及開發報告  
主要使用遞迴的方式實作 Ackermann's funtion  
由於 Ackermann's funtion本身就是透過遞迴定義，因此遞迴函式可以直接依照數學定義進行轉換，Ackermann's funtion具有非常快速的成長速度，當輸入值稍微增加時，就可能產生大量的遞迴呼叫
因此如果輸入值過大，可能造成執行時間過長或堆疊溢位
另外使用堆疊建立非遞迴演算法，透過堆疊的 LIFO 特性，可以模擬原本函式遞迴的執行順序

# Problem2  
## 1. 解題說明  
  如果 $S$ 是一個包含 $n$ 個元素的集合，則 $S$ 的冪集是由 $S$ 所有可能的子集合所組成的集合  
  $S$ = {a,b,c}  
  則 $P(S)$ = {∅,{a},{b},{c},{a,b},{a,c},{b,c},{a,b,c}}  
  一個包含 $n$ 個元素的集合，其冪集一共有  $2^n$ 個子集合
  
  使用 遞迴 產生所有子集合  
  假設目前集合為 $S$ = {a,b,c}  
  取出最後一個元素 $c$ 計算 $P({a,b})$  
  得到 {∅,{a},{b},{a,b}}  
  接著將 $c$ 分別加入上述每一個子集合 {{c},{a,c},{b,c},{a,b,c}}  
  最後將兩部分合併 P({a,b,c}) = {​∅,{a},{b},{a,b},{c},{a,c},{b,c},{a,b,c}}  ​

## 2. 程式實作
  ```cpp
  #include <iostream>

using namespace std;

void PowerSet(int* S, int n, int index, int* current, int currentSize)
{
    if (index == n){

        cout << "{ ";
        for (int i = 0; i < currentSize; i++)
            cout << current[i] << " ";
        cout << "}" << endl;

        return;
    }

    PowerSet(S, n, index + 1, current, currentSize);

    current[currentSize] = S[index];

    PowerSet(S, n, index + 1, current, currentSize + 1);
}

int main()
{
    int n;
    cin >> n;

    int* S = new int[n];
    int* current = new int[n];

    for (int i = 0; i < n; i++)
        cin >> S[i];

    PowerSet(S, n, 0, current, 0);

    delete[] S;
    delete[] current;

    return 0;
}
  ```
## 3. 效能分析  
  **(1)**  
  一個 n 個元素的集合有 $2^n$ 個子集合  
  每次建立新的 subset 時，還需要複製原本的元素，因此最壞情況下需要額外的 $O(n)$  
  時間複雜度為 $O(n2^n)$  

  **(2)**  
  $n$ 個元素，因此儲存所有結果需要 $O(n2^n)$  
  遞迴本身會產生最多 $O(n)$ 的呼叫堆疊  
  空間複雜度為 $O(n2^n)$  
