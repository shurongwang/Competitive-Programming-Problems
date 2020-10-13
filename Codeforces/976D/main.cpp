#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e3;
int n, d[nsz + 5];
set< pair<int, int> > est;
vector< pair<int, int> > ans;

void inline link(int u, int v) {
	if (est.find(make_pair(u, v)) != est.end()) return;
	est.insert(make_pair(u, v)), est.insert(make_pair(v, u));
	ans.push_back(make_pair(u, v));
}

int main() {
	scanf("%d", &n);
	cont (i, n) scanf("%d", &d[i]);
	for (int l = 1, r = n, del = 0; l <= r; del = d[l], ++l, --r) {
		circ (u, del + 1, d[l]) circ (v, del + 1, d[r] + 1) if (u != v) link(u, v);
	}
	printf("%d\n", int(ans.size()));
	loop (i, ans.size()) printf("%d %d\n", ans[i].first, ans[i].second);
}