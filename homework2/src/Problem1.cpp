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
