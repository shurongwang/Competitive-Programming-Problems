#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

template<int mod> struct modulo;
template<int mod> struct modulo_cplx;

template<int mod> struct modulo_cplx {
	modulo<mod> a, b, i2;
	
	modulo_cplx() {}
	modulo_cplx(modulo<mod> a, modulo<mod> b, modulo<mod> i2 = 0) { this->a = a, this->b = b; this->i2 = i2; }
	
	inline modulo_cplx  operator *  (const modulo_cplx &d) { return modulo_cplx(a * d.a + i2 * b * d.b, a * d.b + b * d.a, i2); }
	inline modulo_cplx& operator *= (const modulo_cplx &d) { return *this = *this * d; }
	
	friend inline modulo_cplx pow(const modulo_cplx &w, int p) {
		if (w.a == 0 && w.b == 0) return modulo_cplx(0, 0, w.i2);
		modulo_cplx a = w, r = modulo_cplx(1, 0, w.i2);
		for (; p > 0; a *= a, p >>= 1) if (p & 1) r *= a;
		return r;
	}
};

template<int mod> struct modulo {
	int w;
	operator int&() { return w; }
	operator int() const { return w; }
	
	modulo() {}
	modulo(int w, bool f = 0) { this->w = w; if (f) fix(); }
	void inline fix() { if (w >= mod || w < -mod) w %= mod; if (w < 0) w += mod; }
	
	inline modulo  operator -  () { w = mod - w; if (w >= mod) w -= mod; return *this; }
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
	
	friend inline modulo sqrt(const modulo &w) {
		int k = (mod - 1) / 2;
		assert(pow(w, k) == 1);
		modulo a = rand() % mod;
		for (; pow(a * a - w, k) != mod - 1; a = rand() % mod);
		modulo_cplx<mod> t(a, 1, a * a - w);
		modulo r = pow(t, (mod + 1) / 2).a;
		return min(int(r), int(mod - r));
	}
};
const int mod = 998244353, mod_root = 3;
typedef modulo<mod> rem;
typedef unsigned long long u64;

const int degsz = int(4e5);

template<class type> struct fourier_transform;
template<class type> struct poly;

template<class type> struct fourier_transform {
	int k, sz, rev[degsz + 5];
	u64 b[degsz + 5], pw[degsz + 5];
	
	void inline init(int to) {
		for (sz = 1, k = 0; sz <= to; sz <<= 1, ++k);
		if (k == 0) return;
		loop (i, sz) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	}
	
	void inline dft(poly<type> &a, int tp = 1) {
		a.set_deg(sz - 1);
		loop (i, sz) {
			b[i] = a[i];
			if (i > rev[i]) swap(b[i], b[rev[i]]);
		}
		for (int len = 1; len < sz; len <<= 1) {
			int w0 = pow(rem(mod_root), (mod - 1) / (len << 1));
			if (tp == -1) w0 = inv(rem(w0));
			pw[0] = 1;
			cont (i, len - 1) pw[i] = pw[i - 1] * w0 % mod;
			for (int l = 0; l < sz; l += len << 1) {
				u64 *p0 = b + l, *p1 = b + l + len, *w = pw, tmp;
				for (int i = 0; i < len; ++i, ++p0, ++p1, ++w) {
					tmp = *w * *p1 % mod;
					*p1 = *p0 + mod - tmp;
					*p0 += tmp;
				}
			}
		}
		loop (i, sz) a[i] = b[i] % mod;
		if (tp == -1) {
			rem rs = inv(rem(sz));
			loop (i, sz) a[i] *= rs;
		}
	}
};
fourier_transform<rem> ft;

