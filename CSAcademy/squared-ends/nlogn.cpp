#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e5, asz = 1e6;
const num inf = 0x3f3f3f3f3f3f3f3f;
int n, m, dm, a[nsz + 5], b[nsz + 5], d[nsz + 5];
num dp[2][nsz + 5], ans;

template<class type> struct line {
	type k, b;
	
	line(): k(0), b(inf) {}
	line(type k, type b): k(k), b(b) {}
	
	type inline operator () (type x) const { return k * x + b; }
};

template<class type> struct segment_tree {
	#define md ((l + r) >> 1)
	#define lp ls[u], l, md
	#define rp rs[u], md + 1, r
	
	int sz, rt, tm, p[nsz + 5], vr[2 * nsz + 5], ls[2 * nsz + 5], rs[2 * nsz + 5];
	line<type> t[2 * nsz + 5];
	
	type inline operator [] (int id) { return at(id); }
	
	bool inline out(int u) { return !u || vr[u] != tm; }
	
	void inline chg(int &u) {
		u || (u = ++sz);
		if (out(u)) t[u] = line<num>(), vr[u] = tm;
	}
	
	void inline init(int *p) { cont (i, dm) this->p[i] = p[i]; ++tm; }
	
	void inline upd_all(line<type> f) { upd(1, dm, f, rt, 1, dm); }
	void inline upd(int el, int er, line<type> f) { upd(el, er, f, rt, 1, dm); }
	void upd(int el, int er, line<type> f, int &u, int l, int r) {
		chg(u);
		if (l >= el && r <= er) {
			if (f(p[md]) < t[u](p[md])) swap(f, t[u]);
			if (f(p[l]) < t[u](p[l])) upd(el, er, f, lp);
			if (f(p[r]) < t[u](p[r])) upd(el, er, f, rp);
			return;
		}
		if (el <= md) upd(el, er, f, lp);
		if (er > md)  upd(el, er, f, rp);
	}
	
	type inline qry(int el, int er) { return qry(el, er, rt, 1, dm); }
	type qry(int el, int er, int u, int l, int r) {
		chg(u);
		type res = min(t[u](p[el]), t[u](p[er]));
		if (l >= el && r <= er) return res;
		if (!out(ls[u]) && el <= md) res = min(res, qry(el, er, lp));
		if (!out(rs[u]) && er > md)  res = min(res, qry(el, er, rp));
		return res;
	}
	
	type inline at(int id) { return at(id, rt, 1, dm); }
	type at(int id, int u, int l, int r) {
		if (out(u)) return inf;
		type res = t[u](p[id]);
		if (l == r) return res;
		res = min(res, id <= md ? at(id, lp) : at(id, rp));
		return res;
	}
};
segment_tree<num> tr;

void inline discretize() {
	cont (i, n) d[i] = a[i];
	sort(d + 1, d + n + 1), dm = unique(d + 1, d + n + 1) - d - 1;
	cont (i, n) b[i] = lower_bound(d + 1, d + dm + 1, a[i]) - d;
}

void inline solve() {
	int o = 0, x = 1;
	memset(dp, inf, sizeof(dp));
	dp[o][0] = 0;
	tr.init(d);
	tr.upd_all(line<num>(-2 * a[1], dp[o][0] + (num) a[1] * a[1]));
	cont (k, m) {
		cont (i, n) {
			if (dp[o][i] < inf) tr.upd_all(line<num>(-2 * a[i + 1], dp[o][i] + (num) a[i + 1] * a[i + 1]));
			dp[x][i] = tr[b[i]] + (num) a[i] * a[i];
		}
		swap(o, x);
		memset(dp[x], 0, sizeof(dp[x]));
		tr.init(d);
	}
	ans = dp[o][n];
}

int main() {
	scanf("%d%d", &n, &m);
	cont (i, n) scanf("%d", &a[i]);
	discretize();
	solve();
	printf("%lld\n", ans);
}