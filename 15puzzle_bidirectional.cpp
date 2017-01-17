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
int cnt_q;

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

queue<S> find(queue<S> &q, map<vector<vi>, int> &mymap, map<vector<vi>, int> &tomap) {
	queue<S> _q;
	while(q.size()) {
		S s = q.front(); q.pop();
		REP(i, 4) {
			vector<vi> vvi = s.vvi;
			int y = s.pnt.first + dy[i];
			int x = s.pnt.second + dx[i];
			if(chk(y, x)) {
				swap(vvi[s.pnt.first][s.pnt.second], vvi[y][x]);
				if(mymap.count(vvi) || valid(vvi, s.cnt+1)) continue;
				_q.push(S{vvi, s.cnt+1, pi(y, x)});
				mymap[vvi] = s.cnt+1;
				if(tomap.count(vvi)) {
					cout << tomap[vvi] + s.cnt+1 << endl;
					return queue<S>();
				}
			}
		}
	}
	return _q;
}

int main() {

	int in;
	while(cin >> in) {
		struct timeval ss, e;
		gettimeofday(&ss, NULL);
		S s;
		vector<vi> vvi(4), vvi2(4);
		pi pnt;
		REP(i, 4) {
			vvi[i].resize(4);
			vvi2[i].resize(4);
			REP(j, 4) {
				if(i || j)
					cin >> vvi[i][j];
				else
					vvi[i][j] = in;
				if(vvi[i][j] == 0)
					pnt = pi(i, j);
				vvi2[i][j] = i*4 + j+1;
			}
		}
		vvi2[3][3] = 0;

		map<vector<vi>, int> m1, m2;
		queue<S> q1, q2;
		q1.push(S{vvi, 0, pnt});
		q2.push(S{vvi2, 0, pi(3, 3)});
		m1[vvi] = 0;
		m2[vvi2] = 0;
		if(!valid(vvi, 45)) {
			cout << 0 << endl;
			gettimeofday(&e, NULL);
			printf("time = %lf\n", (e.tv_sec - ss.tv_sec) + (e.tv_usec - ss.tv_usec)*1.0E-6);
			cout << "queue = " << cnt_q << endl;
			continue;
		}

		while(true) {
			q1 = find(q1, m1, m2);
			if(q1.empty()) break;
			cnt_q = max(cnt_q, (int)q1.size() + (int)q2.size());
			q2 = find(q2, m2, m1);
			if(q2.empty()) break;
			cnt_q = max(cnt_q, (int)q1.size() + (int)q2.size());
		}
		gettimeofday(&e, NULL);
		printf("time = %lf\n", (e.tv_sec - ss.tv_sec) + (e.tv_usec - ss.tv_usec)*1.0E-6);
		cout << "queue = " << cnt_q << endl;
	}
	return 0;
}