template<class type> struct poly {
	int deg;
	vector<type> d;
	
	poly() { deg = 0; }
	poly(type a) { deg = 0, d.push_back(a); }
	poly(vector<type> a) { deg = int(a.size()) - 1, d = a; }
	
	void inline set_deg(int sz) { deg = sz, d.resize(sz + 1, 0); }
	
	void inline fix() { for (; d.size() && d.back() == 0; d.pop_back(), --deg); }
	
	inline type& operator [] (int id) { return d[id]; }
	inline type operator [] (int id) const { return d[id]; }
	
	inline type operator () (int x) const {
		if (x == 0) return d[0];
		int r = 0;
		for (int i = deg; i >= 0; --i) r *= x, r += d[i];
		return r;
	}
	
	friend inline poly operator + (const poly &a, const poly &b) {
		poly r; r.set_deg(max(a.deg, b.deg));
		circ (i, 0, r.deg) r[i] = (i <= a.deg ? a[i] : type(0)) + (i <= b.deg ? b[i] : type(0));
		return r;
	}
	friend inline poly operator +  (const poly &a, const type &b) { poly r = a; r[0] += b; return r; }
	friend inline poly operator +  (const type &a, const poly &b) { return b + a; }
	friend inline poly operator += (poly &a, const poly &b) { return a = a + b; }
	friend inline poly operator += (poly &a, const type &b) { return a = a + b; }
	
	friend inline poly operator - (const poly &a, const poly &b) {
		poly r; r.set_deg(max(a.deg, b.deg));
		circ (i, 0, r.deg) r[i] = (i <= a.deg ? a[i] : type(0)) - (i <= b.deg ? b[i] : type(0));
		return r;
	}
	friend inline poly operator -  (const poly &a, const type &b) { poly r = a; r[0] -= b; return r; }
	friend inline poly operator -  (const type &a, const poly &b) { poly r = b - a; circ (i, 0, r.deg) r[i] = -r[i]; return r; }
	friend inline poly operator -= (poly &a, const poly &b) { return a = a - b; }
	friend inline poly operator -= (poly &a, const type &b) { return a = a - b; }
	
	friend inline poly operator * (const poly &a, const poly &b) {
		poly f = a, g = b;
		ft.init(a.deg + b.deg);
		ft.dft(f), ft.dft(g);
		loop (i, ft.sz) f[i] *= g[i];
		ft.dft(f, -1);
		f.set_deg(a.deg + b.deg);
		return f;
	}
	friend inline poly operator *  (const poly &a, const type &b) { poly r = a; circ (i, 0, r.deg) r[i] *= b; return r; }
	friend inline poly operator *  (const type &a, const poly &b) { return b * a; }
	friend inline poly operator *= (poly &a, const poly &b) { return a = a * b; }
	friend inline poly operator *= (poly &a, const type &b) { return a = a * b; }
	
	friend inline poly operator / (const poly &a, const poly &b) {
		int sz = a.deg - b.deg;
		poly f = a, g = b;
		if (a.deg < b.deg) return poly(0);
		reverse(all(f.d)), reverse(all(g.d));
		f.set_deg(sz), g.set_deg(sz);
		f *= inv(g);
		f.set_deg(sz);
		reverse(all(f.d));
		return f;
	}
	friend inline poly operator /= (poly &a, const poly &b) { return a = a / b; }
	
	friend inline poly operator % (const poly &a, const poly &b) {
		poly r = a - b * (a / b);
		r.set_deg(b.deg - 1);
		return r;
	}
	friend inline poly operator %= (poly &a, const poly &b) { return a = a % b; }
	
	friend poly inv(const poly& a) {
		if (a.deg == 0) return inv(a[0]);
		int to = a.deg / 2;
		poly b, r;
		b.deg = to, b.d.assign(&a.d[0], &a.d[to + 2]);
		r = inv(b);
		
		b = a;
		ft.init(2 * a.deg);
		ft.dft(b), ft.dft(r);
		loop (i, ft.sz) r[i] *= (type(2) - r[i] * b[i]);
		ft.dft(r, -1);
		
		r.set_deg(a.deg);
		return r;
	}
	
	friend poly sqrt(const poly &a) {
		if (a.deg == 0) return sqrt(type(a[0]));
		int to = a.deg / 2;
		poly b, r;
		b.deg = to, b.d.assign(&a.d[0], &a.d[to + 2]);
		r = sqrt(b);
		
		r.set_deg(a.deg);
		r = (r + a * inv(r)) * inv(type(2));
		
		r.set_deg(a.deg);
		return r;
	}
	
	friend inline poly derivative(const poly &a) {
		if (a.deg == 0) return type(0);
		poly f;
		f.set_deg(a.deg);
		cont (i, a.deg) f[i - 1] = a[i] * type(i);
		return f;
	}
	
	friend inline poly integral(const poly &a) {
		poly f;
		f.set_deg(a.deg);
		circ (i, 0, a.deg - 1) f[i + 1] = a[i] / type(i + 1);
		return f;
	}
	
	friend inline poly log(const poly &a) {
		poly r;
		r = integral(derivative(a) * inv(a));
		r.set_deg(a.deg);
		return r;
	}
	
	friend inline poly exp(const poly &a) {
		if (a.deg == 0) return type(1);
		int to = a.deg / 2;
		poly b, r;
		b.deg = to, b.d.assign(&a.d[0], &a.d[to + 2]);
		r = exp(b);
		
		r.set_deg(a.deg);
		r = r - r * (log(r) - a);
		
		r.set_deg(a.deg);
		return r;
	}
	
	friend inline poly pow(const poly &a, int p) {
		int k = 0;
		circ (i, 0, a.deg) if (a[i] != 0) { k = i; break; }
		if (a[k] == 0 || k * p > a.deg) return poly(vector<rem>(a.deg + 1, 0));
		
		poly b;
		b.set_deg(a.deg - k);
		rem rs = inv(a[k]);
		circ (i, 0, a.deg - k) b[i] = a[i + k] * rs;
		rs = pow(a[k], p);
		
		poly r = exp(p * log(b));
		r.set_deg(a.deg);
		
		k *= p;
		for (int i = a.deg; i >= k; --i) r[i] = r[i - k] * rs;
		loop (i, k) r[i] = 0;
		return r;
	}
	
	friend inline poly pow(const poly &w, int p, const poly &mod) {
		if (p == 0) return poly(1);
		poly a = w, r = poly(1);
		for (; p > 0; a *= a, a %= mod, p >>= 1) if (p & 1) r *= a, r %= mod;
		return r;
	}
	
	friend inline ostream& operator << (ostream &out, const poly &a) {
		out << "{" << a[0];
		cont (i, a.deg) out << ',' << a[i];
		out << "}\n";
		return out;
	}
};

