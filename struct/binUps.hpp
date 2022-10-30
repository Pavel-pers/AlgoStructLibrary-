#ifndef defNlibs
#include "../defLibsDefs.hpp"
#endif
template <typename E>
struct BinUps
{
    function<E(E, E)> sum;
    vector<vector<pair<ll, E>>> ejV;
    vector<vector<pair<ll, E>>> binU;
    ll mxLn = 32;

    void build()
    {
        for (int v = 0; v < ejV.size(); v++)
        {
            for (pair<ll, E> u : ejV[v])
            {
                binU[0][u.first] = {v, u.second};
            }
        }

        for (int i = 1; i < mxLn; i++)
        {
            for (int v = 0; v < ejV.size(); v++)
            {
                binU[i][v] = {binU[i - 1][binU[i - 1][v].first].first, sum(binU[i - 1][binU[i - 1][v].first].second, binU[i - 1][v].second)};
            }
        }
    }

    pair<ll, E> upOnK(ll v, ll k, ll l = 30)
    {
        l = min(l, mxLn);
        for (; l >= 0; l--)
        {
            if (k > (1LL << l))
            {
                pair<ll, E> prevE = upOnK(binU[l][v].first, k - (1LL << l), l - 1);
                return {prevE.first,
                        sum(prevE.second, binU[l][v].second)};
            }
            if ((1LL << l) == k)
            {
                return {binU[l][v]};
            }
        }
    }

    BinUps(vector<vector<pair<ll, E>>> ej, function<E(E, E)> sum, ll mxLn = 29) : ejV(ej), sum(sum), mxLn(mxLn)
    {
        binU.resize(1 + mxLn, vector<pair<ll, E>>(ej.size()));
        build();
    }
};

#define binUpsDef