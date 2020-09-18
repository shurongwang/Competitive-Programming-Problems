#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

int ts, n, p, m;

void inline solve() {
	scanf("%d%d%d", &n, &p, &m);
	int rl = p, rr = p;
	cont (i, m) {
		int l, r;
		scanf("%d%d", &l, &r);
		int cl = max(l, rl), cr = min(r, rr);
		if (cl <= cr) rl = min(rl, l), rr = max(rr, r);
	}
	printf("%d\n", rr - rl + 1);
}

int main() {
	scanf("%d", &ts);
	cont (cs, ts) {
		solve();
	}
}