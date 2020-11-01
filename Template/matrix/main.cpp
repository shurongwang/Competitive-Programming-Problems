#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

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
	
	friend inline matrix operator + (const matrix &a, const matrix &b) { return matrix(a) += b; }
	inline matrix operator += (const matrix &b) {
		loop (i, n) loop (j, m) d[i][j] += b[i][j];
		return *this;
	}
	
	friend inline matrix operator - (const matrix &a, const matrix &b) { return matrix(a) -= b; }
	inline matrix operator -= (const matrix &b) {
		loop (i, n) loop (j, m) d[i][j] -= b[i][j];
		return *this;
	}
	
	friend inline matrix operator * (const matrix &a, const type &b) { return matrix(a) *= b; }
	friend inline matrix operator * (const type &a, const matrix &b) { return matrix(b) *= a; }
	inline matrix operator *= (const type &b) {
		loop (i, n) loop (j, m) d[i][j] *= b;
		return *this;
	}
	
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