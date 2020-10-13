#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e2;
int ts, n, k, a[nsz + 5];

void inline solve() {
	scanf("%d%d", &n, &k);
	cont (i, n) scanf("%d", &a[i]);
	int cnt = 0;
	a[n + 1] = -1;
	cont (i, n) if (a[i] != a[i + 1]) ++cnt;
	if (k >= cnt) { printf("1\n"); return; }
	if (k - 1 == 0) { printf("-1\n"); return; }
	cnt -= k;
	int r = (cnt - 1) / (k - 1) + 2;
	printf("%d\n", r);
}

int main() {
	scanf("%d", &ts);
	cont (cs, ts) {
		solve();
	}
}