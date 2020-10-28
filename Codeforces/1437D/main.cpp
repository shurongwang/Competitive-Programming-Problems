#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 2e5;
int ts, n, a[nsz + 5], cnt[nsz + 5], ans;

int inline calc(int fm) {
	int to = fm;
	for (; to <= n && (to == n || a[to] < a[to + 1]); ++to);
	return to - fm + 1;
}

void inline solve() {
	scanf("%d", &n);
	cont (i, n) scanf("%d", &a[i]);
	cnt[ans] = 1;
	for (int it = 2; it <= n; ++ans) {
		cont (k, cnt[ans]) {
			int cur = calc(it);
			it += cur, cnt[ans + 1] += cur;
			if (it > n) break;
		}
	}
	printf("%d\n", ans);
}

void inline clear() {
	circ (k, 0, ans) cnt[k] = 0;
	ans = 0;
}

int main() {
	scanf("%d", &ts);
	cont (cs, ts) {
		solve();
		clear();
	}
}