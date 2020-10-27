#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

const int nsz = 1e5;
int ts, n, m, a[nsz + 5], b[nsz + 5], fm[nsz + 5];
num ans;

void inline solve() {
	ans = 0;
	scanf("%d%d", &n, &m);
	cont (i, n) scanf("%d", &a[i]), fm[a[i]] = i;
	cont (i, m) scanf("%d", &b[i]);
	int r = 0;
	cont (i, m) {
		int cur = b[i];
		if (fm[cur] > r) {
			ans += (fm[cur] - i) * 2 + 1;
			r = fm[cur];
		} else ans += 1;
	}
	printf("%lld\n", ans);
}

int main() {
	scanf("%d", &ts);
	cont (cs, ts) {
		solve();
	}
}