#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 5e5;
int n, rt = 1, a[nsz + 5], siz[nsz + 5];
num mx[nsz + 5], ans;

struct graph {
	int sz, hd[nsz + 5];
	
	struct edge {
		int nxt, to;
		
		edge() {}
		edge(int nxt, int to) {
			this->nxt = nxt, this->to = to;
		}
	} e[2 * nsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v) {
		e[++sz] = edge(hd[u], v), hd[u] = sz;
		e[++sz] = edge(hd[v], u), hd[v] = sz;
	}
};
graph g;

struct sheep {
	num tm, mx;
	
	sheep() {}
	sheep(num tm, num mx) {
		this->tm = tm, this->mx = mx;
	}
	
	bool inline operator < (const sheep &b) const { return tm + b.mx < b.tm + mx; }
};

void dfs(int u = rt, int p = -1) {
	vector<sheep> nd;
	siz[u] = 1;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (v == p) continue;
		dfs(v, u);
		siz[u] += siz[v];
		nd.push_back(sheep(2 * siz[v], mx[v]));
	}
	sort(all(nd));
	mx[u] = a[u];
	num sum = 1;
	loop (i, nd.size()) {
		num cur = sum + nd[i].mx;
		mx[u] = max(mx[u], cur);
		sum += nd[i].tm;
	}
	if (p == -1) ans = max(mx[u], (num) a[u] + 2 * (n - 1));
}

int main() {
	scanf("%d", &n);
	cont (i, n) scanf("%d", &a[i]);
	cont (i, n - 1) {
		int u, v;
		scanf("%d%d", &u, &v);
		g.link(u, v);
	}
	dfs();
	printf("%lld\n", ans);
}