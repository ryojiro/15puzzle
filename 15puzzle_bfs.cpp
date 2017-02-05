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
	int cnt, com;
	pi pnt;
};

int getComp(vector<vi> &vvi) {
	int res = 0;
	REP(i, 4) REP(j, 4) {
		if(vvi[i][j] == 0) continue;
		res += abs(goal[vvi[i][j]].first - i);
		res += abs(goal[vvi[i][j]].second - j);
	}
	return res;
}

bool chk(int x, int y) {
	if(x < 0 || y < 0 || 4 <= x || 4 <= y)
		return false;
	return true;
}

int main() {

	int in;
	int cnt_q = 0;
	while(cin >> in) {
		struct timeval ss, e;
		gettimeofday(&ss, NULL);
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

		set<vector<vi>> memo;
		queue<S> pq;
		pq.push(S{vvi, 0, getComp(vvi), pnt});
		memo.insert(vvi);

		while(!pq.empty()) {
			cnt_q = max(cnt_q, (int)pq.size());
			S s = pq.front(); pq.pop();

			if(s.com == s.cnt) {
				cout << s.cnt << endl;
				break;
			}
			REP(i, 4) {
				vvi = s.vvi;
				int y = s.pnt.first + dy[i];
				int x = s.pnt.second + dx[i];
				if(chk(y, x)) {
					swap(vvi[s.pnt.first][s.pnt.second], vvi[y][x]);
					if(!memo.count(vvi)) {
						memo.insert(vvi);
						int com = getComp(vvi)+s.cnt+1;
						//if(com > 45) continue;
						pq.push(S{vvi, s.cnt+1, com, pi(y, x)});
					}
				}
			}
		}
		gettimeofday(&e, NULL);
  	printf("time = %lf\n", (e.tv_sec - ss.tv_sec) + (e.tv_usec - ss.tv_usec)*1.0E-6);
		cout << "queue = " << cnt_q << endl;
	}
	return 0;
}
