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
#include <sys/time.h>
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
	pi pnt;
};

int valid(vvi &vv, int cnt) {
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


set<vvi> memo;

void dfs(int cnt, int limit, S s, bool &hit, int &times) {
	times++;
	int value = valid(s.vv, cnt);
	if(!value) hit = true;
	if(value + cnt > 45) return;
	if(memo.count(s.vv)) return;
	memo.insert(s.vv);
	if(cnt >= limit) return;

	REP(i, 4) {
		vvi vv = s.vv;
		int y = s.pnt.first + dy[i];
		int x = s.pnt.second + dx[i];
		if(chk(y, x)) {
			swap(vv[s.pnt.first][s.pnt.second], vv[y][x]);
			dfs(cnt+1, limit, S{vv, pi(y, x)}, hit, times);
		}
	}
	return;
}

int main() {

	int in;
	while(cin >> in) {
		struct timeval s, e;
		gettimeofday(&s, NULL);

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
			REP(j, 4) {
				cout << vv[i][j] << ' ';
			}
			cout << endl;
		}
		cout << "pnt: " << pnt.first << ' ' << pnt.second << endl;
		*/


		REP(i, 46) {
			int times = 0;
			bool hit = false;
			memo.clear();
			dfs(0, i, S{vv, pnt}, hit, times);
			//cout << "i: " << i << " times: " << times << endl;
			//if(hit) {
				cout << i << endl;
				gettimeofday(&e, NULL);
			  printf("time = %lf\n", (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6);
				//break;
			//}
		}
	}
	return 0;
}
