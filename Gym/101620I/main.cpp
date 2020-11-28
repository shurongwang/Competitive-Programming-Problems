#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e5;
int n, q, a[nsz + 5], l[nsz + 5];
pair<int, int> ans[nsz + 5];

struct segment_tree {
	#define ls (u << 1)
	#define rs (u << 1 | 1)
	#define md ((l + r) >> 1)
	#define lp ls, l, md
	#define rp rs, md + 1, r
	
	int mn[4 * nsz + 5], del[4 * nsz + 5];
	
	void inline down(int u) {
		if (!del[u]) return;
		mn[ls] += del[u], del[ls] += del[u];
		mn[rs] += del[u], del[rs] += del[u];
		del[u] = 0;
	}
	
	void upd(int el, int er, int w, int u = 1, int l = 1, int r = n) {
		if (l >= el && r <= er) return (void) (mn[u] += w, del[u] += w);
		down(u);
		if (el <= md) upd(el, er, w, lp);
		if (er > md)  upd(el, er, w, rp);
		mn[u] = min(mn[ls], mn[rs]);
	}
	
	int find_pre(int to, int u = 1, int l = 1, int r = n) {
		if (l == r) return l;
		down(u);
		if (md + 1 <= to && mn[rs] == 0) {
			int p = find_pre(to, rp);
			if (p != -1) return p;
		}
		if (mn[ls] == 0) return find_pre(to, lp);
		return -1;
	}
	
	int find_suf(int to, int u = 1, int l = 1, int r = n) {
		if (l == r) return l;
		down(u);
		if (md >= to && mn[ls] == 0) {
			int p = find_suf(to, lp);
			if (p != -1) return p;
		}
		if (mn[rs] == 0) return find_suf(to, rp);
		return -1;
	}
};
segment_tree tr;

struct query {
	int l, r, id;
	
	query() {}
	query(int l, int r, int id): l(l), r(r), id(id) {}
	
	bool inline operator < (const query &b) const { return r < b.r; }
};
query qy[nsz + 5];

struct compare1 {
	bool inline operator () (const query &a, const query &b) const {
		return a.l != b.l ? a.l < b.l : a.id < b.id;
	}
};
priority_queue<query, vector<query>, compare1> s;

void solve() {
	static int stk1[nsz + 5], stk2[nsz + 5];
	int s1 = 0, s2 = 0;
	sort(qy + 1, qy + q + 1);
	cont (i, n) {
		for (; s1 && a[stk1[s1]] < a[i]; --s1) tr.upd(stk1[s1 - 1] + 1, stk1[s1], -a[stk1[s1]]);
		tr.upd(stk1[s1] + 1, i, +a[i]), stk1[++s1] = i;
		for (; s2 && a[stk2[s2]] > a[i]; --s2) tr.upd(stk2[s2 - 1] + 1, stk2[s2], +a[stk2[s2]]);
		tr.upd(stk2[s2] + 1, i, -a[i]), stk2[++s2] = i;
		if (i > 1) tr.upd(1, i - 1, -1);
		for (static int it = 1; it <= q && qy[it].r == i; ++it) s.push(query(qy[it].l, qy[it].r, qy[it].id));
		for (int p = tr.find_suf(1); s.size() && s.top().l >= p; s.pop()) ans[s.top().id] = make_pair(tr.find_pre(s.top().l), i);
	}
}

int main() {
	scanf("%d", &n);
	cont (i, n) scanf("%d", &a[i]);
	scanf("%d", &q);
	cont (i, q) {
		int l, r;
		scanf("%d%d", &l, &r);
		qy[i] = query(l, r, i);
	}
	solve();
	cont (i, q) {
		printf("%d %d\n", ans[i].first, ans[i].second);
	}
}