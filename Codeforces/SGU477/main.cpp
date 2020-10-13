#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 5e3;
int n, m, k, p1[nsz + 5], p2[nsz + 5], r1[nsz + 5], r2[nsz + 5];
int sum = -1, res1 = -1, res2 = -1;

void inline calc(int n, int *p, int *res) {
	vector<int> d;
	cont (i, n - 1) {
		int len = p[i + 1] - p[i];
		d.push_back((len - 1) / 2 + 1);
	}
	sort(all(d));
	cont (i, n) res[i] = -1;
	res[0] = 1;
	loop (i, d.size()) {
		if (i + 1 == d.size() || d[i] != d[i + 1]) res[i + 1] = d[i];
	}
}

int inline overlap(const pair<int, int> a, const pair<int, int> b) {
	return max(0, min(a.second, b.second) - max(a.first, b.first));
}

int inline calc(const vector<pair<int, int> > &d1, const vector<pair<int, int> > &d2) {
	int res = 0;
	for (int i = 0, j = 0; i < d1.size() && j < d2.size();) {
		res = max(res, overlap(d1[i], d2[j]));
		++(d1[i].second <= d2[j].second ? i : j);
	}
	return res;
}

bool inline chk(int r1, int r2, int &total) {
	int s1 = 0, s2 = 0;
	static pair<int, int> d1[nsz + 5], d2[nsz + 5];
	cont (i, n) {
		int l = p1[i] - r1, r = p1[i] + r1;
		if (s1 && d1[s1 - 1].second >= l) d1[s1 - 1].second = r;
		else d1[s1++] = make_pair(l, r);
	}
	cont (i, m) {
		int l = p2[i] - r2, r = p2[i] + r2;
		if (s2 && d2[s2 - 1].second >= l) d2[s2 - 1].second = r;
		else d2[s2++] = make_pair(l, r);
	}
	int mx = 0;
	for (int i = 0, j = 0; i < s1 && j < s2;) {
		mx = max(mx, overlap(d1[i], d2[j]));
		++(d1[i].second <= d2[j].second ? i : j);
	}
	total = s1 + s2;
	return mx <= k;
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	cont (i, n) scanf("%d", &p1[i]);
	cont (i, m) scanf("%d", &p2[i]);
	calc(n, p1, r1), calc(m, p2, r2);
	for (int i = n, j = 0; i >= 0; --i) if (r1[i] != -1) {
		for (; j <= m; ++j) if (r2[j] != -1) {
			int total;
			if (chk(r1[i], r2[j], total)) {
				if (sum == -1 || total < sum) sum = total, res1 = r1[i], res2 = r2[j];
			} else break;
		}
	}
	if (sum == -1) printf("No solution\n");
	else printf("%d %d\n", res1, res2);
	return 0;
}