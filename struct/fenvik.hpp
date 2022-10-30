template <typename FenvV>
struct Fenvik
{
    ll sz;
    vector<FenvV> tr;

    void mod(ll i, function<void(FenvV *)> md)
    {
        for (; i < tr.size(); i |= (i + 1))
            md(&tr[i]);
    }

    template <typename tSm>
    tSm sum(ll r, function<tSm(FenvV *a, tSm *s)> sum, tSm dflt = tSm())
    {
        tSm ans = dflt;

        for (; r >= 0; r &= (r + 1), r--)
            ans = sum(&tr[r], &ans);

        return ans;
    }

    Fenvik() = default;
    Fenvik(ll sz, FenvV v = FenvV())
    {
        tr.assign(sz, v);
    }
};


#define FenvikDecl