#ifndef defNlibs
#include "../defLibsDefs.hpp"
#endif

template <typename sgmType>
struct STV
{
    ll l, r;
    sgmType val;
    STV *L = 0, *R = 0;

    STV(ll l, ll r, STV *L = 0, STV *R = 0) : l(l), r(r), L(L), R(R)
    {
        val = sgmType();
    }
    STV(ll l, ll r, sgmType val, STV *L = 0, STV *R = 0) : l(l), r(r), val(val), L(L), R(R){};
};
#define SegmTreeV STV;

template <typename valS>
struct SgmTree
{
    STV<valS> *r;
    vector<valS> s;
    vector<function<void(STV<valS> *)>> preUpd; // функции вызывающиеся перед входом в след вершины вершины
    vector<function<void(STV<valS> *)>> aftUpd; // функции вызываются после входа
    function<void(STV<valS> *)> buildCH = [](STV<valS> *v)
    {
        v->L = new STV<valS>(v->l, (v->l + v->r) / 2);
        v->R = new STV<valS>((v->l + v->r) / 2 + 1, v->r);
    };

    void build(STV<valS> *v)
    {
        if (v->l == v->r)
        {
            v->val = s[v->l];
            return;
        }

        buildCH(v);
        build(v->L);
        build(v->R);

        for (auto f : aftUpd)
            f(v);
    }

    void upd(STV<valS> *v, ll l, ll r, function<void(STV<valS> *)> &updV)
    {
        if (v->l > l || v->r < r)
        {
            return;
        }
        if (v->l >= l && v->r <= r)
        {
            updV(v);
        }

        for (auto prCalc : preUpd)
            prCalc(v);
        upd(v->L, l, r, updV);
        upd(v->R, l, r, updV);
        for (auto rCalc : aftUpd)
            rCalc(v);
    }

    template <typename typeSm>
    typeSm sm(STV<valS> *v, ll l, ll r)
    {
        if (v->l > r || v->r < l)
            return typeSm();
        if (l <= v->l && v->r <= r)
            return typeSm(v->val);

        for (auto prCc : preUpd)
            prCc(v);
        return (typeSm(sm<typeSm>(v->L, l, r), sm<typeSm>(v->R, l, r)));
    }

    STV<valS> *findSgm(STV<valS> *v, function<bool(STV<valS> *e)> &goTo)
    {
        if (v == nullptr)
            return nullptr;
        for (auto prCc : preUpd)
            prCc(v);

        STV<valS> *f;
        if (goTo(v->L))
            f = findSgm(v->L, goTo);
        if (!f && goTo(v->R))
            f = findSgm(v->R, goTo);
        return f;
    }

    SgmTree(vector<valS> v,
            vector<function<void(STV<valS> *)>> preUpd = {},
            vector<function<void(STV<valS> *)>> aftUpd = {}) : s(v), preUpd(preUpd), aftUpd(aftUpd)
    {
        r = new STV<valS>(0, v.size() - 1);
        build(r);
    }
};

#define sgmTreeDef