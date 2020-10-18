#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e5;
int n, a[nsz + 5], to[nsz + 5];
int s1, s2, stk1[nsz + 5], stk2[nsz + 5];
vector<pair<int, int>> ans;

void inline no_way() {
	printf("-1\n");
	exit(0);
}

int inline row(int id) { return id; }

int inline col(int id) { return id; }

int main() {
	scanf("%d", &n);
	cont (i, n) scanf("%d", &a[i]);
	for (int i = n; i >= 1; --i) {
		if (a[i] == 0) continue;
		else if (a[i] == 1) stk1[s1++] = i;
		else if (a[i] == 2) {
			if (!s1) no_way();
			to[i] = stk1[--s1];
			stk2[s2++] = i;
		} else if (a[i] == 3) {
			if (!s1 && !s2) no_way();
			if (s2) to[i] = stk2[--s2];
			else if (s1) to[i] = stk1[--s1];
			stk2[s2++] = i;
		}
	}
	cont (i, n) {
		if (a[i] == 0) continue;
		else if (a[i] == 1) ans.push_back({row(i), col(i)});
		else if (a[i] == 2) ans.push_back({row(to[i]), col(i)});
		else if (a[i] == 3) ans.push_back({row(i), col(i)}), ans.push_back({row(i), col(to[i])});
	}
	printf("%d\n", int(ans.size()));
	loop (i, ans.size()) {
		printf("%d %d\n", ans[i].first, ans[i].second);
	}
}