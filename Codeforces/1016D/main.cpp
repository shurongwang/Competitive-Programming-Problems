#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e2, lgsz = 29;
int n, m, r[nsz + 5], c[nsz + 5], r0[nsz + 5], c0[nsz + 5], a[nsz + 5][nsz + 5], ans[nsz + 5][nsz + 5];

bool inline solve(int *r, int *c, int a[nsz + 5][nsz + 5]) {
	int r1 = 0, c1 = 0;
	cont (i, n) r1 += r[i];
	cont (i, m) c1 += c[i];
	if (abs(r1 - c1) & 1) return 0;
	cont (i, n) cont (j, m) a[i][j] = 0;
	vector<int> pr, pc;
	cont (i, n) if (r[i]) pr.push_back(i);
	cont (i, m) if (c[i]) pc.push_back(i);
	if (pr.size() <= pc.size()) {
		loop (i, pr.size()) a[pr[i]][pc[i]] = 1;
		circ (i, pr.size(), int(pc.size()) - 1) a[1][pc[i]] = 1;
	} else {
		loop (i, pc.size()) a[pr[i]][pc[i]] = 1;
		circ (i, pc.size(), int(pr.size()) - 1) a[pr[i]][1] = 1;
	}
	return 1;
}

int main() {
	scanf("%d%d", &n, &m);
	cont (i, n) scanf("%d", &r[i]);
	cont (i, m) scanf("%d", &c[i]);
	circ (k, 0, lgsz) {
		cont (i, n) r0[i] = r[i] >> k & 1;
		cont (i, m) c0[i] = c[i] >> k & 1;
		if (!solve(r0, c0, a)) { printf("NO\n"); return 0; }
		cont (i, n) cont (j, m) ans[i][j] |= a[i][j] << k;
	}
	printf("YES\n");
	cont (i, n) cont (j, m) printf("%d%c", ans[i][j], "\n "[j < m]);
	
}