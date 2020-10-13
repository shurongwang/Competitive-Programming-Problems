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
const long double eps = 1e-9;
int ts, n, m;
long double a[nsz + 5], t1[nsz + 5], t2[nsz + 5];

long double inline time_1(long double p) {
	int id = lower_bound(a + 1, a + n + 1, p) - a - 1;
	double t = t1[id] + (p - a[id]) / (id + 1);
	return t;
}

long double inline time_2(long double p) {
	int id = lower_bound(a + 1, a + n + 1, p + eps) - a;
	long double t = t2[id] + (a[id] - p) / (n - id + 2);
	return t;
}

void inline solve() {
	scanf("%d%d", &n, &m);
	cont (i, n) scanf("%Lf", &a[i]);
	long double p = 0, v = 1;
	cont (i, n) {
		long double s = a[i] - p;
		t1[i] = t1[i - 1] + s / v;
		p = a[i], v += 1;
	}
	a[n + 1] = m;
	p = m, v = 1;
	for (int i = n; i >= 1; --i) {
		long double s = p - a[i];
		t2[i] = t2[i + 1] + s / v;
		p = a[i], v += 1;
	}
	long double l = 0, r = m, md = (l + r) / 2;
	for (; r - l > eps; md = (l + r) / 2) (time_1(md) < time_2(md) ? l : r) = md;
	printf("%.8Lf\n", time_1(l));
}

void inline clear() {
	circ (i, 0, n + 1) a[i] = t1[i] = t2[i] = 0;
}

int main() {
	scanf("%d", &ts);
	cont (cs, ts) {
		solve();
		clear();
	}
}