#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 5e3;
char s[nsz + 5];
int n, pre[4][nsz + 5], ans;

int inline qry(int *pre, int l, int r) {
	return pre[r] - pre[l - 1];
}

int main() {
	scanf("%d", &n);
	scanf("%s", s + 1);
	cont (i, n) {
		if (s[i] == 'A') ++pre[0][i];
		if (s[i] == 'T') ++pre[1][i];
		if (s[i] == 'C') ++pre[2][i];
		if (s[i] == 'G') ++pre[3][i];
		loop (c, 4) pre[c][i] += pre[c][i - 1];
	}
	cont (l, n) circ (r, l, n) {
		ans += qry(pre[0], l, r) == qry(pre[1], l, r) && qry(pre[2], l, r) == qry(pre[3], l, r);
	}
	printf("%d\n", ans);
}