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
	operator int() const { return w; }
	
	modulo() {}
	modulo(int w) { this->w = w; fix(); }
	template<class type> modulo(type w) { this->w = w % mod; fix(); }
	void inline fix() { if (w >= mod || w < -mod) w %= mod; if (w < 0) w += mod; }
	
	inline modulo  operator -  () const { return mod - w; }
	inline modulo& operator += (const modulo &b) { if ((w += b.w) >= mod) w -= mod; return *this; }
	inline modulo& operator -= (const modulo &b) { if ((w -= b.w) < 0) w += mod; return *this; }
	inline modulo& operator *= (const modulo &b) { w = (unsigned long long) w * b.w % mod; return *this; }
	inline modulo& operator /= (const modulo &b) { return *this *= inv(b); }
	friend modulo operator + (const modulo& a, const modulo& b) { return modulo(a) += b; }
	template<class type> friend modulo operator + (const modulo &a, const type &b) { return modulo(a) += b; }
	template<class type> friend modulo operator + (const type &a, const modulo &b) { return modulo(a) += b; }
	friend modulo operator - (const modulo& a, const modulo& b) { return modulo(a) -= b; }
	template<class type> friend modulo operator - (const modulo &a, const type &b) { return modulo(a) -= b; }
	template<class type> friend modulo operator - (const type &a, const modulo &b) { return modulo(a) -= b; }
	friend modulo operator * (const modulo& a, const modulo& b) { return modulo(a) *= b; }
	template<class type> friend modulo operator * (const modulo &a, const type &b) { return modulo(a) *= b; }
	template<class type> friend modulo operator * (const type &a, const modulo &b) { return modulo(a) *= b; }
	friend modulo operator / (const modulo& a, const modulo& b) { return modulo(a) /= b; }
	template<class type> friend modulo operator / (const modulo &a, const type &b) { return modulo(a) /= b; }
	template<class type> friend modulo operator / (const type &a, const modulo &b) { return modulo(a) /= b; }
	
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

const int nsz = 300;
char s[nsz + 5];
int n, C0, C1, f[nsz + 5][nsz + 5];
rem ans, g[2][nsz + 5][nsz + 5];

void inline upd(int i, int c0, int c1, int c) {
	if (c == 0) f[i][c0 + 1] = max(f[i][c0 + 1], c1);
	if (c == 1) f[i][c0] = max(f[i][c0], c1 + 1);
}

void inline solve() {
	memset(f, -1, sizeof(f)), f[0][0] = 0;
	loop (i, n) {
		int s1 = s[i + 1] ^ 48, s2 = s[i + 2] ^ 48;
		circ (c0, 0, C0) if (f[i][c0] >= 0) {
			int c1 = f[i][c0];
			upd(i + 2, c0, c1, s1);
			upd(i + 2, c0, c1, s2);
			if (c0 > 0) upd(i + 1, c0 - 1, c1, s1);
			if (c1 > 0) upd(i + 1, c0, c1 - 1, s1);
			f[i + 1][c0] = max(f[i + 1][c0], c1);
		}
	}
	g[0][0][0] = 1;
	for (int i = n, o = 0, x = 1; i >= 0; --i) {
		rem val;
		if (i && (s[i] ^ 48)) circ (c0, 0, C0) circ (c1, 0, C1) if ((val = g[o][c0][c1]))
			g[x][c0][c1] += val, g[o][c0 + 1][c1] += val;
		if (i && (s[i] ^ 49)) circ (c0, 0, C0) circ (c1, 0, C1) if ((val = g[o][c0][c1]))
			g[x][c0][c1] += val, g[o][c0][c1 + 1] += val;
		circ (c0, 0, C0) circ (c1, 0, f[i][c0]) ans += g[o][c0][c1];
		swap(o, x), memset(g[x], 0, sizeof(g[x]));
	}
	ans -= 1;
}

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	cont (i, n) (s[i] == '0' ? C0 : C1) += 1;
	solve();
	printf("%d\n", ans.w);
}