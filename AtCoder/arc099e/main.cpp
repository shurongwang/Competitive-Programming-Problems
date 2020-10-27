#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 7e2, egsz = nsz * (nsz - 1) / 2;
const int inf = 0x3f3f3f3f;
bool vis[nsz + 5];
int n, m, b[nsz + 5][nsz + 5], c[nsz + 5], ans = inf;
bitset<nsz + 1> dp;

struct graph {
	int sz, hd[nsz + 5];
	
	struct edge {
		int nxt, to;
		
		edge() {}
		edge(int nxt, int to) {
			this->nxt = nxt, this->to = to;
		}
	} e[egsz * 2 + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v) {
		e[++sz] = edge(hd[u], v), hd[u] = sz;
		e[++sz] = edge(hd[v], u), hd[v] = sz;
	}
};
graph g;

bool dfs(int u, int &s0, int &s1, int cur = 0) {
	if (vis[u]) return c[u] == cur;
	c[u] = cur, vis[u] = 1;
	(cur ? s1 : s0) += 1;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (!dfs(v, s0, s1, cur ^ 1)) return 0;
	}
	return 1;
}

int main() {
	scanf("%d%d", &n, &m);
	cont (i, m) {
		int u, v;
		scanf("%d%d", &u, &v);
		b[u][v] = b[v][u] = 1;
	}
	cont (u, n) circ (v, u + 1, n) if (!b[u][v]) g.link(u, v);
	dp[0] = 1;
	cont (u, n) if (!vis[u]) {
		int s0 = 0, s1 = 0;
		if (!dfs(u, s0, s1)) { printf("-1\n"); return 0; }
		dp = (dp << s1) | (dp << s0);
	}
	circ (k1, 0, n) if (dp[k1]) {
		int k2 = n - k1;
		ans = min(ans, (k1 * (k1 - 1) + k2 * (k2 - 1)) / 2);
	}
	printf("%d\n", ans);
}