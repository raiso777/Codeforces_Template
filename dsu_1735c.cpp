#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n;
	string s;
	cin >> n >> s;

	vector<char> dsu(128), nxt(128, 0);
	for(int i = 0; i < dsu.size(); i++) dsu[i] = i;

	function< char(char) > Froot = [&](char c) {
		return dsu[c] = (dsu[c] == c? c: Froot(dsu[c]));
	};

	int alpha = 0;
	for(auto &c: s) {
		if(!nxt[c]) {
			char mi = 'a';
			char c_rt = Froot(c);
			while(dsu[mi] != mi || (alpha < 25 && mi == c_rt)) mi++;
			dsu[mi] = c_rt;
			nxt[c] = mi, alpha++;
		}
		c = nxt[c];
	}
	cout << s << '\n';
}


int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
