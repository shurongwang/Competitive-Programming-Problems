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
		int n = a.n, m = a.m, r = -1;
		type f = 1;
		loop (c, m) {
			int p = -1;
			circ (i, r + 1, n - 1) if (a[i][c]) { p = i; break; }
			if (p == -1) { f = 0; continue; }
			if (++r != p) swap(a[r], a[p]), f = -f;
			circ (i, r + 1, n - 1) {
				type d = a[i][c] / a[r][c];
				if (d != 0) circ (j, c, m - 1) a[i][j] -= d * a[r][j];
			}
			if (r == n - 1) break;
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
