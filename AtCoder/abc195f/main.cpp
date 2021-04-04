#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (__typeof(to) i = 0; i < to; ++i)
#define cont(i, to)        for (__typeof(to) i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (__typeof(to) i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 74;
const int hsz = int(1e7) + 39, esz = 2e6;
bitset<nsz> g[nsz + 5];
int vis[nsz + 5], pw[nsz + 5];
num n, fm, to, ans = 1, a[nsz + 5];

struct hash_table {
	int sz, hd[hsz + 5];
	
	struct node {
		int nxt;
		bitset<nsz> w;
		
		node() {}
		node(int nxt, bitset<nsz> w): nxt(nxt), w(w) {}
	} e[esz + 5];
	
	int inline to_key(const bitset<nsz> &w) {
		int u = 0;
		cont (i, n) u = (u * 2 + w[i]) % hsz;
		return u;
	}
	
	void inline ins(const bitset<nsz> &w, int u) {
		e[++sz] = node(hd[u], w), hd[u] = sz;
	}
	
	bool inline qry(const bitset<nsz> &w, int u) {
		for (int i = hd[u]; i; i = e[i].nxt) {
			if (e[i].w == w) return 1;
		}
		return 0;
	}
};
hash_table dat;

num gcd(num a, num b) {
	return !b ? a : gcd(b, a % b);
}

void bfs(int s, int &sz, int *nd) {
	static int q[nsz + 5];
	int ql = 0, qr = 0;
	for (q[qr++] = s, vis[s] = s; ql != qr;) {
		int u = q[ql++];
		nd[sz++] = u;
		cont (v, n) if (g[u][v] && !vis[v]) q[qr++] = v, vis[v] = s;
	}
}

num inline calc(int s) {
	static int nd[nsz + 5], d[esz + 5];
	static bitset<nsz> q[esz + 5], p[esz + 5];
	int sz = 0, ql = 0, qr = 1, cnt = 0;
	bfs(s, sz, nd);
	if (sz == 1) return 2;
	for (; ql != qr; ++cnt) {
		bitset<nsz> cur = q[ql], ban = p[ql], nban;
		int key = d[ql]; ++ql;
		loop (i, sz) if (!ban[nd[i]]) {
			int v = nd[i], nkey = (key + pw[v]) % hsz;
			cur[v] = 1, nban = ban | g[v];
			if (!dat.qry(cur, nkey)) {
				q[qr] = cur, p[qr] = nban, d[qr] = nkey; ++qr;
				dat.ins(cur, nkey);
			}
			cur[v] = 0;
		}
	}
	return cnt;
}

void inline init() {
	pw[0] = 1;
	cont (i, n) pw[i] = pw[i - 1] * 2 % hsz;
}

int main() {
	scanf("%lld%lld", &fm, &to);
	n = to - fm + 1;
	circ (i, fm, to) a[num(i) - fm + 1] = i;
	cont (u, n) cont (v, u) g[u][v] = g[v][u] = gcd(a[u], a[v]) > 1;
	init();
	cont (u, n) if (!vis[u]) ans *= calc(u);
	printf("%lld\n", ans);
}