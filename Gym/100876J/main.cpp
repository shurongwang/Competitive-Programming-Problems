#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 2e3;
const int inf = 2.1e9;
int n, m, k;

struct graph {
	int sz, hd[nsz + 5];
	
	struct edge {
		int nxt, to, w, id;
		
		edge() {}
		edge(int nxt, int to, int w, int id) {
			this->nxt = nxt, this->to = to, this->w = w, this->id = id;
		}
	} e[2 * nsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v, int w, int id) {
		e[++sz] = edge(hd[u], v, w, id), hd[u] = sz;
		e[++sz] = edge(hd[v], u, w, id), hd[v] = sz;
	}
};
graph g;

namespace solve_tree {
	struct node {
		int id, fm, ls, rs, val;
		
		node() {}
		node(int val, int id, int ls = 0, int rs = 0, int fm = 0) {
			this->val = val, this->id = id, this->ls = ls, this->rs = rs, this->fm = fm;
		}
	};
	node dat[nsz * nsz + 5];
	
	int sz, rt = 1, siz[nsz + 5], dp[nsz + 5][nsz + 5], ans = inf;
	vector<int> e;
	
	int inline new_node(int val, int ls = 0, int rs = 0, int fm = 0) {
		int u = ++sz;
		dat[u] = node(val, u, ls, rs, fm);
		return u;
	}
	
	void dfs(int u = rt, int p = -1) {
		dp[u][0] = new_node(0);
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to, w = g[i].w;
			if (v == p) continue;
			dfs(v, u);
			for (int k1 = min(k, siz[u]); k1 >= 0; --k1) {
				for (int k2 = min(siz[v], k - k1 - 1); k2 >= 0; --k2) {
					int &id = dp[u][k1 + k2 + 1], ls = dp[u][k1], rs = dp[v][k2], val = dat[ls].val + dat[rs].val + w;
					if (ls && rs && (!id || val < dat[id].val)) id = new_node(val, ls, rs, g[i].id);
				}
			}
			siz[u] += siz[v];
		}
		siz[u] += 1;
	}
	
	void inline find_solution(int u = rt, int p = -1) {
		static int q[nsz * nsz + 5];
		int src = 0, ql = 0, qr = 0;
		cont (u, n) {
			int id = dp[u][k];
			if (!src || (id && dat[id].val < dat[src].val)) src = id;
		}
		ans = dat[src].val;
		q[qr++] = src;
		for (; ql != qr;) {
			int u = q[ql++], ls = dat[u].ls, rs = dat[u].rs;
			if (dat[u].fm) e.push_back(dat[u].fm);
			if (ls) q[qr++] = ls;
			if (rs) q[qr++] = rs;
		}
	}
	
	void inline solve() {
		dfs();
		find_solution();
		printf("%d\n", ans);
		loop (i, e.size()) printf("%d\n", e[i]);
	}
};

namespace solve_circle {
	int d[nsz + 5], ans;
	vector<int> c, e;
	vector< pair<int, int> > h;
	vector< vector< pair<int, int> > > w;
	
	bool dfs(int u, int p = -1) {
		if (c.size() && u == c[0]) return 0;
		c.push_back(u);
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to;
			if (v == p || d[v] == 1) continue;
			h.push_back(make_pair(g[i].w, g[i].id));
			if (!dfs(v, u)) break;
		}
		return 0;
	}
	
	void inline init_circle() {
		cont (u, n) {
			for (int i = g.hd[u]; i; i = g[i].nxt) {
				int v = g[i].to;
				d[u] += 1, d[v] += 1;
			}
		}
		cont (u, n) d[u] >>= 1;
		cont (u, n) if (d[u] != 1) {
			dfs(u);
			break;
		}
		w.resize(c.size());
		loop (id, c.size()) {
			int u = c[id];
			for (int i = g.hd[u]; i; i = g[i].nxt) {
				int v = g[i].to;
				if (d[v] == 1) w[id].push_back(make_pair(g[i].w, g[i].id));
			}
		}
	}
	
	int inline length(int l, int r) {
		return l <= r ? r - l + 1 : r + c.size() - l + 1;
	}
	
	void inline find_solution(int l, int r) {
		priority_queue< pair<int, int> > q;
		int cap = k;
		for (int i = l; i != r; ++i, i %= c.size()) e.push_back(h[i].second), --cap;
		for (int i = l, len = length(l, r); len > 0; --len, ++i, i %= c.size()) {
			loop (j, w[i].size()) {
				if (q.size() < cap) q.push(w[i][j]);
				else if (q.size() && q.top() > w[i][j]) q.pop(), q.push(w[i][j]);
			}
		}
		if (q.size() < cap) q.push(h[r]);
		else if (q.size() && q.top() > h[r]) q.pop(), q.push(h[r]);
		for (; q.size(); q.pop()) e.push_back(q.top().second);
	}
	
	void inline solve() {
		init_circle();
		int el, er, mn = inf;
		loop (l, c.size()) {
			priority_queue<int> q;
			for (int r = l, len = 0, cap = k, cur = 0; len < c.size(); ++len, ++r, r %= c.size()) {
				if (l != r) {
					cur += h[(r - 1 + c.size()) % c.size()].first;
					if (q.size() == cap && q.size()) cur -= q.top(), q.pop();
					cap -= 1;
					if (cap < 0) break;
				}
				loop (i, w[r].size()) {
					int val = w[r][i].first;
					if (q.size() < cap) cur += val, q.push(val);
					else if (q.size() && q.top() > val) cur += val - q.top(), q.pop(), q.push(val);
				}
				int del = 0, pcur = cur;
				if (q.size() < cap) cur += h[r].first, del = 1;
				else if (q.size() && q.top() > h[r].first) cur += h[r].first - q.top();
				if (q.size() + del == cap && mn > cur) mn = cur, el = l, er = r;
				cur = pcur;
			}
		}
		ans = mn;
		find_solution(el, er);
		printf("%d\n", ans);
		loop (i, e.size()) printf("%d\n", e[i]);
	}
};

int main() {
	scanf("%d%d%d", &n, &m, &k);
	cont (i, m) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		g.link(u, v, w, i);
	}
	if (m == n - 1) solve_tree::solve();
	else solve_circle::solve();
}