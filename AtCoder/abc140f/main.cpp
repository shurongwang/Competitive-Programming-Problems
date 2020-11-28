#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int ksz = 18, nsz = 1 << ksz;
int ts, n, k, a[nsz + 5];
vector<int> b;
multiset<int, greater<int> > s;

int inline get() {
	if (!s.size()) return -1;
	int w = *s.begin();
	s.erase(s.begin());
	return w;
}

void inline ins(int w) {
	if (w > 0) s.insert(w);
}

int main() {
	scanf("%d", &k);
	n = 1 << k;
	cont (i, n) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1), reverse(a + 1, a + n + 1);
	if (n > 1 && a[1] == a[2]) { printf("No\n"); return 0; }
	s.insert(k);
	circ (i, 2, n) {
		int w = get();
		vector<int> d;
		if (w == -1) { printf("No"); return 0; }
		ins(w - 1);
		d.push_back(w - 1);
		for (; i <= n && a[i] == a[i + 1]; ++i) {
			w = get();
			if (w == -1) { printf("No"); return 0; }
			ins(w - 1);
			d.push_back(w - 1);
		}
		loop (i, d.size()) ins(d[i]);
	}
	printf("Yes\n");
}