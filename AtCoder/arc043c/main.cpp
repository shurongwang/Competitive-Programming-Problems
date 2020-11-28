#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e5;
int n, a[nsz + 5], b[nsz + 5], p[nsz + 5];
num sum;

struct fenwick_tree {
	int tr[nsz + 5];
	
	void inline clear() {
		memset(tr, 0, sizeof(tr));
	}
	
	void inline upd(int u, int w) {
		for (; u <= n; u += u & -u) tr[u] += w;
	}
	
	int inline qry(int l, int r) { return qry(r) - qry(l - 1); }
	int inline qry(int u) {
		int r = 0;
		for (; u > 0; u -= u & -u) r += tr[u];
		return r;
	}
};
fenwick_tree tr;

void inline rearrange_by(int n, int *a, int *b) {
	static int p[nsz + 5];
	cont (i, n) p[a[i]] = i;
	cont (i, n) a[p[b[i]]] = i;
}

int main() {
	scanf("%d", &n);
	cont (i, n) scanf("%d", &a[i]);
	cont (i, n) scanf("%d", &b[i]);
	cont (i, n) p[i] = a[i];
	rearrange_by(n, a, b);
	cont (i, n) {
		tr.upd(a[i], 1);
		sum += tr.qry(a[i] + 1, n);
	}
	if (sum & 1) {
		printf("-1\n");
		return 0;
	}
	tr.clear();
	num k = 0;
	cont (i, n) {
		int cur = tr.qry(a[i] + 1, n), w = a[i];
		tr.upd(a[i], 1);
		if (k + cur >= sum / 2) {
			sort(a + 1, a + i);
			int p = i - sum / 2 + k;
			for (int j = i; j > p; --j) a[j] = a[j - 1];
			a[p] = w;
			break;
		}
		k += cur;
	}
	cont (i, n) printf("%d%c", b[a[i]], "\n "[i < n]);
}