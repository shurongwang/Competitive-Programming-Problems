#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int lgsz = 30;
const int zero = 1000, one = 1001, two = 1002;
int p2[60 + 5];
vector<string> operations;

string inline int_to_str(int a) {
	if (a == 0) return "0";
	string s;
	for (; a; s += a % 10 + 48, a /= 10);
	reverse(all(s));
	return s;
}

void inline add_to(int i, int j, int to) {
	operations.push_back("+ " + int_to_str(i) + " " + int_to_str(j) + " " + int_to_str(to));
}

void inline cmp_to(int i, int j, int to) {
	operations.push_back("< " + int_to_str(i) + " " + int_to_str(j) + " " + int_to_str(to));
}

void inline set_0(int i) {
	cmp_to(zero, zero, i);
}

void inline set_1(int i) {
	cmp_to(zero, one, i);
}

void inline mul_by_power_of_2(int i, int e) {
	cont (k, e) add_to(i, i, i);
}

void inline mul_power_of_2_to(int i, int e, int k) {
	const int j = 100;
	set_0(j);
	add_to(i, zero, j);
	cont (i, e) add_to(j, j, j);
	add_to(j, zero, k);
}

void inline or_to(int i, int j, int to) {
	const int or_p = 2000;
	cmp_to(zero, i, or_p);
	cmp_to(zero, j, to);
	add_to(to, or_p, to);
	cmp_to(zero, to, to);
}

void inline and_to(int i, int j, int to) {
	const int and_p = 2001;
	cmp_to(zero, i, and_p);
	cmp_to(zero, j, to);
	add_to(to, and_p, to);
	cmp_to(one, to, to);
}

void inline factorize_to_binary(int i, int fm, int len = lgsz) {
	const int sum = 3000, j = 3001, cur = 3002, cur_sum = 3003, cur_del = 3004;
	set_0(sum);
	add_to(i, one, j);
	for (int k = len; k >= 0; --k) {
		add_to(sum, p2[k], cur_sum);
		cmp_to(cur_sum, j, fm + k);
		mul_power_of_2_to(fm + k, k, cur_del);
		add_to(sum, cur_del, sum);
	}
}

void inline mul_bool_to(int i, int j, int to, int len = lgsz) {
	const int fm = 4000;
	factorize_to_binary(i, fm, len);
	circ (k, 0, len) {
		and_to(fm + k, j, fm + k);
	}
	set_0(to);
	circ (k, 0, len) {
		mul_by_power_of_2(fm + k, k);
		add_to(to, fm + k, to);
	}
}

void inline mul(int i, int j, int to) {
	const int fm = 200, a = 300, del = 301;
	factorize_to_binary(j, fm);
	set_0(to);
	set_0(a);
	add_to(a, i, a);
	circ (k, 0, lgsz) {
		mul_bool_to(a, fm + k, del, 60);
		add_to(to, del, to);
		add_to(a, a, a);
	}
}

void inline init() {
	p2[0] = one;
	add_to(0, 1, 5);
	cmp_to(zero, 5, one);
	cont (i, 60) {
		p2[i] = one + i;
		add_to(p2[i - 1], p2[i - 1], p2[i]);
	}
}

int main() {
	init();
	mul(0, 1, 2);
	cout << operations.size() << ln;
	for (string cmd : operations) {
		cout << cmd << ln;
	}
}