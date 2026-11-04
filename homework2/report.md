# 41143142
### Problem1  
## 解題說明  
<img width="517" height="94" alt="image" src="https://github.com/user-attachments/assets/f18f417f-6570-45b5-a6b9-b6cdcf760624" />
<img width="629" height="363" alt="image" src="https://github.com/user-attachments/assets/87fa3ea0-6396-431f-abfb-42e889022187" />
<img width="517" height="368" alt="image" src="https://github.com/user-attachments/assets/1e4d7215-16fd-4bfa-be25-6d00f3fe781b" />


使用圖1和圖2的私有資料，實作一個多項式抽象資料型態（ADT）Polynomial 類別  

建構子 $Polynomial()$：將 terms 初始化為 0，capacity 初始化為基本大小 10，並動態配置 termArray，此時代表多項式 p(x) = 0  

多項式加法 $Add$：利用雙指標兩個多項式的 termArray  
• 若指數相同：係數相加，若相加後不為 0 則加入結果，雙指標同時後移  
• 若指數不同：將指數較大者優先加入結果，該指標後移  

多項式乘法 $Mult$：外層迴圈走訪第一個多項式的每一項，內層迴圈走訪第二個多項式的每一項，將兩項相乘（係數相乘、指數相加）。每一次乘出來的新單項，皆透過一個輔助函式（如 NewTerm）插入至結果多項式中。若指數已存在則合併係數，若不存在則保持降冪排序插入  

多項式求值 $Eval$：利用 Horner's Method 或直接走訪法，將變數 f 代入多項式的每一項中，計算並累加所有項的數值結果