const int nsz = 1e5;
int n, m, a[nsz + 5], b[nsz + 5];
rem fac[nsz + 5], ifc[nsz + 5], ff[nsz + 5], ans;
poly<rem> f[nsz + 5], g;

void inline transfer() {
	sort(a + 1, a + n + 1);
	for (int i = 1, cnt = 1; i <= n; ++i, ++cnt) {
		if (a[i] != a[i + 1]) b[++m] = cnt, cnt = 0;
	}
}

rem inline C(int n, int m) { return fac[n] * ifc[m] * ifc[n - m]; }

void inline factorial_init(int n = nsz) {
	fac[0] = 1;
	cont (i, n) fac[i] = fac[i - 1] * rem(i);
	ifc[n] = inv(fac[n]);
	for (int i = n - 1; i >= 0; --i) ifc[i] = ifc[i + 1] * rem(i + 1);
	ff[0] = ff[1] = 1;
	circ (i, 2, n) ff[i] = ff[i - 2] * rem(i);
}

rem inline pair_up(int n, int k) {
	if (n < 2 * k) return 0;
	if (k == 0) return 1;
	return C(n, 2 * k) * ff[2 * k - 1];
}

poly<rem> solve(int l = 1, int r = m) {
	if (l == r) return f[l];
	int md = (l + r) >> 1;
	return solve(l, md) * solve(md + 1, r);
}

void inline poly_init() {
	cont (i, m) {
		vector<rem> cur(1, 1);
		cont (j, b[i] / 2) cur.push_back(pair_up(b[i], j));
		f[i] = cur;
	}
}

int main() {
	factorial_init();
	scanf("%d", &n);
	n *= 2;
	cont (i, n) scanf("%d", &a[i]);
	transfer();
	poly_init();
	g = solve();
	circ (k, 0, g.deg) {
		rem val = g[k] * pair_up(n - 2 * k, n / 2 - k);
		ans += rem(k & 1 ? -1 : +1, 1) * val;
	}
	printf("%d\n", ans.w);
}