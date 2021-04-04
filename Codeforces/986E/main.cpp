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

const int nsz = 2e5, asz = 1e7, sqrt_asz = 3162;
int n, q, a[nsz + 5];
int rt = 1, pr[nsz + 5], dep[nsz + 5], siz[nsz + 5], hs[nsz + 5], top[nsz + 5], id[nsz + 5], fm[nsz + 5];
vector<int> p, dd, d[nsz + 5];

void inline merge(vector<int> &r, vector<int> &pl, vector<int> &pr, const vector<int> &a, const vector<int> &b) {
	int s1 = a.size(), s2 = b.size(), sz = s1 + s2;
	r.resize(sz), pl.resize(sz + 1), pr.resize(sz + 1);
	for (int i = 0, j = 0, k = 0; i < a.size() || j < b.size(); ++k) {
		pl[k] = i, pr[k] = j;
		r[k] = j == b.size() || i < a.size() && a[i] < b[j] ? a[i++] : b[j++];
	}
	pl[sz] = s1, pr[sz] = s2;
}

struct segment_tree {
	#define md ((l + r) >> 1)
	#define lp ls[u], l, md
	#define rp rs[u], md + 1, r
	
	int n, sz, rt;
	vector<int> ls, rs, fm;
	vector< vector<int> > w, pl, pr, sum;
	
	void inline up(int u) {
		merge(w[u], pl[u], pr[u], w[ls[u]], w[rs[u]]);
		sum[u].resize(w[u].size() + 1);
		loop (i, w[u].size()) sum[u][i + 1] = sum[u][i] + w[u][i];
	}
	
	void inline init(const vector<int> &w, const vector<int> &fm) {
		n = w.size();
		this->fm = fm;
		ls.resize(2 * n), rs.resize(2 * n);
		this->w.resize(2 * n), sum.resize(2 * n);
		pl.resize(2 * n), pr.resize(2 * n);
		build(w, rt, 1, n);
	}
	
	void build(const vector<int> &w, int &u, int l, int r) {
		u = ++sz;
		if (l == r) return (void) (this->w[u].push_back(w[l - 1]), sum[u].push_back(0), sum[u].push_back(w[l - 1]));
		build(w, lp), build(w, rp);
		up(u);
	}
	
	int inline qry(int el, int er, int mx) {
		el = lower_bound(all(fm), el) - fm.begin() + 1;
		er = lower_bound(all(fm), er + 1) - fm.begin();
		int k = lower_bound(all(w[rt]), mx + 1) - w[rt].begin();
		return el <= er ? qry(el, er, mx, k, rt, 1, n) : 0;
	}
	
	int qry(int el, int er, int mx, int k, int u, int l, int r) {
		if (l >= el && r <= er) return sum[u][k] + (w[u].size() - k) * mx;
		int res = 0;
		if (el <= md) res = qry(el, er, mx, pl[u][k], lp);
		if (er > md)  res += qry(el, er, mx, pr[u][k], rp);
		return res;
	}
};
vector<segment_tree> tr;

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

struct query {
	int u, v, w;
	
	query() {}
	query(int u, int v, int w): u(u), v(v), w(w) {}
};
query qy[nsz + 5];

void inline prime_init(int n = sqrt_asz) {
	static bool np[sqrt_asz + 5];
	for (int a = 2; a <= n; ++a) {
		if (np[a]) continue;
		p.push_back(a);
		for (int b = 2 * a; b <= n; b += a) np[b] = 1;
	}
}

void inline factorize(int a, vector<int> &d) {
	int cur = a;
	loop (i, p.size()) {
		int p = ::p[i];
		if (p * p > a || cur == 1) break;
		if (cur % p) continue;
		for (; cur % p == 0; cur /= p);
		d.push_back(p);
	}
	if (cur != 1) d.push_back(cur);
}

int inline log(int a, int p) {
	int r = 0;
	for (; a % p == 0; a /= p, ++r);
	return r;
}

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
	id[u] = ++t, fm[t] = u, top[u] = tp;
	if (!hs[u]) return;
	dfs2(hs[u], tp);
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (v == pr[u] || v == hs[u]) continue;
		dfs2(v, v);
	}
}

void inline init() {
	prime_init();
	cont (i, n) {
		factorize(a[i], d[i]);
		loop (j, d[i].size()) dd.push_back(d[i][j]);
	}
	sort(all(dd)), dd.erase(unique(all(dd)), dd.end());
	dfs1(), dfs2();
	tr.resize(dd.size());
	vector< vector<int> > w(dd.size()), fm(dd.size());
	cont (t, n) {
		int u = ::fm[t];
		loop (i, d[u].size()) {
			int p = d[u][i], id = lower_bound(all(dd), p) - dd.begin();
			w[id].push_back(log(a[u], p));
			fm[id].push_back(t);
		}
	}
	loop (i, dd.size()) tr[i].init(w[i], fm[i]);
}

int inline qry_route(int t, int u, int v, int mx) {
	int res = 0;
	for (; top[u] != top[v]; v = pr[top[v]]) {
		if (dep[top[u]] > dep[top[v]]) swap(u, v);
		res += tr[t].qry(id[top[v]], id[v], mx);
	}
	if (dep[u] > dep[v]) swap(u, v);
	res += tr[t].qry(id[u], id[v], mx);
	return res;
}

int main() {
	scanf("%d", &n);
	cont (i, n - 1) {
		int u, v;
		scanf("%d%d", &u, &v);
		g.link(u, v);
	}
	cont (i, n) scanf("%d", &a[i]);
	init();
	scanf("%d", &q);
	cont (i, q) {
		int u, v, w;
		rem res = 1;
		vector<int> d;
		scanf("%d%d%d", &u, &v, &w);
		factorize(w, d);
		loop (j, d.size()) {
			int p = d[j];
			vector<int>::iterator it = lower_bound(all(dd), p);
			if (it == dd.end() || *it != p) continue;
			res *= pow(rem(p), qry_route(it - dd.begin(), u, v, log(w, p)));
		}
		printf("%d\n", res.w);
	}
}