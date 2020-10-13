#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 2e5;
int n, m, a;
num t, sum, ans;

struct sheep {
	num hp, dmg;
	
	sheep() {}
	sheep(num hp, num dmg) {
		this->hp = hp, this->dmg = dmg;
	}
	
	bool inline operator < (const sheep &wtm) const { return hp - dmg > wtm.hp - wtm.dmg; }
};
sheep dat[nsz + 5];

void inline solve() {
	num res = sum, cnt = 0, lst = 0;
	sort(dat + 1, dat + n + 1);
	cont (i, n) {
		num hp = dat[i].hp, dmg = dat[i].dmg, del = hp - dmg;
		if (del > 0 && i <= m) res += del, ++cnt, lst = del;
	}
	ans = res;
	if (m) cont (i, n) {
		num hp = dat[i].hp, dmg = dat[i].dmg, del = hp - dmg, ndel = hp * t - dmg, cur = res;
		if (del > 0 && i <= m) cur -= del;
		else if (cnt + 1 > m) cur -= lst;
		cur += ndel;
		ans = max(ans, cur);
	}
}

int main() {
	scanf("%d%d%d", &n, &a, &m);
	t = 1 << a;
	cont (i, n) {
		int hp, dmg;
		scanf("%d%d", &hp, &dmg);
		dat[i] = sheep(hp, dmg);
		sum += dmg;
	}
	solve();
	printf("%lld\n", ans);
}