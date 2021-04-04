#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e3, alpsz = 26, inf = 0x3f3f3f3f;
bool g[nsz + 5][nsz + 5], vis[nsz + 5][nsz + 5];
int n, m, ans = inf, dis[nsz + 5][nsz + 5];
vector<int> to[nsz + 5][alpsz];

struct node {
	int d, u, v;
	
	node() {}
	node(int d, int u, int v): d(d), u(u), v(v) {}
	
	bool inline operator < (const node &b) const { return d > b.d; }
};

void inline solve() {
	memset(dis, inf, sizeof(dis));
	priority_queue<node> q;
	q.push(node(dis[1][n] = 0, 1, n));
	for (; q.size();) {
		node cur = q.top(); q.pop();
		int u = cur.u, v = cur.v;
		vis[u][v] = vis[v][u] = 1;
		loop (c, alpsz) {
			loop (i, to[u][c].size()) loop (j, to[v][c].size()) {
				int nu = to[u][c][i], nv = to[v][c][j];
				if (nu > nv) swap(nu, nv);
				if (!vis[nu][nv] && dis[nu][nv] > dis[u][v] + 2) {
					q.push(node(dis[nu][nv] = dis[u][v] + 2, nu, nv));
				}
			}
		}
	}
	cont (u, n) cont (v, n) {
		if (u == v) ans = min(ans, dis[u][v]);
		if (g[u][v]) ans = min(ans, dis[u][v] + 1);
	}
	ans = ans == inf ? -1 : ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin >> n >> m;
	cont (i, m) {
		char c;
		int u, v;
		cin >> u >> v >> c;
		c -= 'a';
		g[u][v] = g[v][u] = 1;
		to[u][c].push_back(v);
		to[v][c].push_back(u);
	}
	solve();
	printf("%d\n", ans);
}