## 程式實作     
```cpp
#include <iostream>
#include <cmath>

using namespace std;

class Polynomial;

class Term {
    friend class Polynomial;
private:
    float coef;
    int exp;
};

class Polynomial {
public:
    Polynomial() {
        capacity = 10;
        terms = 0;
        termArray = new Term[capacity];
    }

    ~Polynomial() {
        delete termArray;
    }

    Polynomial(const Polynomial& poly) {
        capacity = poly.capacity;
        terms = poly.terms;
        termArray = new Term[capacity];
        for (int i = 0; i < terms; i++) {
            termArray[i] = poly.termArray[i];
        }
    }

    Polynomial& operator=(const Polynomial& poly) {
        if (this != &poly) {
            delete termArray;
            capacity = poly.capacity;
            terms = poly.terms;
            termArray = new Term[capacity];
            for (int i = 0; i < terms; i++) {
                termArray[i] = poly.termArray[i];
            }
        }
        return *this;
    }

    void NewTerm(float c, int e) {
        if (c == 0) return;
        for (int i = 0; i < terms; i++) {
            if (termArray[i].exp == e) {
                termArray[i].coef += c;
                if (termArray[i].coef == 0) {
                    for (int j = i; j < terms - 1; j++) {
                        termArray[j] = termArray[j + 1];
                    }
                    terms--;
                }
                return;
            }
        }
        if (terms >= capacity) {
            capacity *= 2;
            Term* newArray = new Term[capacity];
            for (int i = 0; i < terms; i++) {
                newArray[i] = termArray[i];
            }
            delete termArray;
            termArray = newArray;
        }
        int i = terms - 1;
        while (i >= 0 && termArray[i].exp < e) {
            if (i + 1 < capacity) {
                termArray[i + 1] = termArray[i];
            }
            i--;
        }
        if (i + 1 < capacity) {
            termArray[i + 1].coef = c;
            termArray[i + 1].exp = e;
            terms++;
        }
    }

    Polynomial Add(Polynomial poly) {
        Polynomial c;
        int aPos = 0, bPos = 0;
        while (aPos < terms && bPos < poly.terms) {
            if (termArray[aPos].exp == poly.termArray[bPos].exp) {
                float sum = termArray[aPos].coef + poly.termArray[bPos].coef;
                if (sum != 0) c.NewTerm(sum, termArray[aPos].exp);
                aPos++;
                bPos++;
            }
            else if (termArray[aPos].exp < poly.termArray[bPos].exp) {
                c.NewTerm(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
                bPos++;
            }
            else {
                c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
                aPos++;
            }
        }
        for (; aPos < terms; aPos++) c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
        for (; bPos < poly.terms; bPos++) c.NewTerm(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
        return c;
    }

    Polynomial Mult(Polynomial poly) {
        Polynomial result;
        for (int i = 0; i < terms; i++) {
            for (int j = 0; j < poly.terms; j++) {
                result.NewTerm(termArray[i].coef * poly.termArray[j].coef, termArray[i].exp + poly.termArray[j].exp);
            }
        }
        return result;
    }

    float Eval(float f) {
        float result = 0;
        for (int i = 0; i < terms; i++) {
            result += termArray[i].coef * static_cast<float>(pow(f, termArray[i].exp));
        }
        return result;
    }

    void Print() {
        if (terms == 0) {
            cout << "0" << endl;
            return;
        }
        for (int i = 0; i < terms; i++) {
            float c = termArray[i].coef;
            int e = termArray[i].exp;
            if (i > 0 && c > 0) cout << " + ";
            else if (c < 0) {
                if (i == 0) cout << "-";
                else cout << " - ";
                c = -c;
            }
            if (c != 1 || e == 0) cout << c;
            if (e > 0) {
                cout << "x";
                if (e > 1) cout << "^" << e;
            }
        }
        cout << endl;
    }

private:
    Term* termArray;
    int capacity;
    int terms;
};

int main() {
    Polynomial p1, p2;
    int count;
    float c;
    int e;

    cout << "請輸入多項式 1 的總項數: ";
    cin >> count;
    for (int i = 0; i < count; i++) {
        cout << "請輸入第 " << i + 1 << " 項的 [係數] 與 [指數] (空格隔開): ";
        cin >> c >> e;
        p1.NewTerm(c, e);
    }
    cout << "多項式 1 建立完成: ";
    p1.Print();
    cout << endl;

    cout << "請輸入多項式 2 的總項數: ";
    cin >> count;
    for (int i = 0; i < count; i++) {
        cout << "請輸入第 " << i + 1 << " 項的 [係數] 與 [指數] (空格隔開): ";
        cin >> c >> e;
        p2.NewTerm(c, e);
    }
    cout << "多項式 2 建立完成: ";
    p2.Print();
    cout << endl;

    Polynomial pAdd = p1.Add(p2);
    cout << "加法結果 (p1 + p2): ";
    pAdd.Print();

    Polynomial pMult = p1.Mult(p2);
    cout << "乘法結果 (p1 * p2): ";
    pMult.Print();

    float target;
    cout << endl << "請輸入代入多項式的 x 值: ";
    cin >> target;
    cout << "p1(" << target << ") = " << p1.Eval(target) << endl;

    return 0;
}

```
## 效能分析  
• 設多項式 $A(x)$ 的非零項數為 $m$ 即 $A$.terms = $m$。  
• 設多項式 $B(x)$ 的非零項數為 $n$ 即 $B$.terms = $n$。  


(1) 多項式加法 (Add)  

加法運算採用雙指標技術同步走訪兩個多項式的 termArray  
在每一輪比較中，至少會有一個指標往後移動一格  
while 迴圈的最大執行次數為兩個多項式項數之和  
時間複雜度為線性等級的 $O(m + n)$  

加法結果所產生的新多項式，其非零項數最多為兩多項式的項數總和
因此 termArray 最多需要配置 $m + n$ 個 Term 的空間。

(2) 多項式乘法 (Mult)  

將 $A(x)$ 的每一項與 $B(x)$ 的每一項相乘，共產生 $m · n$ 個乘積單項  
每計算出一個新單項，皆須呼叫 NewTerm 函式將其插入結果多項式中  
NewTerm 內部走訪並移動陣列元素的成本與當前結果多項式的項數成正比  
當前項數最高可達 $m · n$，因此每次插入花費 $m · n$，時間複雜度為 $O((m · n)^2)$  

相乘後最大可能項數為 $m · n$，因此動態陣列容量會自動擴充至能容納 $m · n$ 個 Term 結構。  

(3) 多項式求值 (Eval)  

