#include "defLibsDefs.h"

using namespace std;

template <typename T>
struct sparseTable
{
    vector<T> v;
    vector<vector<T>> bnC;
    function<T(T, T)> func;

    void build()
    {
        bnC.resize(32, vector<T>(v.size()));
        bnC[0] = v;
        for (int i = 1; i < 32; i++)
        {
            for (int j = 0; j < v.size(); j++)
            {
                bnC[i][j] = func(bnC[i - 1][j], bnC[i - 1][min(j + (1 << (i - 1)), int(v.size()) - 1)]);
            }
        }
    }

    T calcOnSgm(ll l, ll r)
    {
        ll mxP = 0;
        for (; mxP < 32 && (r - l + 1) <= (1 << mxP); mxP++)
        {
        }
        return func(bnC[mxP][l], bnC[mxP][r - (1 << mxP) + 1]);
    }

    sparseTable(vector<T> v, function<T(T, T)> mult) : v(v), func(mult)
    {
        build();
    }
};
