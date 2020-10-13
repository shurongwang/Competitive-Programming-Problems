#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 2e5;
bool vis[nsz + 5];
int n, m, nd, a[nsz + 5], b[nsz + 5];
num sum, ans;
vector< pair<int, int> > g[nsz + 5];

struct edge {
	int u, v, w;
	
	edge() {}
	edge(int u, int v, int w) {
		this->u = u, this->v = v, this->w = w;
	}
	
	bool inline operator < (const edge b) const { return w > b.w; }
};

struct union_find {
	int pr[nsz + 5];
	
	void inline init(const vector<int> &nd) {
		loop (i, nd.size()) pr[nd[i]] = nd[i];
	}
	
	int qry(int u) { return u == pr[u] ? u : pr[u] = qry(pr[u]); }
	
	bool inline link(int u, int v) {
		u = qry(u), v = qry(v);
		if (u == v) return 0;
		pr[v] = u;
		return 1;
	}
};
union_find uf;

void inline get_info(int s, vector<int> &nd, vector<edge> &eg) {
	static int q[nsz + 5];
	int ql = 0, qr = 0;
	q[qr++] = s, vis[s] = 1;
	for (; ql != qr;) {
		int u = q[ql++];
		nd.push_back(u);
		loop (i, g[u].size()) {
			int v = g[u][i].first, w = g[u][i].second;
			if (u < v) eg.push_back(edge(u, v, w));
			if (!vis[v]) q[qr++] = v, vis[v] = 1;
		}
	}
}

num inline kruskal(vector<int>& nd, vector<edge> &eg) {
	num res = 0;
	uf.init(nd);
	sort(all(eg));
	loop (i, eg.size()) {
		int u = eg[i].u, v = eg[i].v, w = eg[i].w;
		if (uf.link(u, v)) res += w;
	}
	return res;
}

int main() {
	scanf("%d%d", &m, &n);
	nd = n + m;
	cont (i, m) scanf("%d", &a[i]);
	cont (i, n) scanf("%d", &b[i]);
	cont (i, m) {
		int sz;
		scanf("%d", &sz);
		cont (j, sz) {
			int u, p = i + n;
			scanf("%d", &u);
			g[p].push_back(make_pair(u, a[i] + b[u]));
			g[u].push_back(make_pair(p, a[i] + b[u]));
			sum += a[i] + b[u];
		}
	}
	cont (u, nd) {
		if (vis[u]) continue;
		vector<int> nd;
		vector<edge> eg;
		get_info(u, nd, eg);
		ans += kruskal(nd, eg);
	}
	ans = sum - ans;
	printf("%lld\n", ans);
}