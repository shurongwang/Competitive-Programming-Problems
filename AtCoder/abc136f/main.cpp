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
const int mod = 998244353;
typedef modulo<mod> rem;

const int nsz = 2e5;
int n, dm, a[nsz + 5];
rem pw[nsz + 5], ans;
pair<int, int> p[nsz + 5];
map<int, int> to;

struct fenwick_tree {
	int tr[nsz + 5];
	
	void inline clear() {
		memset(tr, 0, sizeof(tr));
	}
	
	void inline upd(int u, int w) {
		for (; u <= n; u += u & -u) tr[u] += w;
	}
	
	int inline qry(int l, int r) { return l <= r ? qry(r) - qry(l - 1) : 0; }
	int inline qry(int u) {
		int r = 0;
		for (; u > 0; u -= u & -u) r += tr[u];
		return r;
	}
};
fenwick_tree tr;

void inline discretize() {
	cont (i, n) to[p[i].second] = 0;
	foreach (it, to) it->second = ++dm;
	cont (i, n) a[i] = to[p[i].second];
}

void inline power_init(int n) {
	pw[0] = 1;
	cont (i, n) pw[i] = pw[i - 1] * 2;
}

int main() {
	scanf("%d", &n);
	cont (i, n) scanf("%d%d", &p[i].first, &p[i].second);
	sort(p + 1, p + n + 1);
	discretize();
	power_init(n);
	cont (i, n) {
		rem cur = pw[n] - 1;
		cur -= pw[i - 1] - 1;
		cur -= pw[n - i] - 1;
		cur -= pw[a[i] - 1] - 1;
		cur -= pw[n - a[i]] - 1;
		ans += cur;
	}
	cont (i, n) {
		rem cur = 0;
		tr.upd(a[i], 1);
		cur += pw[tr.qry(1, a[i] - 1)] - 1;
		cur += pw[tr.qry(a[i] + 1, n)] - 1;
		ans += cur;
	}
	tr.clear();
	for (int i = n; i >= 1; --i) {
		rem cur = 0;
		tr.upd(a[i], 1);
		cur += pw[tr.qry(1, a[i] - 1)] - 1;
		cur += pw[tr.qry(a[i] + 1, n)] - 1;
		ans += cur;
	}
	printf("%d\n", ans.w);
}