使用單一迴圈所有非零項共 $m$ 次，並呼叫 pow 函數計算特定 $x$ 值的冪次後與係數相乘  
迴圈執行次數與非零項數成線性正比，時間複雜度為 $O(m)$

過程中僅使用一個累加變數 result 來儲存最終數值
空間複雜度為 $O(1)$

  
## 測試與驗證  
<img width="731" height="346" alt="image" src="https://github.com/user-attachments/assets/ac8eeed3-0a4e-46b8-8598-4953f7a42e2b" />


## 申論及開發報告  

本題核心為不使用 C++ 標準樣板函式庫，手動實作一個多項式 ADT。
Polynomial 類別內含有指向動態配置記憶體的指標成員 Term *termArray，在物件導向中，如果沒有定義複製建構子與賦值運算子重載，編譯器預設的淺複製將導致多個物件的指標指向同一個Heap記憶體位址
會使物件週期結束、呼叫解構子時，引發二次釋放崩潰

在加法的雙指標中，處理「同類項相消（係數和為 0）」，程式碼必須能夠在運行期將該 Term 移出陣列，並將後方元素前移，同時調降 terms 計數，完成對稀疏多項式的空間最佳化
在乘法中，透過 NewTerm 的二元決策，讓程式在逆序輸入時也能動態維持降冪排序

### Problem2  
## 解題說明  
​
撰寫 C++ 函式以達成多項式的輸入與輸出，並應該重載 << 與 >> 串流運算子來實作  

輸入運算子 $>>$ ：設計上先讀入使用者欲輸入的「非零項總數」，隨後利用迴圈依序讀入每項的 [係數] 與 [指數]。每讀入一項就呼叫內部的新增函式，確保即便使用者輸入時沒有按照順序，程式內部也能自動完成降冪排序與同類項合併  

輸出運算子 $<<$ ：為了讓多項式以人類易讀的漂亮格式印出，輸出時必須逐項檢查並處理多個邊界條件：  
• 正負號連接：除了第一項外，正數前面要補上 +，負數則轉為 - 連接。
• 係數省略：當係數為 1 且指數不為 0 時，應省略不印出 1。
• 未知數與指數：指數為 0 時不印出 x；指數為 1 時僅印出 x 而不印出 ^1；指數大於 1 時才印出 x^e。
• 零多項式：若多項式完全沒有任何非零項，則直接輸出 0。

## 程式實作  
 
## 效能分析    

(1) 輸入運算子 $>>$

外層迴圈會依據使用者指定的項數執行 $k$ 次。每次讀入一項數據後，會呼叫 NewTerm 函式將其插入多項式中。為了維持降冪排序與同類項合併，NewTerm 必須走訪當前已插入的項目平均長度為 $k/2$  
因此時間複雜度以二次方成長，為 $O(k^2)$  
動態陣列需要配置足夠的空間來儲存這 $k$ 個輸入項目，額外記憶體開銷與輸入項數成線性正比  

(2) 輸出運算子 (<<)  

輸出運算僅需使用單一迴圈，從頭到尾遍歷一次長度為 $m$ 的 termArray，並依據內部各項的係數與指數進行條件判斷與字串格式化輸出  
與多項式項數成線性正比，時間複雜度為 $O(m)$  
輸出串流直接將格式化後的文字寫入標準輸出物件，沒有額外動態配置任何陣列或記憶體緩衝區，空間複雜度為 $O(1)$

## 測試與驗證  
<img width="475" height="298" alt="image" src="https://github.com/user-attachments/assets/60e210fa-d0fd-4e1e-ab92-8298c70f5b06" />
<img width="432" height="277" alt="image" src="https://github.com/user-attachments/assets/d326e558-436d-4a1b-9cbd-445afc75dbab" />

## 申論及開發報告  

透過重載 << 與 >> 串流運算子，提升了自訂類別與標準輸入輸出的整合度  
由於 operator<< 與 operator>> 是全域非成員函式，在存取私有變數時引發了編譯器專屬保護錯誤（C2248)  
由於這兩個運算子必須同時讀取 Polynomial 的管理變數與其內部動態陣列物件 Term 的私有內容（coef, exp），因此必須在 Term 與 Polynomial 兩個類別內部同時宣告其為 friend  
