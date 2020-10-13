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
const int mod = int(1e9) + 7;
typedef modulo<mod> rem;

const int nsz = 1e5;
char s1[nsz + 5], s2[nsz + 5];
int n;
rem pw2[nsz + 5], pw10[nsz + 5];
rem a4[nsz + 5], a7[nsz + 5], sum[nsz + 5], sq_sum[nsz + 5], res[nsz + 5];

rem inline f(char *s, int len = n) {
	for (int i = len - 1; i >= 0; --i) {
		if (s[i] == '7') {
			s[i] = '4';
			if (i == 0) return res[n - 1];
		} else if (s[i] == '4') { s[i] = '7'; break; }
	}
	int pk = -1;
	rem cur = 0, pre = 0, res = 0;
	for (int k = len - 1; k >= 0; --k) {
		cur += pw10[k] * 4;
		if (s[len - k - 1] == '4') continue;
		if (pk != -1) res += (pre + a7[pk]) * (cur + a4[k]);
		pk = k, pre = cur;
		res += cur * cur * (pw2[k] - 1);
		if (k > 0) res += ::res[k - 1] + sum[k - 1] * cur * 2;
		res -= (a4[k] + a7[k]) * cur;
		cur += pw10[k] * 3;
	}
	return res;
}

int main() {
	scanf("%s", s1);
	scanf("%s", s2);
	n = strlen(s1);
	sum[0] = 11, sq_sum[0] = 65, res[0] = 28;
	pw2[0] = 1, pw10[0] = 1, a4[1] = 4, a7[1] = 7;
	cont (i, n) {
		pw2[i] = pw2[i - 1] * 2;
		pw10[i] = pw10[i - 1] * 10;
		a4[i + 1] = a4[i] * 10 + 4;
		a7[i + 1] = a7[i] * 10 + 7;
		sum[i] = sum[i - 1] * 20 + pw2[i] * 11;
		sq_sum[i] = sq_sum[i - 1] * 200 + sum[i - 1] * 220 + pw2[i] * 65;
		res[i] = (res[i - 1] + sq_sum[i - 1]) * 100 + sum[i - 1] * 220 + 56 * pw2[i];
		res[i] -= a7[i + 1] * 4 + a4[i + 1] * 7 - 28;
	}
	printf("%d\n", f(s2) - f(s1));
}