#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

namespace io {
	#define isdigit(c)  (c >= '0' && c <= '9')
	#define getchar()   (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufsz, stdin), p1 == p2) ? EOF : *p1++)
	#define flush()     (fwrite(puf, 1, pp - puf, stdout), pp = puf)
	#define putchar(c)  (*pp++ = c, pp - puf == bufsz && flush())
	
	const int bufsz = 1 << 24;
	static char buf[bufsz], puf[bufsz], *p1, *p2, *pp = puf;
	struct flusher { ~flusher() { flush(); } } flusher;
	
	template<class type> void inline read(type &a) {
		char c = getchar();
		for (; !isdigit(c); c = getchar());
		for (a = 0; isdigit(c); a *= 10, a += c & 15, c = getchar());
	}
	
	template<class type> void inline write(type a, char c = ln) {
		static int d[20];
		int s = d[0] = 0;
		for (a < 0 && (putchar(45), a = -a); a; d[s++] = a % 10, a /= 10);
		for (s || (s = 1); s; putchar(d[--s] + 48));
		putchar(c);
	}
}
using namespace io;

const int nsz = 1e6;
const int inf = 0x3f3f3f3f;
int n, k, rt = 1, a[nsz + 5], id[nsz + 5];
int pr[nsz + 5], dep[nsz + 5], hs[nsz + 5];
num ans;
vector<num> dp[nsz + 5];

struct graph {
	int sz, hd[nsz + 5];
	
	struct edge {
		int nxt, to;
		
		edge() {}
		edge(int nxt, int to) { this->nxt = nxt, this->to = to; }
	} e[2 * nsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v) {
		e[++sz] = edge(hd[u], v), hd[u] = sz;
		e[++sz] = edge(hd[v], u), hd[v] = sz;
	}
};
graph g;

void dfs(int u = rt, int p = rt) {
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (v == p) continue;
		dfs(v, u);
		dep[u] = max(dep[u], dep[v] + 1);
		if (dep[v] >= dep[hs[u]]) hs[u] = v;
	}
}

inline num f_val(int u, int k) {
	vector<num> &cur = dp[id[u]];
	return k < cur.size() ? cur[cur.size() - k - 1] : 0;
}

inline num& f(int u, int k) {
	vector<num> &cur = dp[id[u]];
	return cur[cur.size() - k - 1];
}

void inline upd(num &a, num b) {
	if (a < b) a = b;
}

void solve(int u = rt, int p = -1) {
	if (!hs[u]) {
		dp[id[u]].push_back(0);
		dp[id[u]].push_back(a[u]);
	} else {
		solve(hs[u], u);
		id[u] = id[hs[u]], dp[id[u]].push_back(a[u]);
		upd(f(u, 0), f(u, 1));
		if (dep[u] >= k) upd(f(u, 0), f(u, k) + a[u]);
	}
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (v == p || v == hs[u]) continue;
		solve(v, u);
		circ (d, 0, min(k, dep[v]) + 1) {
			num val = f_val(u, d);
			if (d > 0) upd(f(u, d), f_val(v, d - 1) + f_val(u, max(k - d, d)));
			upd(f(u, d), val + f_val(v, max(k - d - 1, d - 1)));
		}
		for (int d = dep[v]; d >= 0; --d) upd(f(u, d), f(u, d + 1));
	}
}

int main() {
	read(n), read(k), k += 1;
	cont (i, n) read(a[i]), id[i] = i;
	cont (i, n - 1) {
		int u, v;
		read(u), read(v);
		g.link(u, v);
	}
	dfs(), solve();
	circ (d, 0, min(dep[rt], k)) upd(ans, f(rt, d));
	write(ans);
}