
#include <bits/stdc++.h>

#define ln                '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

namespace io {
	#define isdigit(c)  (c >= '0' && c <= '9')
	#define isalpha(c)  (c >= 'a' && c <= 'z')
	#define isAlpha(c)  (c >= 'A' && c <= 'Z')
	#define isalnum(c)  (isalpha(c) || isAlpha(c) || isdigit(c))
	#define getchar()   (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufsz, stdin), p1 == p2) ? EOF : *p1++)
	#define flush()     (fwrite(puf, 1, pp - puf, stdout), pp = puf)
	#define putchar(c)  (*pp++ = c, pp - puf == bufsz && flush())
	
	const int bufsz = 1 << 24;
	static char buf[bufsz], puf[bufsz], *p1, *p2, *pp = puf;
	struct flusher { ~flusher() { flush(); } } flusher;
	
	template<class type> void inline read(type &a) {
		int f = 1, c = getchar();
		for (; !isdigit(c); c == 45 && (f = -1), c = getchar());
		for (a = 0; isdigit(c); a *= 10, a += c & 15, c = getchar());
		a *= f;
	}
	
	void inline read_str(string &s) {
		char c = getchar();
		for (; !isalnum(c); c = getchar());
		for (s = ""; isalnum(c); s += c, c = getchar());
	}
	
	template<class type> void inline write(type a, char c = ln) {
		static int d[20];
		int s = d[0] = 0;
		for (a < 0 && (putchar(45), a = -a); a; d[s++] = a % 10, a /= 10);
		for (s || (s = 1); s; putchar(d[--s] + 48));
		putchar(c);
	}
	
	void inline write_str(string s, char c = ln) {
		loop (i, s.size()) {
			putchar(s[i]);
		}
		putchar(c);
	}
}
using namespace io;

int seed;
random_device rd;
mt19937 rdm(rd());

void inline init() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	freopen("dat.in", "w", stdout);
}

num inline random(num l, num r) {
	return (num) rdm() * rand() % (r - l + 1) + l;
}

int main() {
	
}