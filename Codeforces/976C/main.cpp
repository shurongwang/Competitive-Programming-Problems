#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 3e5;
int n, ss, stk[nsz + 5];

struct segment {
	int l, r, id;
	
	segment() {}
	segment(int l, int r) {
		this->l = l, this->r = r;
	}
	
	bool inline operator < (const segment &b) const { return l != b.l ? l < b.l : r > b.r; }
};
segment a[nsz + 5];

int main() {
	scanf("%d", &n);
	cont (i, n) scanf("%d%d", &a[i].l, &a[i].r), a[i].id = i;
	sort(a + 1, a + n + 1);
	cont (i, n) {
		for (; ss && a[stk[ss - 1]].r < a[i].r; --ss);
		if (ss) {
			printf("%d %d\n", a[i].id, a[stk[ss - 1]].id);
			return 0;
		}
		stk[ss++] = i;
	}
	printf("-1 -1\n");
}