#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
using namespace std;
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); i++)
#define pb push_back
#define mp make_pair
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef long long ll;
typedef unsigned long long ull;
const int INF = 1<<28;
const ll MOD = 1000000007;
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
const pi goal[] = {
	pi(3,3), pi(0,0), pi(0,1), pi(0,2),
	pi(0,3), pi(1,0), pi(1,1), pi(1,2),
	pi(1,3), pi(2,0), pi(2,1), pi(2,2),
	pi(2,3), pi(3,0), pi(3,1), pi(3,2)
};

struct S {
	vector<vi> vvi;
	int cnt;
	pi pnt;
};

//枝刈り
bool valid(vector<vi> &vvi, int cnt) {
	int res = 0;
	REP(i, 4) REP(j, 4) {
		if(vvi[i][j] == 0) continue;
		res += abs(goal[vvi[i][j]].first - i);
		res += abs(goal[vvi[i][j]].second - j);
	}
	return (res + cnt > 45) ? true : false;
}

bool chk(int x, int y) {
	if(x < 0 || y < 0 || 4 <= x || 4 <= y)
		return false;
	return true;
}

bool dfs(int cnt, int limit, S &s, set<vector<vi> > &memo) {
	REP(i, 4) {
		vector<vi> vvi = s.vvi;
		int y = s.pnt.first + dy[i];
		int x = s.pnt.second + dx[i];
		bool res = false;
		if(chk(y, x)) {
			swap(vvi[s.pnt.first][s.pnt.second], vvi[y][x]);
			if(memo.count(vvi)) continue;
			memo.insert(vvi);
			if(valid(vvi, s.cnt+1))
				return true;
			if(cnt < limit)
				res = dfs(cnt+1, S{vvi, s.cnt+1, pi(y, x)}, memo)
		}
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int in;
	while(cin >> in) {
		S s;
		vector<vi> vvi(4);
		pi pnt;
		REP(i, 4) {
			vvi[i].resize(4);
			REP(j, 4) {
				if(i || j)
					cin >> vvi[i][j];
				else
					vvi[i][j] = in;
				if(vvi[i][j] == 0)
					pnt = pi(i, j);
			}
		}

		set<vector<vi> > memo;

		REP(i, 45) {
			if(dfs(i, 45, s, memo)) {
				cout << i << endl;
				break;
			}
		}
	}
	return 0;
}
