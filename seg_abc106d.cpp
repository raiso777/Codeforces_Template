#include <bits/stdc++.h>
#define ff first
#define ss second
using namespace std;

using range_t = pair<int, int>;
using query_t = pair<range_t, int>;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, m, q;
	cin >> n >> m >> q, n++;

	vector< range_t > trains(m);
	for(auto &it: trains) cin >> it.ff >> it.ss;
	sort(trains.begin(), trains.end());

	vector< query_t > querys(q);
	for(int i = 0; i < q; i++) {
		auto &it = querys[i];
		cin >> it.ff.ff >> it.ff.ss, it.ss = i;
	}
	sort(querys.begin(), querys.end());
	
	vector<int> st(2 * n - 1);
	function< void(int, int, int, int, int) > Update = 
		[&](int x, int l, int r, int qi, int qv) {
			if(l == r) {
				st[x] += qv;
				return;
			}
			int y = (l + r) >> 1;
			int z = x + ((y - l + 1) << 1);
			if(qi <= y) Update(x + 1, l, y, qi, qv);
			else Update(z, y + 1, r, qi, qv);
			st[x] = st[x + 1] + st[z];
		};
	function< int(int, int, int, int, int) > Query =
		[&](int x, int l, int r, int ql, int qr) {
			if(ql <= l && r <= qr) return st[x];
			int y = (l + r) >> 1;
			int z = x + ((y - l + 1) << 1);
			int ans = 0;
			if(ql <= y) ans += Query(x + 1, l, y, ql, qr);
			if(y < qr) ans += Query(z, y + 1, r, ql, qr);
			return ans;
		};

	for(auto it: trains) Update(0, 0, n - 1, it.ss, 1);
	
	vector<int> ans(q);
	auto train = trains.begin();
	auto query = querys.begin();
	for(int i = 1; i < n; i++) {
		for(; train != trains.end() && train -> ff < i; train++)
			Update(0, 0, n - 1, train -> ss, -1);

		for(; query != querys.end() && query -> ff.ff == i; query++)
			ans[query -> ss] = Query(0, 0, n - 1, 0, query -> ff.ss);
	}

	for(auto it: ans) cout << it << '\n';
	return 0;
}
