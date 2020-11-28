#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e5, lgsz = 59;
typedef bitset<nsz + 1> bits;
int n;
num a[nsz + 5], ans;
bits b[lgsz + 5];

int inline high_bit(const bits &w) {
	int l = -1, r = nsz + 1, md = (l + r) >> 1, cnt = w.count();
	for (; r - l > 1; md = (l + r) >> 1) {
		((w << md).count() == cnt ? l : r) = md;
	}
	return nsz - l;
}

struct linear_basis {
	map<int, bits> b;
	
	bits inline chk(bits w) {
		for (; w.count();) {
			int k = high_bit(w);
			if (b.find(k) != b.end()) w ^= b[k];
			else return w;
		}
		return w;
	}
	
	void inline ins(bits w) {
		for (; w.count();) {
			int k = high_bit(w);
			if (b.find(k) != b.end()) w ^= b[k];
			else { b[k] = w; break; }
		}
	}
};
linear_basis dat;

bool inline solution_exist(const bits &w) {
	return !(w.count() == 1 && w[0] == 1);
}

int main() {
	scanf("%d", &n);
	cont (i, n) scanf("%lld", &a[i]);
	circ (k, 0, lgsz) cont (i, n) b[k][i] = a[i] >> k & 1;
	for (int k = lgsz; k >= 0; --k) {
		bits w = b[k];
		if (w.count() % 2 == 0) {
			w[0] = 1;
			if (solution_exist(dat.chk(w))) {
				dat.ins(w);
				ans += 2ull << k;
			}
		} else ans += 1ull << k;
	}
	printf("%lld\n", ans);
}