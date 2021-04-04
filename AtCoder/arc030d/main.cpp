#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 2e5, trsz = nsz + 500;
int n, m;
num a[nsz + 5];

struct persistent_treap {
	int rt, sz, ss, stk[trsz];
	
	struct node {
		int ls, rs, siz, cnt;
		num sum, val, del;
		
		node() {}
		node(num w): ls(0), rs(0), siz(1), cnt(0), sum(w), val(w), del(0) {}
		
		inline node& operator += (const num w) {
			sum += w * siz, val += w, del += w;
			return *this;
		}
	};
	node t[trsz + 5];
	
	int inline make(num w) {
		int u = ss ? stk[--ss] : ++sz;
		t[u] = node(w);
		return u;
	}
	
	int inline cpy(int p) {
		int u = ss ? stk[--ss] : ++sz;
		t[u] = t[p], t[u].cnt = 0;
		inc(t[u].ls), inc(t[u].rs);
		return u;
	}
	
	void inline inc(int u) {
		if (!u) return;
		t[u].cnt += 1;
	}
	
	void inline dec(int u) {
		if (!u) return;
		if (--t[u].cnt == 0) {
			stk[ss++] = u;
			dec(t[u].ls), dec(t[u].rs);
		}
	}
	
	void inline up(int u) {
		int ls = t[u].ls, rs = t[u].rs;
		t[u].siz = t[ls].siz + t[rs].siz + 1;
		t[u].sum = t[ls].sum + t[rs].sum + t[u].val;
	}
	
	void inline down(int u) {
		if (t[u].del == 0) return;
		int ls = t[u].ls, rs = t[u].rs;
		if (ls) t[u].ls = cpy(ls), dec(ls), ls = t[u].ls, inc(ls), t[ls] += t[u].del;
		if (rs) t[u].rs = cpy(rs), dec(rs), rs = t[u].rs, inc(rs), t[rs] += t[u].del;
		t[u].del = 0;
	}
	
	int build(num *a, int l, int r) {
		if (l > r) return 0;
		int md = (l + r) >> 1, u = make(a[md]);
		t[u].ls = build(a, l, md - 1), inc(t[u].ls);
		t[u].rs = build(a, md + 1, r), inc(t[u].rs);
		up(u);
		return u;
	}
	
	void inline init(int n, num *a) {
		rt = build(a, 1, n), inc(rt);
	}
	
	int mrg(int v1, int v2) {
		if (!v1 || !v2) return v1 | v2;
		if (rand() % (t[v1].siz + t[v2].siz) < t[v1].siz) {
			int u = cpy(v1), p;
			down(u), p = t[u].rs, t[u].rs = mrg(t[u].rs, v2), inc(t[u].rs), dec(p), up(u);
			return u;
		} else {
			int u = cpy(v2), p;
			down(u), p = t[u].ls, t[u].ls = mrg(v1, t[u].ls), inc(t[u].ls), dec(p), up(u);
			return u;
		}
	}
	
	void spl(int u, int k, int &v1, int &v2) {
		if (!u) return (void) (v1 = v2 = 0);
		int cur = t[t[u].ls].siz + 1, p;
		if (cur <= k) {
			v1 = cpy(u), down(v1), p = t[v1].rs;
			spl(t[v1].rs, k - cur, t[v1].rs, v2), inc(t[v1].rs), dec(p), up(v1);
		} else {
			v2 = cpy(u), down(v2), p = t[v2].ls;
			spl(t[v2].ls, k, v1, t[v2].ls), inc(t[v2].ls), dec(p), up(v2);
		}
	}
	
	void inline upd(int l, int r, num w) {
		int u, v1, v2, v3, ps = sz;
		spl(rt, r, u, v3), inc(u), inc(v3), dec(rt);
		spl(u, l - 1, v1, v2), inc(v1), inc(v2), dec(u);
		t[v2] += w;
		u = mrg(v1, v2), inc(u), dec(v1), dec(v2);
		rt = mrg(u, v3), inc(rt), dec(u), dec(v3);
	}
	
	void inline set(int l1, int r1, int l2, int r2) {
		int u1, u2, v1, v2, v3;
		spl(rt, r2, v2, v3), inc(v2), inc(v3);
		spl(v2, l2 - 1, v1, u2), inc(v1), inc(u2), dec(v2);
		dec(v1), dec(v3);
		spl(rt, r1, u1, v3), inc(u1), inc(v3);
		spl(u1, l1 - 1, v1, v2), inc(v1), inc(v2), dec(u1);
		dec(rt), dec(v2);
		u1 = mrg(v1, u2), inc(u1), dec(v1), dec(u2);
		rt = mrg(u1, v3), inc(rt), dec(u1), dec(v3);
	}
	
	num inline qry(int l, int r) {
		int u, v1, v2, v3;
		spl(rt, r, u, v3), inc(u), inc(v3);
		spl(u, l - 1, v1, v2), inc(v1), inc(v2), dec(u);
		num res = t[v2].sum;
		dec(v1), dec(v2), dec(v3);
		return res;
	}
};
persistent_treap tr;

int main() {
	scanf("%d%d", &n, &m);
	cont (i, n) scanf("%lld", &a[i]);
	tr.init(n, a);
	cont (i, m) {
		int tp, l, r, ll, rr, w;
		scanf("%d%d%d", &tp, &l, &r);
		if (tp == 1) {
			scanf("%d", &w);
			tr.upd(l, r, w);
		} else if (tp == 2) {
			scanf("%d%d", &ll, &rr);
			tr.set(l, r, ll, rr);
		} else if (tp == 3) {
			printf("%lld\n", tr.qry(l, r));
		}
	}
}