#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 2e5, lgsz = 18, trsz = 5 * nsz * lgsz;
int n, rt = 1, ans[nsz + 5], pr[nsz + 5], mx[nsz + 5], rs[nsz + 5];
vector<int> g[nsz + 5];

struct treap {
    int sz, ls[trsz], rs[trsz], siz[trsz], key[trsz], val[trsz], cnt[trsz], sum[trsz];
    
    int inline node(int w, int cnt) {
        int u = ++sz;
        siz[u] = 1;
        val[u] = w;
        key[u] = rand();
        this->cnt[u] = sum[u] = cnt;
        return u;
    }
    
    void inline up(int u) {
        siz[u] = siz[ls[u]] + siz[rs[u]] + 1;
        sum[u] = sum[ls[u]] + sum[rs[u]] + cnt[u];
    }
    
    int merge(int v1, int v2) {
        if (!v1 || !v2)  return v1 | v2;
        if (key[v1] > key[v2]) {
            rs[v1] = merge(rs[v1], v2);
            up(v1);
            return v1;
        } else {
            ls[v2] = merge(v1, ls[v2]);
            up(v2);
            return v2;
        }
    }
    
    void split(int u, int w, int &v1, int &v2) {
        if (!u) {
            v1 = v2 = 0;
            return;
        }
        if (val[u] <= w) {
            v1 = u;
            split(rs[u], w, rs[u], v2);
        } else {
            v2 = u;
            split(ls[u], w, v1, ls[u]);
        }
        up(u);
    }
    
    void inline ins(int &rt, int w, int cnt) {
        int v1, v2;
        split(rt, w, v1, v2);
        rt = merge(merge(v1, node(w, cnt)), v2);
    }
    
    int inline qry(int &rt, int w) {
        int v1, v2, res;
        split(rt, w, v1, v2);
        res = sum[v1];
        rt = merge(v1, v2);
        return res;
    }
    
    int unite(int v1, int v2) {
        if (!v1 || !v2)  return v1 | v2;
        if (siz[v1] < siz[v2]) {
            swap(v1, v2);
        }
        v1 = unite(v1, ls[v2]);
        v1 = unite(v1, rs[v2]);
        int ls, rs, md;
        split(v1, val[v2] - 1, ls, md);
        split(md, val[v2], md, rs);
        if (md) {
            cnt[md] += cnt[v2];
            sum[md] += sum[v2];
        } else {
            ins(md, val[v2], cnt[v2]);
        }
        return merge(merge(ls, md), rs);
    }
};
treap tr;

void dfs(int u = rt) {
    loop (i, g[u].size()) {
        int v = g[u][i];
        if (v == pr[u])  continue;
        pr[v] = u;
        mx[v] = max(mx[u], u);
        dfs(v);
        rs[u] = tr.unite(rs[u], rs[v]);
    }
    if (u == rt)  return;
    tr.ins(rs[u], 0, 1);
    if (u > mx[pr[u]]) {
        ans[u] = tr.qry(rs[u], mx[u]);
    } else {
        if (pr[u] < mx[pr[u]]) {
            ans[u] = 0;
        } else {
            ans[u] = tr.qry(rs[u], mx[u]) - tr.qry(rs[u], mx[pr[u]]);
        }
    }
    int v1, v2;
    tr.split(rs[u], u - 1, v1, v2);
    rs[u] = tr.merge(tr.node(u, tr.sum[v1]), v2);
}

void pre(int u = rt) {
    loop (i, g[u].size()) {
        int v = g[u][i];
        if (v == pr[u])  continue;
        ans[v] += ans[u];
        pre(v);
    }
}

int main() {
    scanf("%d", &n);
    cont (i, n - 1) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs();
    pre();
    circ (u, 2, n) {
        printf("%d ", ans[u]);
    }
}