#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int asz = 1e3;

struct TheNicePair {
	int ans, fm[asz + 5];
	vector<int> p;
	
	void inline prime_init(int to = asz) {
		static bool inp[asz + 5];
		circ (i, 2, to) {
			if (inp[i]) continue;
			p.push_back(i), fm[i] = int(p.size()) - 1;
			for (int j = i << 1; j <= asz; j += i) inp[j] = 1;
		}
	}
	
	int solve(vector<int> a) {
		prime_init();
		ans = -1;
		loop (l, a.size()) {
			int mx = 0;
			vector<int> cnt(p.size(), 0);
			circ (r, l, a.size() - 1) {
				int cur = a[r];
				loop (i, p.size()) {
					if (p[i] * p[i] > cur) break;
					if (cur % p[i]) continue;
					for (mx = max(mx, ++cnt[i]); cur % p[i] == 0; cur /= p[i]);
				}
				if (cur > 1) mx = max(mx, ++cnt[fm[cur]]);
				if (mx >= (r - l) / 2 + 1) ans = max(ans, r - l); 
			}
		}
		return ans;
	}
};