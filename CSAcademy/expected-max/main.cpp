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

const int nsz = 20, msz = 10, ksz = 30, msksz = (1 << msz) - 1, dom = 1 / rem(1e6);
short lg[msksz + 5];
int n, m, sum, full;
rem p[nsz + 5][msz + 5][5], dp[msksz + 5][ksz + 5], f[2][msksz + 5][ksz + 5], ans;

void inline init() {
	loop (i, msz) lg[1 << i] = i;
}

void inline solve() {
	int o = 0, x = 1;
	f[o][0][0] = 1;
	loop (i, n) {
		circ (mx, 0, sum) {
			memset(dp, 0, sizeof(dp));
			circ (S, 0, full) dp[S][0] = f[o][S][mx];
			loop (j, m) circ (w, 0, sum) circ (S, 0, full) {
				if (!(S >> j & 1)) cont (k, 3) dp[S | (1 << j)][w + k] += dp[S][w] * p[i + 1][j + 1][k];
			}
			circ (w, 0, sum) circ (S, 0, full) f[x][S][max(mx, w)] += dp[S][w];
		}
		swap(o, x);
		memset(f[x], 0, sizeof(f[x]));
	}
	circ (mx, 0, sum) ans += f[o][full][mx] * mx;
}

int main() {
	init();
	scanf("%d%d", &n, &m);
	sum = 3 * m, full = (1 << m) - 1;
	cont (k, 3) {
		cont (j, m) cont (i, n) scanf("%d", &p[i][j][k].w), p[i][j][k] *= dom;
	}
	solve();
	printf("%d\n", ans.w);
}