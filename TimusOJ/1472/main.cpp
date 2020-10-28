#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e5, inf = 0x3f3f3f3f;
int n, rt = 1, dp[nsz + 5][2];

struct graph {
	int sz, hd[nsz + 5];
	
	struct edge {
		int nxt, to, w;
		
		edge() {}
		edge(int nxt, int to, int w) {
			this->nxt = nxt, this->to = to, this->w = w;
		}
	} e[nsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v, int w) {
		e[++sz] = edge(hd[u], v, w), hd[u] = sz;
	}
};
graph g;

void dfs(int u = rt) {
	bool f = 0;
	dp[u][0] = 0, dp[u][1] = 0;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to, w = g[i].w;
		dfs(v);
		dp[u][0] += dp[v][0];
		dp[u][1] += min(dp[v][0] + w, dp[v][1]);
		f = 1;
	}
	if (!f) dp[u][1] = inf;
}

int main() {
	scanf("%d", &n);
	circ (u, 2, n) {
		int p, w;
		scanf("%d%d", &p, &w);
		g.link(p, u, w);
	}
	dfs();
	printf("%d.00\n", dp[rt][1]);
}