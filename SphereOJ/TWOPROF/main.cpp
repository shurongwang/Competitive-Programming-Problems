#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

namespace io {
	#define isdigit(c)  (c >= '0' && c <= '9')
	#define getchar()   (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufsz, stdin), p1 == p2) ? EOF : *p1++)
	#define flush()     (fwrite(puf, 1, pp - puf, stdout), pp = puf)
	#define putchar(c)  (*pp++ = c, pp - puf == bufsz && flush())
	
	const int bufsz = 1 << 24;
	static char buf[bufsz], puf[bufsz], *p1, *p2, *pp = puf;
	struct flusher { ~flusher() { flush(); } } flusher;
	
	template<class type> void inline read(type &a) {
		char c = getchar();
		for (; !isdigit(c); c = getchar());
		for (a = 0; isdigit(c); a *= 10, a += c & 15, c = getchar());
	}
	
	template<class type> void inline write(type a, char c = ln) {
		static int d[20];
		int s = d[0] = 0;
		for (; a; d[s++] = a % 10, a /= 10);
		for (s || (s = 1); s; putchar(d[--s] + 48));
		putchar(c);
	}
}
using namespace io;

const int nsz = 1e5;
bool can[nsz + 5];
int ts, n, m;
pair<int, int> d[nsz + 5];

struct event {
	bool tp;
	int t, id;
	
	event() {}
	event(int t, int id, bool tp) { this->t = t, this->id = id, this->tp = tp; }
	
	bool inline operator < (const event &e) const { return t != e.t ? t < e.t : tp > e.tp; }
};
event ev[2 * nsz + 5];

void inline solve() {
	read(n);
	cont (i, n) {
		int l, r;
		read(l), read(r);
		d[i] = make_pair(l, r);
	}
	if (d[1].first > d[2].first) swap(d[1], d[2]);
	cont (i, n) {
		int l = d[i].first, r = d[i].second;
		ev[m++] = event(l, i, 0);
		ev[m++] = event(r, i, 1);
	}
	sort(ev, ev + m);
	int need = 0, sum = 0;
	loop (i, m) {
		need += ev[i].tp ? -1 : +1;
		sum = max(sum, need);
	}
	bool available = 1;
	loop (i, m) {
		int id = ev[i].id;
		if (ev[i].tp) {
			--need, available |= can[id];
		} else {
			can[id] = id == 1 ? 0 : available;
			available = !(++need == sum);
		}
	}
	write(sum + !can[2]);
}

void inline clear() {
	m = 0;
	cont (i, n) can[i] = 0;
}

int main() {
	read(ts);
	cont (cs, ts) {
		solve();
		clear();
	}
}