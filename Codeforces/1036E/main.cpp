#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e3;
int n;
num ans;

struct point {
	num x, y;
	
	point() {}
	point(int x, int y): x(x), y(y) {}
	
	bool inline operator < (const point &b) const { return x != b.x ? x < b.x : y < b.y; }
};

num inline gcd(num a, num b) { return !b ? a : gcd(b, a % b); }

struct segment {
	num a, b, c, lx, rx, ly, ry;
	
	segment() {}
	segment(int a, int b, int c, int lx, int rx, int ly, int ry): a(a), b(b), c(c), lx(lx), rx(rx), ly(ly), ry(ry) {}
	segment(int x1, int y1, int x2, int y2) {
		a = y2 - y1, b = x1 - x2, c = a * -x1 + b * -y1;
		lx = min(x1, x2), rx = max(x1, x2), ly = min(y1, y2), ry = max(y1, y2);
	}
	
	friend inline bool intersect_int(const segment &a, const segment &b, point &p) {
		if (a.a * b.b - b.a * a.b == 0) return 0;
		num D = a.a * b.b - a.b * b.a, Dx = a.b * b.c - a.c * b.b, Dy = a.c * b.a - a.a * b.c;
		num l, r, x = Dx / D, y = Dy / D;
		if (Dx % D || Dy % D) return 0;
		l = max(a.lx, b.lx), r = min(a.rx, b.rx);
		if (l > r || l > x || x > r) return 0;
		l = max(a.ly, b.ly), r = min(a.ry, b.ry);
		if (l > r || l > y || y > r) return 0;
		p = point(x, y);
		return 1;
	}
	
	friend inline int count_int(const segment &a) {
		num g = gcd(abs(a.a), abs(a.b));
		if (a.a) {
			num k = abs(a.a) / g;
			return (a.ry - a.ly) / k + 1;
		} else return a.rx - a.lx + 1;
	}
};
segment a[nsz + 5];

int main() {
	scanf("%d", &n);
	cont (i, n) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		a[i] = segment(x1, y1, x2, y2);
		ans += count_int(a[i]);
	}
	cont (i, n) {
		point p;
		set<point> s;
		cont (j, i - 1) if (intersect_int(a[i], a[j], p)) s.insert(p);
		ans -= s.size();
	}
	printf("%lld\n", ans);
}