# Problem1  
## 1. 解題說明  
Ackermann's funtion $A(m,n)$ 定義如下：  
<img width="636" height="132" alt="image" src="https://github.com/user-attachments/assets/0b1e7100-7286-481c-9ef3-5c1284d3f223" />  
Ackermann 函數是一個成長速度非常快的遞迴函數，即使輸入值不大，也會產生非常大量的函式呼叫。  
**1. 撰寫一個遞迴函式計算 Ackermann 函數**  

  如果 m=0，回傳 n+1  
  如果 n=0，計算 $A(m-1,1)$  
  其他情況，計算 $A(m−1,A(m,n−1))$  
  
**2. 撰寫一個非遞迴演算法計算 Ackermann 函數**  

Ackermann's funtion本身有巢狀遞迴  
$A(m−1,A(m,n−1))$  
使用堆疊呼叫函式，利用LIFO特性，保存還未計算的m  
## 2. 程式實作
