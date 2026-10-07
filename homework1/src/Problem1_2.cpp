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