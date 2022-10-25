#include "../defLibsDefs.hpp"

using namespace std;

template <typename valStr>
struct sparseTable
{
    vector<valStr> v;
    vector<vector<valStr>> bnC;
    function<valStr(valStr, valStr)> func;

    void build()
    {
        bnC.resize(32, vector<valStr>(v.size()));
        bnC[0] = v;
        for (int i = 1; i < 32; i++)
        {
            for (int j = 0; j < v.size(); j++)
            {
                bnC[i][j] = func(bnC[i - 1][j], bnC[i - 1][min(j + (1 << (i - 1)), int(v.size()) - 1)]);
            }
        }
    }

    valStr calcOnSgm(ll l, ll r)
    {
        ll mxP = 0;
        for (; mxP < 32 && (r - l + 1) <= (1 << mxP); mxP++)
        {
        }
        return func(bnC[mxP][l], bnC[mxP][r - (1 << mxP) + 1]);
    }

    sparseTable(vector<valStr> v, function<valStr(valStr, valStr)> mult) : v(v), func(mult)
    {
        build();
    }
};