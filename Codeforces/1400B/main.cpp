
#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

int ts, v1, v2, c1, c2, w1, w2, ans;

void inline solve() {
	scanf("%d%d%d%d%d%d", &v1, &v2, &c1, &c2, &w1, &w2);
	ans = 0;
	if (w1 > w2) swap(w1, w2), swap(c1, c2);
	circ (k1, 0, c1) {
		if (k1 * w1 > v1) break;
		int k2 = min(c2, (v1 - k1 * w1) / w2);
		int k3 = min(c1 - k1, v2 / w1), k4 = min(c2 - k2, (v2 - k3 * w1) / w2);
		ans = max(ans, k1 + k2 + k3 + k4);
	}
	printf("%d\n", ans);
}

int main() {
	scanf("%d", &ts);
	cont (cs, ts) {
		solve();
	}
}