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
	modulo(int w, bool f = 0) { this->w = w; if (f) fix(); }
	void inline fix() { if (w >= mod || w < -mod) w %= mod; if (w < 0) w += mod; }
	
	inline modulo  operator -  () { w = -w + mod; return *this; }
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
		return modulo(u, 1);
	}
	
	friend inline modulo pow(const modulo &w, int p) {
		if (!w)  return 0;
		modulo a = w, r = 1;
		for (; p > 0; a *= a, p >>= 1) if (p & 1) r *= a;
		return r;
	}
};
const int mod = 998244353;
typedef modulo<mod> rem;

const int nsz = 2e3;
int n, rt = 1;
vector<rem> f[nsz + 5];

struct union_find {
	int pr[nsz + 5], sz[nsz + 5], es[nsz + 5];
	
	void inline init(int n) {
		cont (u, n) pr[u] = u, sz[u] = 1;
	}
	
	int qry(int u) { return pr[u] == u ? u : pr[u] = qry(pr[u]); }
	
	int inline link(int u, int v) {
		u = qry(u), v = qry(v);
		if (u == v) { ++es[u]; return 0; }
		pr[v] = u, sz[u] += sz[v], es[u] += es[v] + 1;
		return 1;
	}
};
union_find uf;

struct edge {
	int u, v, w;
	
	edge() {}
	edge(int u, int v, int w) { this->u = u, this->v = v, this->w = w; }
	
	bool inline operator < (const edge b) const { return w < b.w; }
};
vector<edge> e;

vector<rem> inline convolution(const vector<rem> &a, const vector<rem> &b) {
	vector<rem> r(a.size() + b.size() - 1, 0);
	loop (i, a.size()) loop (j, b.size()) r[i + j] += a[i] * b[j];
	return r;
}

int main() {
	scanf("%d", &n);
	cont (u, n) cont (v, n) {
		int w;
		scanf("%d", &w);
		if (u < v) e.push_back(edge(u, v, w));
	}
	cont (u, n) f[u].push_back(0), f[u].push_back(1);
	sort(all(e));
	uf.init(n);
	loop (i, e.size()) {
		int u = uf.qry(e[i].u), v = uf.qry(e[i].v), w = e[i].w, p;
		if (uf.link(u, v)) f[u] = convolution(f[u], f[v]);
		if (uf.es[u] * 2 == uf.sz[u] * (uf.sz[u] - 1)) f[u][1] += 1;
	}
	rt = uf.qry(rt);
	cont (k, n) printf("%d%c", f[rt][k].w, "\n "[k < n]);
}