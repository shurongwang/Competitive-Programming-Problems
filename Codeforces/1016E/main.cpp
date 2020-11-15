#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;
typedef double             f32;

using namespace std;

const int nsz = 2e5;
int n, m;
f32 sl, sr, sy, pre[nsz + 5];
pair<f32, f32> d[nsz + 5];

struct point {
	f32 x, y;
	
	point() {}
	point(f32 x, f32 y): x(x), y(y) {}
	
	friend inline ostream& operator << (ostream &out, const point &p) { return out << '(' << p.x << ',' << p.y << ')'; }
};

struct line {
	f32 a, b, c;
	
	line() {}
	line(f32 x1, f32 y1, f32 x2, f32 y2): a(y2 - y1), b(x1 - x2), c(a * -x1 + b * -y1) {}
	
	f32 inline at_x(f32 x) { return -(a * x + c) / b; }
	f32 inline at_y(f32 y) { return -(b * y + c) / a; }
	
	friend inline ostream& operator << (ostream &out, const line &l) { return out << l.a << "x" << (l.b < 0 ? '\0' : '+') << l.b << "y" << (l.c < 0 ? '\0' : '+') << l.c << "=0"; }
};

f32 inline sum(int l, int r) { return l > r ? 0.0 : pre[r] - pre[l - 1]; }

f32 inline l_of(int id, const point &p) { return line(d[id].first, 0, p.x, p.y).at_y(sy); }

f32 inline r_of(int id, const point &p) { return line(d[id].second, 0, p.x, p.y).at_y(sy); }

f32 inline qry(const point &p) {
	int l, r, md, pl, pr;
	f32 k = (p.y - sy) / p.y;
	{
		l = 0, r = n, md = (l + r) >> 1;
		for (; r - l > 1; md = (l + r) >> 1) (r_of(md, p) >= sl ? r : l) = md;
		pl = r;
	} {
		l = 1, r = n + 1, md = (l + r) >> 1;
		for (; r - l > 1; md = (l + r) >> 1) (l_of(md, p) <= sr ? l : r) = md;
		pr = l;
	}
	if (pl > pr) return 0.0;
	if (pl == pr) return max(0.0, min(sr, r_of(pr, p)) - max(sl, l_of(pl, p)));
	return k * sum(pl + 1, pr - 1) + (r_of(pl, p) - max(l_of(pl, p), sl)) + (min(r_of(pr, p), sr) - l_of(pr, p));
}

int main() {
	scanf("%lf%lf%lf%d", &sy, &sl, &sr, &n);
	cont (i, n) scanf("%lf%lf", &d[i].first, &d[i].second);
	cont (i, n) pre[i] = pre[i - 1] + d[i].second - d[i].first;
	scanf("%d", &m);
	cont (i, m) {
		point p;
		scanf("%lf%lf", &p.x, &p.y);
		printf("%.8lf\n", qry(p));
	}
}