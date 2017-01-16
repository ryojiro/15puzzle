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
typedef vector<vi> vvi;
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
	vvi vv;
	int cnt;
	pi pnt;
};

//枝刈り
bool valid(vvi &vv, int cnt) {
	int res = 0;
	REP(i, 4) REP(j, 4) {
		if(vv[i][j] == 0) continue;
		res += abs(goal[vv[i][j]].first - i);
		res += abs(goal[vv[i][j]].second - j);
	}
	return (res + cnt > 45) ? true : false;
}

int getComp(vvi &vv) {
	int res = 0;
	REP(i, 4) REP(j, 4) {
		if(vv[i][j] == 0) continue;
		res += abs(goal[vv[i][j]].first - i);
		res += abs(goal[vv[i][j]].second - j);
	}
	return res;
}

bool chk(int x, int y) {
	if(x < 0 || y < 0 || 4 <= x || 4 <= y)
		return false;
	return true;
}

int bfs(int limit, queue<S> &q) {
	while(!q.empty()) {
		S s = q.front(); q.pop();
		REP(i, 4) {
			vvi vv = s.vv;
			int y = s.pnt.first + dy[i];
			int x = s.pnt.second + dx[i];
			if(chk(y, x)) {
				swap(vv[s.pnt.first][s.pnt.second], vv[y][x]);
				int com = getComp(vv);
				if(com + s.cnt+1 > limit) continue;
				if(com + s.cnt+1 > 45) continue;
				if(!com) {
					return s.cnt+1;
				}
				q.push(S{vv, s.cnt+1, pi(y, x)});
			}
		}
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int in;
	while(cin >> in) {
		chrono::system_clock::time_point  start, end;
		start = chrono::system_clock::now();
		vvi vv(4);
		pi pnt;
		REP(i, 4) {
			vv[i].resize(4);
			REP(j, 4) {
				if(i || j)
					cin >> vv[i][j];
				else
					vv[i][j] = in;
				if(vv[i][j] == 0)
					pnt = pi(i, j);
			}
		}
	/*
	REP(i, 4) {
		REP(j, 4)
			cout << vv[i][j] << ' ';
		cout << endl;
	}
	*/
		if(!getComp(vv)) {
			cout << 0 << endl;
			continue;
		}

		queue<S> q;
		REP(i, 45) {
			q.push(S{vv, 0, pnt});
			int ans = bfs(i, q);
			if(ans != -1) {
				cout << ans << endl;
				break;
			}
		}
		end = chrono::system_clock::now();
		double elapsed = chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
		cout << elapsed << " ms" << endl;
	}
	return 0;
}
