#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

int n, m;
vector< pair<int, int> > ans;

void inline solve(int l, int r) {
	if (l == r) return;
	int len = r - l + 1, md = (l + r) >> 1;
	if (len & 1) {
		solve(l, md - 1), solve(md + 1, r);
		circ (i, l, md - 1) ans.push_back(make_pair(i, md - l + 1 + i));
	} else {
		solve(l, md), solve(md + 1, r);
		circ (i, l, md) ans.push_back(make_pair(i, md - l + 1 + i));
	}
}

int main() {
	scanf("%d", &n);
	for (m = 1; m <= n; m <<= 1);
	m >>= 1;
	solve(1, m), solve(n - m + 1, n);
	printf("%d\n", int(ans.size()));
	loop (i, ans.size()) {
		printf("%d %d\n", ans[i].first, ans[i].second);
	}
}