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
int ts, n, a[nsz + 5], b[nsz + 5], c[nsz + 5];

void inline solve() {
	scanf("%d", &n);
	cont (i, n) scanf("%d", &a[i]);
	cont (i, n) scanf("%d", &b[i]);
	cont (i, n) scanf("%d", &c[i]);
	int pre = -1, first = -1;
	cont (i, n) {
		if (a[i] != pre && (i != n || a[i] != first)) pre = a[i];
		else if (b[i] != pre && (i != n || b[i] != first)) pre = b[i];
		else if (c[i] != pre && (i != n || c[i] != first)) pre = c[i];
		if (i == 1) first = pre;
		printf("%d ", pre);
	}
	printf("\n");
}

int main() {
	scanf("%d", &ts);
	cont (cs, ts) {
		solve();
	}
}