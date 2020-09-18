#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 30;
int ts, n, m, k, a[nsz + 5][nsz + 5], ans;
vector<int> d[2 * nsz + 5];

int inline appear_most(vector<int> &a) {
	sort(all(a));
	int cnt = 0, res = 0;
	loop (i, a.size()) {
		cnt += 1;
		if (i == a.size() - 1 || a[i] != a[i + 1]) {
			res = max(res, cnt);
			cnt = 0;
		}
	}
	return res;
}

void inline solve() {
	scanf("%d%d", &n, &m);
	cont (i, n) cont (j, m) scanf("%d", &a[i][j]);
	k = n + m - 1, ans = 0;
	cont (i, n) cont (j, m) {
		int k1 = i + j - 1, k2 = k - k1 + 1;
		d[min(k1, k2)].push_back(a[i][j]);
	}
	cont (i, k) {
		if ((k & 1) && i == k / 2 + 1) continue;
		ans += d[i].size() - appear_most(d[i]);
	}
	cont (i, k) d[i].clear();
	printf("%d\n", ans);
}

int main() {
	scanf("%d", &ts);
	cont (cs, ts) {
		solve();
	}
}