#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 50;

struct graph {
	int sz, hd[nsz + 5];
	
	struct edge {
		int nxt, to;
		
		edge() {}
		edge(int nxt, int to) {
			this->nxt = nxt, this->to = to;
		}
	} e[nsz * nsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v) {
		e[++sz] = edge(hd[u], v), hd[u] = sz;
	}
};

struct TheTips {
	int n;
	double p[nsz + 5], ans;
	graph g;
	
	vector<int> inline bfs(int s) {
		static bool vis[nsz + 5];
		static int q[nsz + 5];
		int ql = 0, qr = 0;
		vector<int> nd;
		memset(vis, 0, sizeof(vis));
		for (q[qr++] = s, vis[s] = 1; ql != qr;) {
			int u = q[ql++];
			nd.push_back(u);
			for (int i = g.hd[u]; i; i = g[i].nxt) {
				int v = g[i].to;
				if (!vis[v]) q[qr++] = v, vis[v] = 1;
			}
		}
		return nd;
	}
	
	double solve(vector<string> go, vector<int> percent) {
		n = int(percent.size());
		loop (i, n) loop (j, n) if (go[i][j] == 'Y') g.link(j + 1, i + 1);
		loop (i, n) p[i + 1] = percent[i] / 100.0;
		cont (u, n) {
			vector<int> nd = bfs(u);
			double cur = 1;
			loop (i, nd.size()) {
				int v = nd[i];
				cur *= 1 - p[v];
			}
			ans += 1 - cur;
		}
		return ans;
	}
};