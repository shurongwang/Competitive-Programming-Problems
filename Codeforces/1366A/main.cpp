#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

int ts, a, b;

bool inline chk(int k) {
	if (min(a, b) < k) return 0;
	return a + b - 2 * k >= k;
}

void inline solve() {
	scanf("%d%d", &a, &b);
	int l = 0, r = min(a, b) + 1, md = (l + r) >> 1;
	for (; r - l > 1; md = (l + r) >> 1) {
		(chk(md) ? l : r) = md;
	}
	printf("%d\n", l);
}

int main() {
	scanf("%d", &ts);
	cont (cs, ts) {
		solve();
	}
}