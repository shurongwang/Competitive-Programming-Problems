#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 5e3, mx = 1e4;
const num inf = 0x3f3f3f3f3f3f3f3f;
bool umai[nsz + 5];
int n, d, cnt;
num f[mx + 5], sum;
vector<string> roasted_sheep;

struct sheep {
	int w;
	string s;
	
	sheep() {}
	sheep(int w, const string &s) { this->w = w, this->s = s; }
	
	bool inline operator < (const sheep &b) const { return w < b.w; }
};
sheep a[nsz + 5];

void inline upd(num &a, num b) {
	if (a > b) a = b;
}

int main() {
	freopen("addict.in", "r", stdin);
	freopen("addict.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin >> n >> d;
	cont (i, n) {
		int w;
		string s;
		cin >> s >> w;
		a[i] = sheep(w, s);
	}
	sort(a + 1, a + n + 1);
	cont (i, mx) f[i] = inf;
	cont (i, n) {
		int w = a[i].w;
		num val = inf;
		circ (k, max(0, w - d), w) upd(val, f[k] + 1);
		if (val == inf) break;
		for (int k = mx; k >= w; --k) upd(f[k], f[k - w] + val);
		umai[i] = 1;
	}
	cont (i, n) if (umai[i]) {
		cnt += 1, sum += f[a[i].w];
		roasted_sheep.push_back(a[i].s);
	}
	cout << cnt << ' ' << sum << ln;
	sort(all(roasted_sheep));
	loop (i, roasted_sheep.size()) cout << roasted_sheep[i] << ln;
	return 0;
}