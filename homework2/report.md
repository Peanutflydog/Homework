# 41143142
### Problem1  
## 解題說明  
<img width="517" height="94" alt="image" src="https://github.com/user-attachments/assets/f18f417f-6570-45b5-a6b9-b6cdcf760624" />
<img width="629" height="363" alt="image" src="https://github.com/user-attachments/assets/87fa3ea0-6396-431f-abfb-42e889022187" />
<img width="517" height="368" alt="image" src="https://github.com/user-attachments/assets/1e4d7215-16fd-4bfa-be25-6d00f3fe781b" />


使用圖1和圖2的私有資料，實作一個多項式抽象資料型態（ADT）Polynomial 類別


## 程式實作     

## 效能分析  

## 測試與驗證  

## 申論及開發報告  

### Problem2  
## 解題說明  
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

## 程式實作  
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
## 效能分析    
  一個 n 個元素的集合有 $2^n$ 個子集合  
  每次建立新的 subset 時，還需要複製原本的元素，因此最壞情況下需要額外的 $O(n)$  
  時間複雜度為 $O(n2^n)$  
  
  $n$ 個元素，因此儲存所有結果需要 $O(n2^n)$  
  遞迴本身會產生最多 $O(n)$ 的呼叫堆疊  
  空間複雜度為 $O(n2^n)$  

## 測試與驗證  
<img width="436" height="235" alt="image" src="https://github.com/user-attachments/assets/4c8d7e8f-e98a-4670-aae8-e261467e7cc4" />  
<img width="437" height="384" alt="image" src="https://github.com/user-attachments/assets/6ab3fb49-bc65-42a8-89de-34f6ccbc0928" />  

## 申論及開發報告  
使用遞迴方式產生集合的冪集  
先計算不包含目前元素的冪集，再將目前元素加入原本產生的每一個子集合，最後將兩個結果合併  
例如對集合 {1,2,3}  
先計算 $P$({1,2})  
將元素 3 加入原本的每一個子集合，就能得到所有包含3的子集合  
由於每增加一個元素，子集合的數量就會變成原本的兩倍，因此∣$P(S)$∣ = $2^n$  
