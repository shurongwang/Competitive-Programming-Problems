#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 4e3;
const int inf = 0x3f3f3f3f;
bool vis[nsz + 5][nsz + 5];
int n, m, dmx, dmy, dx, dy, ans = inf;
vector<int> ax, ay;

struct pos {
	int x, y;
	
	pos() {}
	pos(int x, int y) { this->x = x, this->y = y; }
	
	friend inline bool operator <= (const pos &a, const pos &b) { return a.x <= b.x && a.y <= b.y; }
	
	friend inline bool operator < (const pos &a, const pos &b) { return a.x != b.x ? a.x < b.x : a.y < b.y; }
};
pos a[nsz + 5], b[nsz + 5];
vector<pos> d, stk;

int main() {
	scanf("%d%d", &n, &m);
	cont (i, n) scanf("%d%d", &a[i].x, &a[i].y);
	cont (i, m) scanf("%d%d", &b[i].x, &b[i].y);
	cont (i, n) cont (j, m) if (a[i] <= b[j]) {
		d.push_back(pos(b[j].x - a[i].x, b[j].y - a[i].y));
	}
	sort(all(d));
	stk.push_back(pos(-1, inf));
	loop (i, d.size()) {
		for (; stk.size() && stk.back().y <= d[i].y; stk.pop_back());
		stk.push_back(d[i]);
	}
	stk.push_back(pos(inf, -1));
	loop (i, stk.size() - 1) {
		ans = min(ans, stk[i].x + stk[i].y + 1);
		ans = min(ans, stk[i].x + 1 + stk[i + 1].y + 1);
	}
	printf("%d\n", ans);
}