template<int mod> struct modulo {
	typedef modulo T;
	int w;
	operator int() const { return w; }
	
	modulo() {}
	modulo(int w) { this->w = w; fix(); }
	template<class type> modulo(type w) { this->w = w % mod; fix(); }
	void inline fix() { if (w >= mod || w < -mod) w %= mod; if (w < 0) w += mod; }
	
	inline T  operator -  () const { return mod - w; }
	inline T& operator += (const T &b) { if ((w += b.w) >= mod) w -= mod; return *this; }
	inline T& operator -= (const T &b) { if ((w -= b.w) < 0) w += mod; return *this; }
	inline T& operator *= (const T &b) { w = (unsigned long long) w * b.w % mod; return *this; }
	inline T& operator /= (const T &b) { return *this *= inv(b); }
	#define make_operation(op) \
	friend inline T operator op (const T &a, const T &b) { return T(a) op##= b; }\
	template<class U> friend inline T operator op (const T &a, const U &b) { return T(a) op##= b; }\
	template<class U> friend inline T operator op (const U &a, const T &b) { return T(a) op##= b; }
	make_operation(+) make_operation(-) make_operation(*) make_operation(/)
	#undef make_operation
	
	T inline inv() {
		int a = w, m = mod, u = 0, v = 1, t;
		for (; a != 0; t = m / a, m -= t * a, swap(a, m), u -= t * v, swap(u, v));
		return u;
	}
	
	friend inline T pow(const T &w, int p) {
		T a = w, r = 1;
		for (; p > 0; a *= a, p >>= 1) if (p & 1) r *= a;
		return r;
	}
};
const int mod = /* number */;
typedef modulo<mod> rem;