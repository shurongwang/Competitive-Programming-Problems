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
int n, m1, m2, sr, sc, se, sum, dx[nsz + 5], dy[nsz + 5];
int a1[nsz + 5], a2[nsz + 5], a3[nsz + 5], a4[nsz + 5];
num ans;

struct fenwick_tree {
	int tr[nsz + 5];
	
	void inline upd(int u, int w) {
		for (; u <= m2; u += u & -u) tr[u] += w;
	}
	
	int inline qry(int u) {
		int r = 0;
		for (; u > 0; u -= u & -u) r += tr[u];
		return r;
	}
	int inline qry(int l, int r) { return qry(r) - qry(l - 1); }
};
fenwick_tree tr;

struct segment {
	int id, l, r;
	
	segment() {}
	segment(int id, int l, int r) {
		this->id = id, this->l = l, this->r = r;
	}
	
	bool inline operator < (const segment &b) const {
		return id != b.id ? id < b.id : l < b.l;
	}
};
segment r[nsz + 5], c[nsz + 5];

struct event {
	int t, l, r;
	
	event() {}
	event(int t, int l = 0, int r = 0) {
		this->t = t, this->l = l, this->r = r;
	}
	
	bool inline operator < (const event &b) const {
		return t != b.t ? t < b.t : r < b.r;
	}
};
event ev[nsz + 5];

void inline init() {
	sort(dx + 1, dx + m1 + 1), m1 = unique(dx + 1, dx + m1 + 1) - dx - 1;
	sort(dy + 1, dy + m2 + 1), m2 = unique(dy + 1, dy + m2 + 1) - dy - 1;
	cont (i, n) {
		int x1 = a1[i], y1 = a2[i], x2 = a3[i], y2 = a4[i];
		x1 = lower_bound(dx + 1, dx + m1 + 1, x1) - dx;
		y1 = lower_bound(dy + 1, dy + m2 + 1, y1) - dy;
		x2 = lower_bound(dx + 1, dx + m1 + 1, x2) - dx;
		y2 = lower_bound(dy + 1, dy + m2 + 1, y2) - dy;
		if (x1 == x2) {
			c[++sc] = segment(x1, y1, y2);
		} else {
			r[++sr] = segment(y1, x1, x2);
		}
	}
	sort(r + 1, r + sr + 1);
	sort(c + 1, c + sc + 1);
	int it = 0;
	cont (i, sr) {
		if (r[i].id == r[it].id && r[i].l <= r[it].r) {
			r[it].r = max(r[it].r, r[i].r);
		} else r[++it] = r[i];
	}
	sr = it, it = 0;
	cont (i, sc) {
		if (c[i].id == c[it].id && c[i].l <= c[it].r) {
			c[it].r = max(c[it].r, c[i].r);
		} else c[++it] = c[i];
	}
	sc = it;
}

int main() {
	scanf("%d", &n);
	cont (i, n) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
		if (x1 == x2) {
			dx[++m1] = x1, dy[++m2] = y1, dy[++m2] = y2;
		} else {
			dy[++m2] = y1, dx[++m1] = x1, dx[++m1] = x2;
		}
		a1[i] = x1, a2[i] = y1, a3[i] = x2, a4[i] = y2;
	}
	init();
	cont (i, sr) ans += dx[r[i].r] - dx[r[i].l] + 1;
	cont (i, sc) ans += dy[c[i].r] - dy[c[i].l] + 1;
	cont (i, sr) {
		ev[++se] = event(r[i].l, r[i].id);
		ev[++se] = event(r[i].r + 1, r[i].id, -1);
	}
	cont (i, sc) {
		ev[++se] = event(c[i].id, c[i].l, c[i].r);
	}
	sort(ev + 1, ev + se + 1);
	cont (i, se) {
		int l = ev[i].l, r = ev[i].r;
		if (r <= 0) {
			r += r == 0;
			tr.upd(l, r);
		} else {
			ans -= tr.qry(l, r);
		}
	}
	printf("%lld\n", ans);
}