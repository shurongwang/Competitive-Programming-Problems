#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 2e5, inf = 0x3f3f3f3f;
int n, m, k, t, a[nsz + 5], ans;

struct sheep {
	int l, r, d;
	
	sheep() {}
	sheep(int l, int r, int d): l(l), r(r), d(d) {}
	
	bool inline operator < (const sheep &b) const { return l < b.l; }
};
sheep b[nsz + 5];

bool inline chk(int rk) {
	int d = a[rk], res = m + 1;
	vector<sheep> cur;
	cont (i, k) if (b[i].d > d) cur.push_back(b[i]);
	loop (i, cur.size()) {
		int j = i, r = cur[i].r;
		for (; j + 1 < cur.size() && cur[j + 1].l <= r; ++j, r = max(r, cur[j].r));
		res += (r - cur[i].l + 1) << 1;
		i = j;
	}
	return res <= t;
}

void inline solve() {
	int l = 0, r = n + 1, md = (l + r) >> 1;
	for (; r - l > 1; md = (l + r) >> 1) {
		(chk(md) ? l : r) = md;
	}
	ans = l;
}

int main() {
	scanf("%d%d%d%d", &n, &m, &k, &t);
	cont (i, n) scanf("%d", &a[i]);
	a[0] = inf;
	sort(a + 1, a + n + 1), reverse(a + 1, a + n + 1);
	cont (i, k) {
		int l, r, d;
		scanf("%d%d%d", &l, &r, &d);
		b[i] = sheep(l, r, d);
	}
	sort(b + 1, b + k + 1);
	solve();
	printf("%d\n", ans);
}