#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 5e5, asz = 5e5 + 1;
const int inf = 0x3f3f3f3f;
int n, q, a[nsz + 5], cnt[asz + 5], ans[nsz + 5];
vector<int> p[asz + 5], id[nsz + 5];

struct segment {
	int l, r, id;
	
	segment() {}
	segment(int l, int r, int id): l(l), r(r), id(id) {}
	
	bool inline operator < (const segment &b) { return l != b.l ? l < b.l : r < b.r; }
};
segment s[nsz + 5];

struct fenwick_tree {
	int tr[nsz + 5];
	
	void inline init() {
		cont (i, n) tr[i] = 1;
		cont (i, n) if (i + (i & -i) <= n) tr[i + (i & -i)] += tr[i];
	}
	
	void inline upd(int u, int w) {
		for (; u <= n; u += u & -u) tr[u] += w;
	}
	
	int inline qry(int l, int r) { return qry(r) - qry(l - 1); }
	int inline qry(int u) {
		int res = 0;
		for (; u > 0; u -= u & -u) res += tr[u];
		return res;
	}
};
fenwick_tree f;

struct segment_tree {
	#define md ((l + r) >> 1)
	#define lp ls[u], l, md
	#define rp rs[u], md + 1, r
	
	int sz, rt, ls[2 * nsz + 5], rs[2 * nsz + 5];
	int r1[2 * nsz + 5], r2[2 * nsz + 5], del[2 * nsz + 5];
	pair<int, int> mx[2 * nsz + 5];
	
	void inline chg(int u, int w) {
		mx[u].first += w, del[u] += w;
	}
	
	void inline down(int u) {
		if (!del[u]) return;
		int &w = del[u];
		chg(ls[u], w), chg(rs[u], w);
		w = 0;
	}
	
	void inline init() { init(rt, 1, n); }
	void init(int &u, int l, int r) {
		u = ++sz, r1[u] = r2[u] = -1, mx[u] = make_pair(-inf, -1);
		if (l == r) return;
		init(lp), init(rp);
	}
	
	void upd_w(int el, int er, int w, int u = 1, int l = 1, int r = n) {
		if (l >= el && r <= er) return (void) (chg(u, w));
		down(u);
		if (el <= md) upd_w(el, er, w, lp);
		if (er > md) upd_w(el, er, w, rp);
		mx[u] = max(mx[ls[u]], mx[rs[u]]);
	}
	
	void set_w(int id, pair<int, int> w, int u = 1, int l = 1, int r = n) {
		if (l == r) return (void) (mx[u] = w);
		down(u);
		id <= md ? set_w(id, w, lp) : set_w(id, w, rp);
		mx[u] = max(mx[ls[u]], mx[rs[u]]);
	}
	
	pair<int, int> inline qry_w() { return mx[rt]; }
	
	int qry_r1(int w, int u = 1, int l = 1, int r = n) {
		if (l == r) return l;
		int p = -1;
		if (r1[ls[u]] >= w && (p = qry_r1(w, lp)) != -1) return p;
		if (r1[rs[u]] >= w && (p = qry_r1(w, rp)) != -1) return p;
		return p;
	}
	
	int qry_r2(int el, int er, int w, int u = 1, int l = 1, int r = n) {
		if (l == r) return l;
		int p = -1;
		if (el <= md && r2[ls[u]] >= w && (p = qry_r2(el, er, w, lp)) != -1) return p;
		if (er > md  && r2[rs[u]] >= w && (p = qry_r2(el, er, w, rp)) != -1) return p;
		return p;
	}
	
	void set_r1(const segment&s, int u = 1, int l = 1, int r = n) {
		if (l == r) return (void) (r1[u] = s.r);
		s.l <= md ? set_r1(s, lp) : set_r1(s, rp);
		r1[u] = max(r1[ls[u]], r1[rs[u]]);
	}
	
	void pop_r1(int id, int u = 1, int l = 1, int r = n) {
		if (l == r) return (void) (r1[u] = -1);
		id <= md ? pop_r1(id, lp) : pop_r1(id, rp);
		r1[u] = max(r1[ls[u]], r1[rs[u]]);
	}
	
	void set_r2(const segment &s, int u = 1, int l = 1, int r = n) {
		if (l == r) return (void) (r2[u] = s.r);
		s.l <= md ? set_r2(s, lp) : set_r2(s, rp);
		r2[u] = max(r2[ls[u]], r2[rs[u]]);
	}
	
	int at(int id, int u = 1, int l = 1, int r = n) {
		if (l == r) return mx[u].first;
		down(u);
		return id <= md ? at(id, lp) : at(id, rp);
	}
	
	int at_r2(int id, int u = 1, int l = 1, int r = n) {
		if (l == r) return r2[u];
		down(u);
		return id <= md ? at_r2(id, lp) : at_r2(id, rp);
	}
};
segment_tree tr;

struct link_list {
	int pre[nsz + 5], nxt[nsz + 5];
	
	void inline del(int u) {
		link(pre[u], nxt[u]);
	}
	
	void inline link(int u, int v) {
		if (v) pre[v] = u;
		if (u) nxt[u] = v;
	}
};
link_list ls;

bool inline by_r(int i, int j) { return s[i].r < s[j].r; }

void inline activate(int id) {
	int l = s[id].l, r = s[id].r;
	tr.set_r1(s[id]);
	::id[l].pop_back();
	tr.set_r2(::id[l].size() ? s[::id[l].back()] : segment(l, -1, -1));
	tr.set_w(l, make_pair(f.qry(l, r), id));
}

void inline abandon(int id) {
	int l = s[id].l;
	tr.pop_r1(l);
	tr.set_w(l, make_pair(-inf, -1));
	ls.del(id);
}

void inline init() {
	cont (i, n) p[a[i] += 1].push_back(i);
	cont (i, q) id[s[i].l].push_back(i);
	cont (i, n) if (id[i].size()) sort(all(id[i]), by_r);
	int mx_r = 0, pre = 0;
	f.init(), tr.init();
	cont (l, n) if (id[l].size()) {
		int cur = id[l].back(), r = s[cur].r;
		if (r > mx_r) activate(cur), ls.link(pre, cur), pre = cur, mx_r = r;
		else tr.set_r2(s[cur]);
	}
}

void inline solve() {
	for (int c = asz; c >= 1; --c) {
		for (pair<int, int> cur = tr.qry_w(); cur.first - c >= 0; cur = tr.qry_w()) {
			int id = cur.second, pre = ls.pre[id], nxt = ls.nxt[id], lst = pre;
			int l = s[id].l, r = nxt ? s[nxt].l - 1 : n, w = pre ? s[pre].r + 1 : 0;
			ans[id] = c, abandon(id);
			for (int cl, id; l <= r && (cl = tr.qry_r2(l, r, w)) != -1; l = s[id].l + 1, w = s[id].r + 1, lst = id) {
				id = ::id[cl].back();
				activate(id), ls.link(lst, id);
			}
			ls.link(lst, nxt);
		}
		loop (i, p[c].size()) {
			int r = ::p[c][i], l = tr.qry_r1(r);
			f.upd(r, -1);
			if (l != -1) tr.upd_w(l, r, -1);
		}
	}
}

int main() {
	scanf("%d%d", &n, &q);
	cont (i, n) scanf("%d", &a[i]);
	cont (i, q) {
		int l, r;
		scanf("%d%d", &l, &r);
		s[i] = segment(l, r, i);
	}
	init();
	solve();
	cont (i, q) printf("%d\n", ans[i]);
}