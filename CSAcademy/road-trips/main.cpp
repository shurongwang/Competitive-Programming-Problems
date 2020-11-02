#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e5, ksz = 18, msksz = (1 << ksz) - 1;
const num inf = 0x3f3f3f3f3f3f3f3f;
int n, m, k, full, a[nsz + 5];
int rt = 1, pr[nsz + 5], dep[nsz + 5], siz[nsz + 5], hs[nsz + 5], top[nsz + 5], dfn[nsz + 5], fm[nsz + 5];
num len[nsz + 5], dp[msksz + 5][ksz + 5], ans;
vector<int> lf;

struct graph {
	int sz, hd[nsz + 5];
	
	struct edge {
		int nxt, to, w;
		
		edge() {}
		edge(int nxt, int to, int w) {
			this->nxt = nxt, this->to = to, this->w = w;
		}
	} e[2 * nsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v, int w) {
		e[++sz] = edge(hd[u], v, w), hd[u] = sz;
		e[++sz] = edge(hd[v], u, w), hd[v] = sz;
	}
};
graph g;

void dfs1(int u = rt) {
	siz[u] = 1;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to, w = g[i].w;
		if (v == pr[u]) continue;
		pr[v] = u, dep[v] = dep[u] + 1, len[v] = len[u] + w;
		dfs1(v);
		siz[u] += siz[v];
		if (siz[hs[u]] < siz[v]) hs[u] = v;
	}
}

void dfs2(int u = rt, int tp = rt) {
	static int t;
	dfn[u] = ++t, fm[t] = u, top[u] = tp;
	if (!hs[u]) return (void) (lf.push_back(u));
	dfs2(hs[u], tp);
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (v == pr[u] || v == hs[u]) continue;
		dfs2(v, v);
	}
}

int inline lca(int u, int v) {
	for (; top[u] != top[v]; v = pr[top[v]]) {
		if (dep[top[u]] > dep[top[v]]) swap(u, v);
	}
	if (dep[u] > dep[v]) swap(u, v);
	return u;
}

num inline dis(int u, int v) {
	return len[u] + len[v] - 2 * len[lca(u, v)];
}

void inline upd(num &a, num b) {
	if (a < b) a = b;
}

void inline solve() {
	sort(a, a + m);
	dfs1(), dfs2();
	k = int(lf.size()), full = (1 << k) - 1;
	memset(dp, -inf, sizeof(dp));
	dp[0][0] = 0;
	circ (S, 0, full) {
		vector<int> leaf;
		loop (i, k) if (S >> i & 1) leaf.push_back(dfn[lf[i]]);
		loop (c, m) {
			num val = dp[S][c], w = a[c];
			if (val < 0) continue;
			loop (i, k) {
				if (S >> i & 1) { upd(dp[S][c + 1], val); continue; }
				int t = dfn[lf[i]], u = lf[i];
				if (!leaf.size()) {
					upd(dp[S | (1 << i)][c + 1], val + w * len[u]);
				} else {
					int id = lower_bound(all(leaf), t) - leaf.begin();
					int pre = id == 0 ? rt : fm[leaf[id - 1]];
					int nxt = id == leaf.size() ? rt : fm[leaf[id]];
					int p1 = lca(pre, u), p2 = lca(u, nxt), p = dep[p1] > dep[p2] ? p1 : p2;
					upd(dp[S | (1 << i)][c + 1], val + w * (len[u] - len[p]));
				}
			}
		}
		upd(ans, dp[S][m]);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	loop (i, m) scanf("%d", &a[i]);
	cont (i, n - 1) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		g.link(u, v, w);
	}
	solve();
	printf("%lld\n", ans);
}