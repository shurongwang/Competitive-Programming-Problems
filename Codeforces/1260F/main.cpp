#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

template<int mod> struct modulo {
	int w;
	template<typename type> operator type() const { return static_cast<type>(w); }
	
	modulo() {}
	modulo(int w) { this->w = w; fix(); }
	void inline fix() { if (w >= mod || w < -mod) w %= mod; if (w < 0) w += mod; }
	
	inline modulo  operator -  () const { return mod - w; }
	inline modulo& operator += (const modulo &b) { if ((w += b.w) >= mod) w -= mod; return *this; }
	inline modulo& operator -= (const modulo &b) { if ((w -= b.w) < 0) w += mod; return *this; }
	inline modulo& operator *= (const modulo &b) { w = (unsigned long long) w * b.w % mod; return *this; }
	inline modulo& operator /= (const modulo &b) { return *this *= inv(b); }
	friend modulo operator + (const modulo& a, const modulo& b) { return modulo(a) += b; }
	template<typename type> friend modulo operator + (const modulo &a, const type &b) { return modulo(a) += b; }
	template<typename type> friend modulo operator + (const type &a, const modulo &b) { return modulo(a) += b; }
	friend modulo operator - (const modulo& a, const modulo& b) { return modulo(a) -= b; }
	template<typename type> friend modulo operator - (const modulo &a, const type &b) { return modulo(a) -= b; }
	template<typename type> friend modulo operator - (const type &a, const modulo &b) { return modulo(a) -= b; }
	friend modulo operator * (const modulo& a, const modulo& b) { return modulo(a) *= b; }
	template<typename type> friend modulo operator * (const modulo &a, const type &b) { return modulo(a) *= b; }
	template<typename type> friend modulo operator * (const type &a, const modulo &b) { return modulo(a) *= b; }
	friend modulo operator / (const modulo& a, const modulo& b) { return modulo(a) /= b; }
	template<typename type> friend modulo operator / (const modulo &a, const type &b) { return modulo(a) /= b; }
	template<typename type> friend modulo operator / (const type &a, const modulo &b) { return modulo(a) /= b; }
	friend istream& operator >> (istream& in, modulo& a) { return in >> a.w; }
	friend ostream& operator << (ostream& out, const modulo& a) { return out << a.w; }
	
	friend inline modulo inv(const modulo &w) {
		int a = w, m = mod, u = 0, v = 1, t;
		for (; a != 0; t = m / a, m -= t * a, swap(a, m), u -= t * v, swap(u, v));
		return u;
	}
	
	friend inline modulo pow(const modulo &w, int p) {
		if (!w)  return 0;
		modulo a = w, r = 1;
		for (; p > 0; a *= a, p >>= 1) if (p & 1) r *= a;
		return r;
	}
};
const int mod = int(1e9) + 7;
typedef modulo<mod> rem;

const int nsz = 1e5, csz = 1e5;
int n, cl[nsz + 5], cr[nsz + 5], cs[nsz + 5];
int rt = 1, pr[nsz + 5], siz[nsz + 5], dep[nsz + 5], hs[nsz + 5], top[nsz + 5], id[nsz + 5];
rem total = 1, sum, ans;

struct fenwick_tree {
	rem tr[nsz + 5][2];
	
	void inline upd(int l, int r, rem w) { upd(l, w), upd(r + 1, -w); }
	void inline upd(int id, rem w0) {
		rem w1 = w0 * id;
		for (int u = id; u <= n; u += u & -u) tr[u][0] += w0, tr[u][1] += w1;
	}
	
	rem inline qry(int l, int r) { return qry(r) - qry(l - 1); }
	rem inline qry(int id) {
		rem r0 = 0, r1 = 0;
		for (int u = id; u > 0; u -= u & -u) r0 += tr[u][0], r1 += tr[u][1];
		return r0 * (id + 1) - r1;
	}
};
fenwick_tree tr;

struct graph {
	int sz, hd[nsz + 5];
	
	struct edge {
		int nxt, to;
		
		edge() {}
		edge(int nxt, int to): nxt(nxt), to(to) {}
	} e[2 * nsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v) {
		e[++sz] = edge(hd[u], v), hd[u] = sz;
		e[++sz] = edge(hd[v], u), hd[v] = sz;
	}
};
graph g;

struct event {
	int u, del;
	
	event() {}
	event(int u, int del): u(u), del(del) {}
	
	bool inline operator < (const event &b) const { return del < b.del; }
};
vector<event> ev[csz + 5];

void dfs1(int u = rt) {
	siz[u] = 1;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (v == pr[u]) continue;
		pr[v] = u, dep[v] = dep[u] + 1;
		dfs1(v);
		siz[u] += siz[v];
		if (siz[hs[u]] < siz[v]) hs[u] = v;
	}
}

void dfs2(int u = rt, int tp = rt) {
	static int t = 0;
	id[u] = ++t;
	top[u] = tp;
	if (!hs[u]) return;
	dfs2(hs[u], tp);
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (v == pr[u] || v == hs[u]) continue;
		dfs2(v, v);
	}
}

void inline upd_route(int u, int v, rem w) {
	for (; top[u] != top[v]; v = pr[top[v]]) {
		if (dep[top[u]] > dep[top[v]]) swap(u, v);
		tr.upd(id[top[v]], id[v], w);
	}
	if (dep[u] > dep[v]) swap(u, v);
	tr.upd(id[u], id[v], w);
}

rem inline qry_route(int u, int v) {
	rem r = 0;
	for (; top[u] != top[v]; v = pr[top[v]]) {
		if (dep[top[u]] > dep[top[v]]) swap(u, v);
		r += tr.qry(id[top[v]], id[v]);
	}
	if (dep[u] > dep[v]) swap(u, v);
	r += tr.qry(id[u], id[v]);
	return r;
}

void inline init() {
	dfs1(), dfs2();
	cont (u, n) {
		ev[cl[u]].push_back(event(u, +1));
		ev[cr[u] + 1].push_back(event(u, -1));
	}
	cont (c, csz) sort(all(ev[c]));
}

int main() {
	scanf("%d", &n);
	cont (i, n) scanf("%d%d", &cl[i], &cr[i]), cs[i] = cr[i] - cl[i] + 1, total *= cs[i];
	cont (i, n - 1) {
		int u, v;
		scanf("%d%d", &u, &v);
		g.link(u, v);
	}
	init();
	rem s1 = 0, s2 = 0, s3 = 0;
	cont (c, csz) {
		loop (i, ev[c].size()) {
			int u = ev[c][i].u, d = ev[c][i].del;
			rem w = inv(rem(cs[u]));
			if (d == -1) s1 -= dep[u] * w, s2 -= w, s3 -= dep[u] * w * w;
			if (d == +1) s1 += dep[u] * w, s2 += w, s3 += dep[u] * w * w;
		}
		ans += total * (s1 * s2 - s3);
	}
	sum = 0;
	cont (c, csz) {
		loop (i, ev[c].size()) {
			int u = ev[c][i].u, d = ev[c][i].del;
			rem w = inv(rem(cs[u])) * d;
			if (d == -1) upd_route(rt, u, w), sum += (qry_route(rt, u) - tr.qry(rt, rt)) * w;
			if (d == +1) sum += (qry_route(rt, u) - tr.qry(rt, rt)) * w, upd_route(rt, u, w);
		}
		ans -= 2 * total * sum;
	}
	printf("%d\n", ans.w);
}