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

template<class type> struct matrix {
	int n, m;
	vector< vector<type> > d;
	
	matrix() {}
	matrix(int n, int m, int w = 0) {
		this->n = n, this->m = m;
		d.resize(n, vector<type>(m, 0));
		loop (i, min(n, m)) d[i][i] = w;
	}
	matrix(vector< vector<type> > a) {
		n = a.size(), m = a[0].size(), d = a;
	}
	
	vector<type>& operator [] (int id) { return d[id]; }
	const vector<type>& operator [] (int id) const { return d[id]; }
	
	friend inline matrix operator * (const matrix &a, const matrix &b) {
		matrix r(a.n, b.m);
		loop (i, a.n) loop (k, a.m) if (a[i][k]) loop (j, b.m) r[i][j] += a[i][k] * b[k][j];
		return r;
	}
	friend inline matrix operator *= (matrix &a, const matrix &b) { return a = a * b; }
	
	friend inline ostream& operator << (ostream &out, const matrix &a) {
		loop (i, a.n) {
			out << "{";
			if (a.m) out << a[i][0];
			cont (j, a.m - 1) out << ',' << a[i][j];
			out << "}\n";
		}
		return out;
	}
	
	friend inline type eliminate(matrix &a) {
		int n = a.n, m = a.m;
		type f = 1;
		loop (i, n) {
			int r = -1;
			circ (k, i, n - 1) if (a[k][i]) { r = k; break; }
			if (r == -1) return 0;
			if (i != r) swap(a[r], a[i]), f = -f;
			circ (k, i + 1, n - 1) {
				type p = a[k][i] / a[i][i];
				circ (j, i, m - 1) a[k][j] -= p * a[i][j];
			}
		}
		for (int i = n - 1; i >= 0; --i) circ (k, 0, i - 1) {
			type p = a[k][i] / a[i][i];
			a[k][i] = 0;
			circ (j, n, m - 1) a[k][j] -= p * a[i][j];
		}
		return f;
	}
	
	friend inline type det(matrix a) {
		type r = eliminate(a);
		loop (i, a.n) r *= a[i][i];
		return r;
	}
	
	friend inline matrix inv(matrix a) {
		int n = a.n;
		matrix r(n, n);
		loop (i, n) loop (j, n) a.d[i].push_back(i == j);
		a.m += n;
		if (!eliminate(a)) return matrix(0, 0);
		loop (i, n) {
			type p = 1 / a[i][i];
			circ (j, n, a.m - 1) r[i][j - n] = a[i][j] * p;
		}
		return r;
	}
	
	friend inline matrix pow(matrix a, num p) {
		matrix r(a.n, a.m, 1);
		for (; p > 0; a *= a, p >>= 1) if (p & 1) r *= a;
		return r;
	}
};
typedef matrix<rem> mat;

const int nsz = 3e4, alphsz = 10;
char s[nsz + 5];
int n, m, q;
mat t[alphsz + 5], pre[2][nsz + 5];

void inline init() {
	loop (c, m - 1) {
		t[c] = mat(m, m, 1);
		loop (i, m) t[c][i][c] = 1;
	}
	pre[0][0] = pre[1][0] = mat(m, m, 1);
	cont (i, n) pre[0][i] = pre[0][i - 1] * t[s[i] - 'a'], pre[1][i] = inv(pre[0][i]);
}

rem inline qry(int l, int r) {
	rem res = 0;
	mat a(1, m);
	a[0][m - 1] = 1;
	a *= pre[1][l - 1];
	a *= pre[0][r];
	loop (i, m - 1) res += a[0][i];
	return res;
}

int main() {
	scanf("%s", s + 1);
	scanf("%d", &q);
	n = strlen(s + 1), m = alphsz;
	init();
	cont (i, q) {
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", qry(l, r).w);
	}
}