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
const int inf = 0x3f3f3f3f;
bool fix[nsz + 5];
int n, m, dm, rt, a[nsz + 5], ans;

struct treap {
	static int rt;
	bool cv[nsz + 5];
	int sz, ls[nsz + 5], rs[nsz + 5], siz[nsz + 5], w[nsz + 5], del[nsz + 5], cov[nsz + 5];
	
	int inline new_node(int w = 0) {
		int u = ++sz;
		siz[u] = 1, this->w[u] = w;
		return u;
	}
	
	void inline up(int u) {
		siz[u] = siz[ls[u]] + siz[rs[u]] + 1;
	}
	
	void inline add_u(int u, int w) {
		if (w) this->w[u] += w, del[u] += w;
	}
	
	void inline set_u(int u, int w) {
		this->w[u] = cov[u] = w, cv[u] = 1, del[u] = 0;
	}
	
	void inline down(int u) {
		int ls = this->ls[u], rs = this->rs[u];
		if (cv[u]) {
			if (ls) set_u(ls, cov[u]);
			if (rs) set_u(rs, cov[u]);
			cv[u] = 0;
		}
		if (ls) add_u(ls, del[u]);
		if (rs) add_u(rs, del[u]);
		del[u] = 0;
	}
	
	void inline init(int l, int r) {
		rt = build(l, r);
	}
	
	int build(int l, int r) {
		if (l > r) return 0;
		int md = (l + r) >> 1, u = new_node(0);
		ls[u] = build(l, md - 1);
		rs[u] = build(md + 1, r);
		up(u);
		return u;
	}
	
	int mrg(int v1, int v2) {
		if (!v1 || !v2) return v1 | v2;
		if (rand() % (siz[v1] + siz[v2]) < siz[v1]) {
			down(v1), rs[v1] = mrg(rs[v1], v2), up(v1); return v1;
		} else {
			down(v2), ls[v2] = mrg(v1, ls[v2]), up(v2); return v2;
		}
	}
	
	void spl0(int u, int w, int &v1, int &v2) {
		if (!u) return (void) (v1 = v2 = 0);
		down(u);
		int cur = siz[ls[u]] + 1;
		if (cur <= w) {
			v1 = u, spl0(rs[u], w - cur, rs[u], v2), up(u);
		} else {
			v2 = u, spl0(ls[u], w, v1, ls[u]), up(u);
		}
	}
	
	void spl1(int u, int w, int &v1, int &v2) {
		if (!u) return (void) (v1 = v2 = 0);
		down(u);
		if (this->w[u] >= w) {
			v1 = u, spl1(rs[u], w, rs[u], v2), up(u);
		} else {
			v2 = u, spl1(ls[u], w, v1, ls[u]), up(u);
		}
	}
	
	int at(int u, int k) {
		if (!u) return 0;
		down(u);
		int cur = siz[ls[u]] + 1;
		if (cur == k) return u;
		if (cur <= k) return at(rs[u], k - cur);
		return at(ls[u], k);
	}
	
	int operator [] (int id) {
		int u = at(rt, id);
		if (!u) return inf;
		return w[u];
	}
	
	void inline add(int l, int r, int w) {
		int v1, v2;
		spl0(rt, l - 1, v1, rt);
		spl0(rt, r, rt, v2);
		add_u(rt, w);
		rt = mrg(v1, mrg(rt, v2));
	}
	
	void inline add_all(int w) {
		add_u(rt, w);
	}
	
	void inline set(int l, int r, int w) {
		int v1, v2;
		spl0(rt, l - 1, v1, rt);
		spl0(rt, r, rt, v2);
		set_u(rt, w);
		rt = mrg(v1, mrg(rt, v2));
	}
	
	void inline set_all(int w) {
		set_u(rt, w);
	}
	
	int min(int u = rt) {
		for (; rs[u]; down(u), u = rs[u]);
		return w[u];
	}
	
	void go(int u) {
		down(u);
		if (ls[u]) go(ls[u]);
		cerr << "(" << (w[u] >= inf ? -1 : w[u]) << "), ";
		if (rs[u]) go(rs[u]);
	}
	
	void inline dbg(int u = rt) {
		cerr << "{";
		if (u) go(u);
		cerr << "}" << ln;
	}
};
int treap::rt;
treap tr;

void inline discretize() {
	static int b[nsz + 5];
	cont (i, n) b[++dm] = a[i];
	sort(b + 1, b + dm + 1), dm = unique(b + 1, b + dm + 1) - b - 1;
	cont (i, n) a[i] = lower_bound(b + 1, b + dm + 1, a[i]) - b;
}

int main() {
	scanf("%d%d", &n, &m);
	cont (i, n) scanf("%d", &a[i]), a[i] -= i;
	discretize();
	cont (i, m) {
		int p;
		scanf("%d", &p);
		fix[p] = 1;
	}
	tr.init(1, dm);
	cont (i, n) {
		int v1, v2, v3, val, cur;
		if (fix[i]) {
			val = tr[a[i]];
			tr.spl0(tr.rt, a[i] - 1, v1, v2);
			tr.set_u(v1, inf);
			tr.set_u(v2, val);
			tr.rt = tr.mrg(v1, v2);
		} else {
			val = tr[a[i]], cur = val + 1;
			tr.add_all(1);
			if (val < cur) {
				tr.spl0(tr.rt, a[i] - 1, v1, tr.rt);
				tr.spl1(tr.rt, cur, tr.rt, v2);
				tr.set_u(tr.rt, val);
				tr.rt = tr.mrg(v1, tr.mrg(tr.rt, v2));
			}
		}
	}
	ans = tr.min();
	ans = ans >= inf ? -1 : ans;
	printf("%d\n", ans);
}