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

const int nsz = 2e5, inf = 0x3f3f3f3f;
int n, to[nsz + 5], p[nsz + 5], d[nsz + 5];
rem dp[nsz + 5];
pair<int, int> dat[nsz + 5];

int main() {
	scanf("%d", &n);
	cont (i, n) scanf("%d%d", &dat[i].first, &dat[i].second);
	sort(dat + 1, dat + n + 1);
	cont (i, n) p[i] = dat[i].first, d[i] = dat[i].second;
	int ss = 0, stk[nsz + 5];
	for (int i = n; i >= 1; --i) {
		for (to[i] = i; ss && p[stk[ss - 1]] < p[i] + d[i]; --ss) to[i] = max(to[i], to[stk[ss - 1]]);
		if (!ss) to[i] = n;
		stk[ss++] = i;
	}
	dp[n + 1] = 1;
	for (int i = n; i >= 1; --i) dp[i] = dp[i + 1] + dp[to[i] + 1];
	printf("%d\n", dp[1].w);
}