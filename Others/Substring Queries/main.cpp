#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e5, masz = 2 * nsz, alpsz = 26;
int n, q, ans[nsz + 5];
string s[nsz + 5];

struct suffix_automaton {
    int sz, rt, lst, pr[masz + 5], len[masz + 5], g[masz + 5][alpsz + 5];

    int inline node() {
        int u = ++sz;
        pr[u] = len[u] = 0, memset(g[u], 0, sizeof(g[u]));
        return u;
    }

    void inline ins(char ch) {
        int c = ch - 'a', p = lst, u = lst = node();
        len[u] = len[p] + 1;
        for (; p && !g[p][c]; g[p][c] = u, p = pr[p]);
        int q = g[p][c];
        if (!q) pr[u] = rt;
        else if (len[p] + 1 == len[q]) pr[u] = q;
        else {
            int v = node();
            len[v] = len[p] + 1, pr[v] = pr[q], memcpy(g[v], g[q], sizeof(g[q]));
            pr[u] = pr[q] = v;
            for (; p && g[p][c] == q; g[p][c] = v, p = pr[p]);
        }
    }

    void inline init(const string &s) {
        sz = 0, rt = lst = node();
        loop (i, s.size()) ins(s[i]);
    }

    int inline qry(const string &s) {
        int u = rt, cur = 0, res = 0;
        loop (i, s.size()) {
            int c = s[i] - 'a';
            for (; u && !g[u][c]; u = pr[u], cur = min(cur, len[u]));
            if (u) u = g[u][c], cur = min(len[u], cur + 1);
            else u = rt, cur = 0;
            res = max(res, cur);
        }
        return res;
    }
};
suffix_automaton ma;

struct query {
    int u, v, id;

    query() {}
    query(int u, int v, int id): u(u), v(v), id(id) {}

    bool inline operator < (const query &b) const { return u != b.u ? u < b.u : v < b.v; }
};
query b[nsz + 5];

bool inline compare(int u, int v) {
    return s[u].size() != s[v].size() ? s[u].size() < s[v].size() : u > v;
}

void inline solve() {
    sort(b + 1, b + q + 1);
    for (int i = 1, j, k; i <= q; i = j) {
        int u = b[i].u;
        ma.init(s[u]);
        for (j = i; j <= q && b[j].u == u; j = k) {
            int v = b[j].v, cur = ma.qry(s[v]);
            for (k = j; k <= q && b[k].u == u && b[k].v == v; ++k) ans[b[k].id] = cur;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> q;
    cont (i, n) cin >> s[i];
    cont (i, q) {
        int u, v;
        cin >> u >> v;
        u += 1, v += 1;
        if (compare(u, v)) swap(u, v);
        b[i] = query(u, v, i);
    }
    solve();
    cont (i, q) printf("%d\n", ans[i]);
}