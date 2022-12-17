//https://www.luogu.com.cn/problem/P4137
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
using namespace std;

struct SGT {
	int n;
	vector<int> v;
	SGT(int _n) {
		n = 1;
		while(n < _n) n <<= 1;
		v.assign(2 * n, INT_MAX);
	}

	void Update(int qi, int qv) {
		qi += n, v[qi] = qv;
		for(int i = qi; i; i >>= 1) v[i >> 1] = max(v[i], v[i ^ 1]);
	}

	int Query(int qv) {
		int res = 1;
		while(res < n) res = (v[res << 1] > qv? res << 1: res << 1 | 1);
		return res - n;
	}
};


int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, m;
	cin >> n >> m;

	int maxa = 0;
	vector<int> a(n);
	for(auto &it: a) cin >> it, maxa = max(maxa, it);

	vector< vector< pair<int, int> > > q(n);
	for(int i = 0; i < m; i++) {
		int l, r;
		cin >> l >> r, l--, r--;
		q[l].pb(mp(r, i));
	}

	vector<int> ans(m);
	SGT sgt(maxa + 1);
	for(int i = n - 1; i >= 0; i--) {
		sgt.Update(a[i], i);
		for(auto [qi, idx]: q[i]) {
			int tmp = sgt.Query(qi);
			ans[idx] = tmp;
		}
	}
	for(auto it: ans) cout << it << '\n';
	return 0;
}
