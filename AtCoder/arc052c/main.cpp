#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e4, msz = 1e5, sqrtsz = 200;
const int inf = 0x3f3f3f3f;
int n, m, src = 1, cnt[nsz + 5], dis[nsz + 5][sqrtsz + 5];
map<pair<int, int>, int> id;

template<int ndsz, int egsz> struct graph {
	int sz, hd[ndsz + 5];
	
	struct edge {
		int nxt, to, w;
		
		edge() {}
		edge(int nxt, int to, int w): nxt(nxt), to(to), w(w) {}
	} e[2 * egsz + 5];
	
	inline edge operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v, int w) {
		e[++sz] = edge(hd[u], v, w), hd[u] = sz;
		e[++sz] = edge(hd[v], u, w), hd[v] = sz;
	}
};
graph<nsz, msz> g;

struct node {
	int w, u, d;
	
	node() {}
	node(int w, int u, int d): w(w), u(u), d(d) {}
	
	bool inline operator < (const node &b) const { return w > b.w; }
};

bool inline upd(int &a, int b) {
	if (a > b) { a = b; return 1; }
	return 0;
}

void inline bfs(int s, int *d) {
	static deque<int> q;
	for (d[s] = 0, q.push_back(s); q.size();) {
		int u = q.front(); q.pop_front();
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to, w = g[i].w;
			if (upd(d[v], d[u] + w)) w ? q.push_back(v) : q.push_front(v);
		}
	}
}

void inline dijkstra() {
	priority_queue<node> q;
	for (q.push(node(dis[src][0] = 0, src, 0)); q.size();) {
		int u = q.top().u, d = q.top().d; q.pop();
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to, w = g[i].w;
			if (w == 0 && cnt[u] + d <= cnt[v] + sqrtsz) {
				w = 1;
				int nd = cnt[u] + d - cnt[v];
				if (upd(dis[v][nd], dis[u][d] + w)) q.push(node(dis[v][nd], v, nd));
			} else if (w == 1 && cnt[u] + d + 1 <= cnt[v] + sqrtsz) {
				w += cnt[u] + d;
				int nd = cnt[u] + d - cnt[v] + 1;
				if (upd(dis[v][nd], dis[u][d] + w)) q.push(node(dis[v][nd], v, nd));
			}
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	cont (i, m) {
		int u, v, w;
		scanf("%d%d%d", &w, &u, &v);
		g.link(++u, ++v, w);
	}
	memset(cnt, inf, sizeof(cnt));
	bfs(src, cnt);
	memset(dis, inf, sizeof(dis));
	dijkstra();
	cont (u, n) {
		int mn = inf;
		circ (k, 0, sqrtsz) mn = min(mn, dis[u][k]);
		printf("%d\n", mn);
	}
}