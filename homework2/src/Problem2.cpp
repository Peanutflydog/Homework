#include <iostream>
#include <cmath>

using namespace std;

class Polynomial;

class Term {
    friend class Polynomial;
    friend ostream& operator<<(ostream& os, const Polynomial& poly);
    friend istream& operator>>(istream& is, Polynomial& poly);
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
        delete[] termArray;
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
            delete[] termArray;
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
            delete[] termArray;
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

    friend ostream& operator<<(ostream& os, const Polynomial& poly);
    friend istream& operator>>(istream& is, Polynomial& poly);

private:
    Term* termArray;
    int capacity;
    int terms;
};

ostream& operator<<(ostream& os, const Polynomial& poly) {
    if (poly.terms == 0) {
        os << "0";
        return os;
    }
    for (int i = 0; i < poly.terms; i++) {
        float c = poly.termArray[i].coef;
        int e = poly.termArray[i].exp;
        if (i > 0 && c > 0) os << " + ";
        else if (c < 0) {
            if (i == 0) os << "-";
            else os << " - ";
            c = -c;
        }
        if (c != 1 || e == 0) os << c;
        if (e > 0) {
            os << "x";
            if (e > 1) os << "^" << e;
        }
    }
    return os;
}

istream& operator>>(istream& is, Polynomial& poly) {
    int numTerms;
    if (!(is >> numTerms)) return is;
    poly.terms = 0;
    for (int i = 0; i < numTerms; i++) {
        float c;
        int e;
        is >> c >> e;
        poly.NewTerm(c, e);
    }
    return is;
}

int main() {
    Polynomial p1, p2;

    cout << "使用 >> 輸入多項式 1 " << endl;
    cin >> p1;
    cout << "使用 << 輸出多項式 1: " << p1 << endl << endl;

    cout << "使用 >> 輸入多項式 2 " << endl;
    cin >> p2;
    cout << "使用 << 輸出多項式 2: " << p2 << endl << endl;

    Polynomial pAdd = p1.Add(p2);
    cout << "加法運算結果 (p1 + p2): " << pAdd << endl;

    Polynomial pMult = p1.Mult(p2);
    cout << "乘法運算結果 (p1 * p2): " << pMult << endl;

    return 0;
}
