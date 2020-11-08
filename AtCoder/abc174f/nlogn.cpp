#include <bits/stdc++.h>

#define ln                '\n'
#define all(dat)          dat.begin(), dat.end()
#define loop(i, to)       for (int i = 0; i < to; ++i)
#define cont(i, to)       for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)   for (int i = fm; i <= to; ++i)
#define foreach(it, dat)  for (__typeof(dat.begin()) it = dat.begin(); it != dat.end(); ++it)

typedef long long num;
typedef unsigned long long msk;

using namespace std;

const int nsz = 1e5;
int ts, n, a[nsz + 5], ct[nsz + 5];

void inline solve() {
	vector< pair<int, int> > b;
	cont (i, n) {
		b.push_back(make_pair(a[i], i));
		ct[i] = 0;
	}
	sort(all(b));
	
//	loop (i, b.size()) cerr << b[i] << "\n "[i + 1 < b.size()];
	
	int cnt = 0;
	for (; b.size() > 1; ++cnt) {
		int mx = b[b.size() - 1].first, to = mx - b[0].first, id = b[b.size() - 1].second;
		int pos = upper_bound(all(b), make_pair(to, id)) - b.begin();
		if (pos <= 0 || b.size() > 2 && pos <= 1) {
//			cerr << "exit" << ln;
			break;
		}
		b.insert(b.begin() + pos, make_pair(to, id));
		b.pop_back();
		b.erase(b.begin());
		++ct[id];
//		if (cnt == 0) cerr << pos - 1 << ' ' << b.size() << ln;
		
//		cerr << "OK" << ln;
	}
	cout << n - cnt << ln;
//	cerr << ln;
}

int main() {
	// freopen("snakes.in", "r", stdin);
	// freopen("snakes.out", "w", stdout);
	scanf("%d", &ts);
//	ts =1;
	scanf("%d", &n);
	cont (i, n) scanf("%d", &a[i]);
	solve();
	cont (cs, ts - 1) {
		int k;
		scanf("%d", &k);
		cont (i, k) {
			int p, w;
			scanf("%d%d", &p, &w);
			a[p] = w;
		}
		solve();
	}
	return 0;
}