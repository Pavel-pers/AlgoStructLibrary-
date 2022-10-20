#include "defLibsDefs.h"

using namespace std;

struct Val2Ind
{
    vector<ll> ind;

    void build()
    {
        sort(all(ind));
        ind.resize(unique(all(ind)) - ind.begin());
    }
    void add(ll x)
    {
        ind.push_back(x);
    }

    ll size()
    {
        return ind.size();
    }
    ll i(ll v)
    {
        return upper_bound(all(ind), v) - ind.begin() - 1;
    }

    Val2Ind() = default;
    Val2Ind(vector<ll> s) : ind(s)
    {
        build();
    }
};
