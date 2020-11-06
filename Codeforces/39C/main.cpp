#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 4e3;
int n, m, l[nsz + 5], r[nsz + 5], fm[nsz + 5][nsz + 5], dp[nsz + 5][nsz + 5], pre[nsz + 5][nsz + 5];
vector<int> to[nsz + 5], res;

void inline discretize() {
	static int d[2 * nsz + 5];
	cont (i, n) d[++m] = l[i], d[++m] = r[i];
	sort(d + 1, d + m + 1), m = unique(d + 1, d + m + 1) - d - 1;
	cont (i, n) l[i] = lower_bound(d + 1, d + m + 1, l[i]) - d, r[i] = lower_bound(d + 1, d + m + 1, r[i]) - d;
}

void inline find_solution() {
	static pair<int, int> stk[nsz + 5];
	int ss = 0;
	stk[ss++] = make_pair(1, m);
	for (; ss;) {
		pair<int, int> cur = stk[--ss];
		int l = cur.first, r = cur.second, k = pre[l][r];
		if (fm[l][r]) res.push_back(fm[l][r]);
		if (l == r || !k) continue;
		stk[ss++] = make_pair(l, k), stk[ss++] = make_pair(k, r);
	}
}

bool inline upd(int &a, int b) {
	if (a < b) { a = b; return 1; }
	return 0;
}

int main() {
	scanf("%d", &n);
	cont (i, n) {
		int o, r;
		scanf("%d%d", &o, &r);
		::l[i] = o - r, ::r[i] = o + r;
	}
	discretize();
	cont (i, n) to[l[i]].push_back(r[i]), fm[l[i]][r[i]] = i;
	cont (i, m) sort(all(to[i]));
	circ (len, 2, m) {
		for (int l = 1, r = len; r <= m; ++l, ++r) {
			if (upd(dp[l][r], dp[l + 1][r])) pre[l][r] = l + 1;
			if (upd(dp[l][r], dp[l][r - 1])) pre[l][r] = r - 1;
			loop (i, to[l].size()) {
				int k = to[l][i];
				if (k >= r) break;
				if (upd(dp[l][r], dp[l][k] + dp[k][r])) pre[l][r] = k;
			}
			dp[l][r] += bool(fm[l][r]);
		}
	}
	find_solution();
	printf("%d\n", dp[1][m]);
	loop (i, res.size()) printf("%d%c", res[i], "\n "[i + 1 < res.size()]);
}