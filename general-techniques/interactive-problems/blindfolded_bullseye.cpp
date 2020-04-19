// interactive, binary search, finding center of circle given 4 symmetric points on perimeter
// https://codingcompetitions.withgoogle.com/codejam/round/000000000019fef2/00000000002d5b63
// 2020 GCJ 1B

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)

const int MAXX = 1000000000;
vi pokes = {-MAXX / 2, 0, MAXX / 2};

const string HIT = "HIT";
const string MISS = "MISS";
const string WRONG = "WRONG";
const string CENTER = "CENTER";

string ask(int x, int y) {
  cout << x << " " << y << endl;
  string res;
  cin >> res;
  if (res == WRONG) exit(0);
  else if (res == CENTER) throw -1;
  return res;
}

template <typename T, typename UnaryPredicate>
T ipartition_point(T first, T last, UnaryPredicate pred) {
  while (first < last) {
    auto mid = first + (last - first) / 2;
    if (pred(mid)) first = mid + 1;
    else last = mid;
  }
  return first;
}

void solve_test_case() {
  int sx, sy;
  bool done = false;
  trav(x, pokes) trav(y, pokes)
    if (ask(x, y) == "HIT")
      tie(sx, sy) = tie(x, y);
  auto min_x = ipartition_point(-MAXX, sx, [&](auto x){return ask(x, sy) == MISS;});
  auto max_x = ipartition_point(sx, MAXX, [&](auto x) {return ask(x, sy) == HIT;}) - 1;
  auto min_y = ipartition_point(-MAXX, sy, [&](auto y){return ask(sx, y) == MISS;});
  auto max_y = ipartition_point(sy, MAXX, [&](auto y){return ask(sx, y) == HIT;}) - 1;
  auto center_x = min_x + (max_x - min_x) / 2;
  auto center_y = min_y + (max_y - min_y) / 2;
  assert(ask(center_x, center_y) == "CENTER");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int num_tests, A, B;
  cin >> num_tests >> A >> B;
  for (int test_num = 1; test_num <= num_tests; test_num++) {
    try {solve_test_case();}
    catch(int e) {assert(e == -1);}
  }
}
