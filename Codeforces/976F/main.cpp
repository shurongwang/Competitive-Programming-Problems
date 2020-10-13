#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 4e3, ndsz = 2 * nsz + 2, egsz = ndsz * 2 + nsz;
const int inf = 0x3f3f3f3f;
int n1, n2, m, deg[nsz + 5], min_deg = inf;
int src, snk, sz, d[nsz + 5], cur[nsz + 5], nd[nsz + 5][2];
pair<int, int> e[nsz + 5];
vector< vector<int> > ans;

struct graph {
	int sz, hd[nsz + 5];
	
	struct edge {
		int nxt, to, f, id;
		
		edge() {}
		edge(int nxt, int to, int f) {
			this->nxt = nxt, this->to = to, this->f = f;
		}
	} e[2 * egsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v, int f) {
		e[++sz] = edge(hd[u], v, f), hd[u] = sz;
		e[++sz] = edge(hd[v], u, 0), hd[v] = sz;
	}
};
graph g;

int inline rev(int id) { return id & 1 ? ++id : --id; }

bool inline bfs() {
	static int q[nsz + 5];
	int ql = 0, qr = 0;
	cont (u, sz) cur[u] = g.hd[u], d[u] = -1;
	q[qr++] = src, d[src] = 0;
	for (; ql != qr;) {
		int u = q[ql++];
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to, f = g[i].f;
			if (d[v] != -1 || !f) continue;
			q[qr++] = v, d[v] = d[u] + 1;
		}
	}
	return d[snk] > 0;
}

int dfs(int u = src, int mf = inf) {
	if (u == snk) return mf;
	int res = 0;
	for (int &i = cur[u]; i; i = g[i].nxt) {
		int v = g[i].to, f = g[i].f;
		if (d[v] != d[u] + 1 || !f) continue;
		int cur = dfs(v, min(mf - res, f));
		if (cur) {
			g[i].f -= cur, g[rev(i)].f += cur, res += cur;
			if (res == mf) break;
		}
	}
	return res;
}

void inline max_flow(int &flow) {
	for (; bfs(); flow += dfs());
}

void inline graph_init() {
	src = ++sz, snk = ++sz;
	cont (u, n1) nd[u][0] = ++sz;
	cont (u, n2) nd[u][1] = ++sz;
	cont (u, n1) g.link(src, nd[u][0], deg[u] - min_deg);
	cont (u, n2) g.link(nd[u][1], snk, deg[u + n1] - min_deg);
	cont (i, m) {
		int u = e[i].first, v = e[i].second;
		g.link(nd[u][0], nd[v][1], 1);
		g.e[g.sz - 1].id = i;
	}
}

void inline find_solution(vector<int> &r) {
	cont (p, n1) for (int i = g.hd[nd[p][0]]; i; i = g[i].nxt) {
		if (i < rev(i) && g[i].f == 1) r.push_back(g[i].id);
	}
}

void inline solve() {
	cont (i, m) {
		int u = e[i].first, v = e[i].second;
		++deg[u], ++deg[v + n1];
	}
	cont (u, n1 + n2) min_deg = min(min_deg, deg[u]);
	graph_init();
	ans.resize(min_deg + 1);
	for (int k = min_deg, flow = 0; k >= 0; --k) {
		max_flow(flow);
		find_solution(ans[k]);
		for (int i = g.hd[src]; i; i = g[i].nxt) if (i < rev(i)) g[i].f += 1;
		for (int i = g.hd[snk]; i; i = g[i].nxt) if (i > rev(i)) g[rev(i)].f += 1;
	}
	circ (k, 0, min_deg) {
		printf("%d", int(ans[k].size()));
		loop (i, ans[k].size()) {
			printf(" %d", ans[k][i]);
		}
		printf("\n");
	}
}

int main() {
	scanf("%d%d%d", &n1, &n2, &m);
	cont (i, m) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[i] = make_pair(u, v);
	}
	solve();
}