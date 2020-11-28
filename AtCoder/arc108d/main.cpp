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

const int nsz = 1e3;
const char A = 'A', B = 'B';
int n;
rem ans;
string s;
vector<string> s1 = {"AAAA", "AAAB", "AABA", "AABB", "ABAB", "ABBB", "BBAB", "BBBB"};
vector<string> s2 = {"ABAA", "BABA", "BABB", "BBAA"};
vector<string> s3 = {"ABBA", "BBBA", "BAAA", "BAAB"};

void inline solve1() {
	bool f = 0;
	loop (i, s1.size()) if (s == s1[i]) f = 1;
	if (!f) return;
	ans = 1;
}

void inline solve2() {
	bool f = 0;
	loop (i, s2.size()) if (s == s2[i]) f = 1;
	if (!f) return;
	ans = pow(rem(2), n - 3);
}

void inline solve3() {
	bool f = 0;
	loop (i, s3.size()) if (s == s3[i]) f = 1;
	if (!f) return;
	static rem dp[nsz + 5][2];
	dp[1][0] = 1;
	circ (i, 2, n) {
		dp[i][0] = dp[i - 1][1];
		dp[i][1] = dp[i - 1][0] + dp[i - 1][1];
	}
	ans = dp[n][1];
}

int main() {
	ios::sync_with_stdio(0);
	cin >> n;
	if (n == 2) { cout << 1 << ln; return 0; }
	cont (i, 4) {
		char c;
		cin >> c;
		s += c;
	}
	solve1(), solve2(), solve3();
	cout << ans << ln;
}