#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 2e5, inf = 0x3f3f3f3f;
int n, rt = 1, dp[nsz + 5], sum[nsz + 5], res[nsz + 5], ans;

struct graph {
	int sz, hd[nsz + 5];
	
	struct edge {
		int nxt, to, w;
		
		edge() {}
		edge(int nxt, int to, int w): nxt(nxt), to(to), w(w) {}
	} e[2 * nsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v, int w) {
		e[++sz] = edge(hd[u], v, w), hd[u] = sz;
		e[++sz] = edge(hd[v], u, w), hd[v] = sz;
	}
};
graph g;

struct functor {
	pair<int, int> mx[2];
	
	functor() {
		mx[0] = mx[1] = make_pair(-inf, -1);
	}
	
	void inline ins(int w, int id) {
		if (w > mx[0].first) mx[1] = mx[0], mx[0] = make_pair(w, id);
		else if (w > mx[1].first) mx[1] = make_pair(w, id);
	}
	
	int inline qry(int id = 0) {
		if (mx[0].second != id) return mx[0].first;
		return mx[1].first;
	}
};
functor f[nsz + 5];

void dfs(int u = rt, int p = -1) {
	dp[u] = 0;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to, w = g[i].w;
		if (v == p) continue;
		dfs(v, u);
		int cur = max(dp[v], dp[v] + f[v].qry() + w);
		dp[u] += cur;
		f[u].ins(dp[v] + w - cur, v);
	}
}

void solve(int u = rt, int p = -1) {
	res[u] = dp[u];
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to, w = g[i].w;
		if (v == p) continue;
		dp[u] = res[u] - max(dp[v], dp[v] + f[v].qry() + w);
		int cur = max(dp[u], dp[u] + f[u].qry(v) + w);
		f[v].ins(dp[u] + w - cur, u);
		dp[v] += cur;
		solve(v, u);
	}
}

int main() {
	scanf("%d", &n);
	cont (i, n - 1) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		g.link(u, v, w);
	}
	dfs(), solve();
	cont (u, n) ans = max(ans, res[u]);
	printf("%d\n", ans);
}