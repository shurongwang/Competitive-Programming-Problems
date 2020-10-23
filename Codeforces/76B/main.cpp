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
const int inf = 0x3f3f3f3f;
int n, m, tmp, a[nsz + 5], b[nsz + 5], mn[nsz + 5], ans;
int dp[nsz + 5][2];
vector<int> to[nsz + 5];

void inline upd(int &a, int b) {
	if (a > b) a = b;
}

bool calc(int d, int cd) {
	return d == inf ? 0 : d != cd;
}

int main() {
	scanf("%d%d%d%d", &n, &m, &tmp, &tmp);
	cont (i, n + m) {
		int p;
		scanf("%d", &p);
		(i <= n ? a[i] : b[i - n]) = p;
	}
	cont (i, n) {
		int p = a[i], id = lower_bound(b + 1, b + m + 1, p) - b, d1 = inf, d2 = inf;
		if (id == m + 1) --id;
		d1 = abs(a[i] - b[id]);
		if (id != 1) d2 = abs(a[i] - b[id - 1]);
		if (d1 >= d2) to[i].push_back(id - 1);
		if (d1 <= d2) to[i].push_back(id);
	}
	memset(mn, inf, sizeof(mn));
	cont (i, n) {
		if (to[i].size() == 2) continue;
		int id = to[i][0], d = abs(a[i] - b[id]);
		if (d < mn[id]) {
			if (mn[id] != inf) ans += 1;
			mn[id] = d;
		} else if (d > mn[id]) ans += 1;
	}
	
	memset(dp, inf, sizeof(dp));
	int o = 0, x = 1;
	dp[o][0] = dp[o][1] = 0;
	int p = -1;
	cont (i, n) if (to[i].size() == 2) {
		int id = to[i][0], d = abs(a[i] - b[id]), d1 = inf;
		if (p != -1 && to[p][1] == id) {
			d1 = abs(a[p] - b[id]);
			upd(dp[x][0], dp[o][0] + calc(mn[id], d));
			upd(dp[x][0], dp[o][1] + calc(min(mn[id], d1), d));
		} else upd(dp[x][0], min(dp[o][0], dp[o][1]) + calc(mn[id], d));
		id = to[i][1], d = abs(a[i] - b[id]);
		upd(dp[x][1], min(dp[o][0], dp[o][1]) + calc(mn[id], d));
		
		p = i;
		swap(o, x);
		memset(dp[x], inf, sizeof(dp[x]));
	}
	ans += min(dp[o][0], dp[o][1]);
	printf("%d\n", ans);
	return 0;
}