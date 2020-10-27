#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

template<int bas> struct number {
	int sz;
	vector<int> d;
	
	number() { sz = 0; }
	number(int a) {
		d.resize(sz = 1, a);
	}
	number(string s) {
		int len = this->len();
		sz = int(s.size()), d.resize(sz = sz / len + bool(sz % len), 0);
		for (int i = int(s.size()) - 1, k = 0; i >= 0; i -= len, ++k) {
			for (int j = len - 1; j >= 0; --j) {
				d[k] = d[k] * 10 + (i - j >= 0 ? s[i - j] ^ 48 : 0);
			}
		}
		this->fix();
	}
	
	inline int& operator [] (int id) { return d[id]; }
	inline const int operator [] (int id) const { return d[id]; }
	
	int inline len() const {
		int r = -1;
		for (int w = bas; w > 0; w /= 10, ++r);
		return r;
	}
	
	void inline init(int sz) {
		d.resize(this->sz = sz, 0);
	}
	
	void inline fix() {
		for (; sz && d.back() == 0; d.pop_back(), --sz);
	}
	
	friend inline number operator + (const number &a, const number &b) {
		number r;
		r.init(max(a.sz, b.sz) + 1);
		loop (i, r.sz - 1) {
			int cur = r[i] + (i < a.sz ? a[i] : 0) + (i < b.sz ? b[i] : 0);
			r[i + 1] = cur / bas, r[i] = cur % bas;
		}
		r.fix();
		return r;
	}
	friend inline number operator += (number &a, const number &b) { return a = a + b; }
	
	friend inline bool operator <= (const number &a, const number &b) {
		if (a.sz != b.sz) return a.sz < b.sz;
		for (int i = a.sz - 1; i >= 0; --i) if (a[i] != b[i]) return a[i] < b[i];
		return 1;
	}
	
	friend inline istream& operator >> (istream &in, number &a) {
		string s;
		in >> s;
		a = s;
		return in;
	}
	
	friend inline ostream& operator << (ostream &out, const number &a) {
		if (a.sz == 0) return out << '0';
		int len = a.len();
		out << a[a.sz - 1];
		for (int i = a.sz - 2; i >= 0; --i) out << setw(len) << setfill('0') << a[i];
		return out;
	}
};
typedef number<int(1e9)> nbr;

const int nsz = 100, msz = 50;
int n, m, p, s[nsz + 5];
nbr rk, f[nsz + 5][msz + 5];

nbr inline calc(int k, int sum) {
	return f[n - k][(p - sum % p) % p];
}

int main() {
	ios::sync_with_stdio(0);
	cin >> n >> m >> p >> rk;
	f[0][0] = 1;
	loop (i, n) loop (k, p) cont (j, m) {
		f[i + 1][(k + j) % p] += f[i][k];
	}
	int sum = 0;
	nbr cur = 0;
	cont (i, n) {
		for (++s[i], ++sum; cur + calc(i, sum) <= rk; cur += calc(i, sum), ++s[i], ++sum);
	}
	cont (i, n) cout << s[i] << "\n "[i < n];
}