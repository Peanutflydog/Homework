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