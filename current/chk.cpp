
#include <bits/stdc++.h>

#define ln                '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const bool spj = 0;
const int ts = 1e2;
const string cpp_compile_cmd = "g++ *.cpp -o * -std=c++2a -O2";

bool inline judge() {
	system("./gen");
	if (spj) {
		system("./spj");
		string status;
		ifstream in("log.out");
		in >> status;
		return status == "Accepted";
	} else {
		system("./main < dat.in > dat.out");
		system("./std < dat.in > std.out");
		return !system("diff dat.out std.out > log.out");
	}
}

void inline cpp_compile(const string &file_name, const string &cpp_compile_cmd = ::cpp_compile_cmd) {
	string cmd = cpp_compile_cmd;
	vector<string> s;
	int lst = 0;
	loop (i, cmd.size()) {
		if (i == cmd.size() - 1 || cmd[i] == '*') {
			s.push_back(cmd.substr(lst, i - lst + (cmd[i] != '*')));
			lst = i + 1;
		}
	}
	cmd = s[0];
	cont (i, s.size() - 1)  cmd += file_name + s[i];
	system(cmd.c_str());
}

int main() {
	ios::sync_with_stdio(0);
	system("ulimit -s 65522");
	cpp_compile("gen"), cpp_compile("main"), cpp_compile("std");
	if (spj) cpp_compile("spj");
	cerr << "Compiled" << ln;
	cont (cs, ts) {
		if (!judge()) {
			cerr << "Wrong Answer." << ln;
			return 0;
		}
		cerr.fill('0');
		cerr << "#" << setw(3) << cs << ": Accepted" << ln;
	}
	return 0;
}
