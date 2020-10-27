#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

template<int mod> struct modulo {
    int w;
    operator int&() { return w; }
    operator int() const { return w; }
    
    modulo() {}
    modulo(int w, bool f = 0) { this->w = w; if (f) fix(); }
    void inline fix() { if (w >= mod || w < -mod) w %= mod; if (w < 0) w += mod; }
    
    inline modulo  operator -  () { w = -w + mod; return *this; }
    inline modulo  operator +  (const modulo &b) { modulo r = *this; return r += b; }
    inline modulo  operator -  (const modulo &b) { modulo r = *this; return r -= b; }
    inline modulo  operator *  (const modulo &b) { modulo r = *this; return r *= b; }
    inline modulo  operator /  (const modulo &b) { modulo r = *this; return r /= b; }
    inline modulo& operator += (const modulo &b) { if ((w += b.w) >= mod) w -= mod; return *this; }
    inline modulo& operator -= (const modulo &b) { if ((w -= b.w) < 0) w += mod; return *this; }
    inline modulo& operator *= (const modulo &b) { w = (num) w * b.w % mod; return *this; }
    inline modulo& operator /= (const modulo &b) { return *this *= inv(b); }
    
    friend inline modulo inv(const modulo &w) {
        int a = w, m = mod, u = 0, v = 1, t;
        for (; a != 0; t = m / a, m -= t * a, swap(a, m), u -= t * v, swap(u, v));
        return modulo(u, 1);
    }
    
    friend inline modulo pow(const modulo &w, int p) {
        if (!w)  return 0;
        modulo a = w, r = 1;
        for (; p > 0; a *= a, p >>= 1) if (p & 1) r *= a;
        return r;
    }
};
const int mod = int(1e9) + 7;
typedef modulo<mod> rem;

template<class type> struct matrix {
    int n, m;
    vector< vector<type> > d;
    
    matrix() { n = m = 0; }
    matrix(int n, int m, int k = 0) {
        this->n = n, this->m = m;
        d.resize(n, vector<type>(m, 0));
        if (n == m && k) loop (i, n) d[i][i] = k;
    }
    
    const vector<type>& operator [] (int id) const { return d[id]; }
    vector<type>& operator [] (int id) { return d[id]; }
    
    friend inline matrix operator * (const matrix &a, const matrix &b) {
        matrix r(a.n, b.m);
        loop (i, a.n) loop (k, a.m) if (a[i][k]) loop (j, b.m) if (b[k][j]) r[i][j] += rem(a[i][k]) * b[k][j];
        return r;
    }
    friend inline matrix operator *= (matrix &a, const matrix &b) { return a = a * b; }
    
    friend inline ostream& operator << (ostream &out, const matrix &a) {
        loop (i, a.n) loop (j, a.m) out << a[i][j] << ("\n,"[j + 1 < a.m]);
        return out;
    }
    
    friend inline matrix pow(const matrix &w, int p) {
        matrix a = w, r(w.n, w.m, 1);
        for (; p > 0; a *= a, p >>= 1) if (p & 1) r *= a;
        return r;
    }
};
typedef matrix<rem> mat;

const int nsz = 7, ssz = 50, msksz = (1 << (nsz - 1)) - 1;
char s[ssz + 5];
int n, t, sz, full;
mat a;

mat inline calc(mat f[2]) {
    mat r(f[0].n, f[0].m, 1), b[4] = {f[0] * f[0], f[0] * f[1], f[1] * f[0], f[1] * f[1]};
    for (int i = 0; i + 1 < sz; i += 2) {
        int c0 = s[i] - 48, c1 = s[i + 1] - 48;
        r *= b[c0 << 1 | c1];
    }
    if (sz & 1) r *= f[s[sz - 1] - 48];
    return r;
}

void inline solve() {
    mat f[2];
    f[0] = f[1] = mat(full + 1, full + 1);
    a = mat(full + 1, full + 1, 1);
    loop (c, 2) circ (fm, 0, full) {
        circ (tS, 0, full) if (__builtin_popcount(tS) % 2 == 0) {
            bool flag = 1;
            int to = 0, S = tS | (c << n);
            loop (i, n) {
                int c0 = S >> i & 1, c1 = S >> (i + 1) & 1;
                if (!(fm >> i & 1) && c0 > c1) { flag = 0; break; }
                to |= ((fm >> i & 1) | (c0 < c1)) << i;
            }
            if (flag) f[c][fm][to] += rem(1);
        }
    }
    a = pow(calc(f), t);
    printf("%d\n", a[0][full]);
}

int main() {
    scanf("%d%d", &n, &t);
    scanf("%s", s);
    sz = strlen(s), full = (1 << n) - 1;
    solve();
}