#include <iostream>
#include <vector>
using namespace std;

const int N = 40; // constant size of the array (replaced #define)

// inline function to compute sum of vector elements
inline void sum(int& p, int n, const vector<int>& d)
{
    p = 0; // initialize accumulator to 0

    // loop through all elements and add them
    for (int i = 0; i < n; ++i)
        p += d[i];
}

int main()
{
    int accum = 0; // variable to store final sum

    vector<int> data(N); // vector of size N

    // initialize vector with values 0 to N-1
    for (int i = 0; i < N; ++i)
        data[i] = i;

    // compute sum of vector elements
    sum(accum, N, data);

    // output result using C++ IO
    cout << "sum is " << accum << endl;

    return 0;
}