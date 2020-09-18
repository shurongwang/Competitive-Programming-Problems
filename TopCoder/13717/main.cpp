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
	operator int&() { return w; }
	operator int() const { return w; }
	
	modulo() {}
	modulo(int w, bool f = 0) { this->w = w; if (f) fix(); }
	void inline fix() { if (w >= mod || w < -mod) w %= mod; if (w < 0) w += mod; }
	
	inline modulo  operator -  () { w = -w + mod; return *this; }
	inline modulo  operator +  (const modulo &b) { modulo r = *this; return r += b; }
	inline modulo  operator -  (const modulo &b) { modulo r = *this; return r -= b; }
	inline modulo  operator *  (const modulo &b) { modulo r = *this; return r *= b; }
	inline modulo  operator /  (const modulo &b) { modulo r = *this; return r /= b; }
	inline modulo& operator += (const modulo &b) { if ((w += b.w) >= mod) w -= mod; return *this; }
	inline modulo& operator -= (const modulo &b) { if ((w -= b.w) < 0) w += mod; return *this; }
	inline modulo& operator *= (const modulo &b) { w = (num) w * b.w % mod; return *this; }
	inline modulo& operator /= (const modulo &b) { return *this *= inv(b); }
	
	friend inline modulo inv(const modulo &w) {
		int a = w, m = mod, u = 0, v = 1, t;
		for (; a != 0; t = m / a, m -= t * a, swap(a, m), u -= t * v, swap(u, v));
		return modulo(u, 1);
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

const int nsz = 2e3;

struct graph {
	int sz, hd[nsz + 5];
	
	struct edge {
		int nxt, to;
		
		edge() {}
		edge(int nxt, int to) {
			this->nxt = nxt, this->to = to;
		}
	} e[nsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v) {
		e[++sz] = edge(hd[u], v), hd[u] = sz;
	}
};

struct TheTreeAndMan {
	int n, rt = 1;
	rem inv2 = inv(rem(2)), dep[nsz + 5], siz[nsz + 5], f[nsz + 5], sf[nsz + 5], ans;
	graph g;
	
	void dfs1(int u) {
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to;
			dep[v] = dep[u] + rem(1);
			dfs1(v);
			f[u] += siz[u] * siz[v];
			siz[u] += siz[v];
			sf[u] += sf[v];
		}
		siz[u] += rem(1);
		sf[u] += f[u];
	}
	
	rem inline square(rem a) { return a * a; }
	
	void dfs2(int u) {
		rem sum = 0, del = 0;
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to;
			dfs2(v);
			sum += siz[v];
			del += siz[v] * siz[v];
		}
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to;
			rem head = dep[u], foot = sf[v];
			rem body = (square(sum - siz[v]) - del + square(siz[v])) * inv2;
			ans += head * body * foot;
		}
	}
	
	int solve(vector<int> parent) {
		n = int(parent.size()) + 1;
		loop (i, n - 1) g.link(parent[i] + 1, i + 2);
		dfs1(rt), dfs2(rt);
		return ans.w;
	}
};