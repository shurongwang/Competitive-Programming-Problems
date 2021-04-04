#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e5, mod = 1e9 + 7, dsz = 4;
int n, m, d[nsz + 5];

struct matrix {
	int n, m, d[dsz + 5][dsz + 5];
	
	matrix(int n = 0, int m = 0, bool e = 0) {
		this->n = n, this->m = m;
		loop (i, n) {
			loop (j, m) {
				d[i][j] = (i == j) & e;
			}
		}
	}
	
	matrix(vector< vector<int> > a) {
		n = a.size(), m = a[0].size();
		loop (i, n) {
			loop (j, m) {
				d[i][j] = a[i][j];
			}
		}
	}
	
	int* operator [] (int id) {
		return d[id];
	}
};
matrix a = matrix({
	{1, 0, 1},
	{2, 1, 2},
	{1, 1, 2},
}),
b = matrix({
	{1, 0, 0},
	{2, 1, 0},
	{1, 1, 1},
}),
res = matrix(3, 1);

matrix inline operator * (matrix a, matrix b) {
	matrix res(a.n, b.m);
	loop (i, a.n) {
		loop (j, b.m) {
			loop (k, a.m) {
				res[i][j] = (res[i][j] + (num) a[i][k] * b[k][j] % mod) % mod;
			}
		}
	}
	return res;
}

matrix inline qpow(matrix a, int p) {
	matrix res(a.n, a.m, 1);
	for (; p; p >>= 1) {
		if (p & 1) {
			res = res * a;
		}
		a = a * a;
	}
	return res;
}

int main() {
	scanf("%d%d", &n, &m);
	cont (i, m) {
		scanf("%d", &d[i]);
		++d[i];
	}
	res[0][0] = 1;
	cont (i, m) {
		res = qpow(a, d[i] - d[i - 1] - 1) * res;
		res = b * res;
	}
	res = qpow(a, n - d[m]) * res;
	printf("%d\n", res[2][0]);
}
