// 2D line sweep (intersection defined as perimeters intersecting, not areas)
// https://naipc19.kattis.com/problems/intersectingrectangles
// 2019 NAIPC

#include <bits/stdc++.h>
using namespace std;

struct rectangle {
  int x1, y1, x2, y2;
};

struct event {
  int x, y1, y2;
  bool add;

  bool operator<(const event& o) const { return x < o.x; }
};

vector<event> rectangle_to_event(const rectangle& r) {
  event e1 = event{r.x1, r.y1, r.y2, true};
  event e2 = event{r.x2, r.y1, r.y2, false};
  return {e1, e2};
}

bool has_intersection_1d(const set<int>& window, int y1, int y2) {
  int zone1 = *window.lower_bound(y1);
  int zone2 = *window.lower_bound(y2);
  return zone1 != zone2;
}

int has_intersection(const vector<rectangle>& rectangles) {
  vector<event> events;
  for (const auto& rect : rectangles) {
    for (auto event : rectangle_to_event(rect)) {
      events.push_back(event);
    }
  }
  sort(events.begin(), events.end());

  set<int> borders;
  for (int i = 0; i < events.size(); i++) {
    if (events[i].add) {
      borders.insert(events[i].y1);
      borders.insert(events[i].y2);
    } else {
      int y1 = events[i].y1;
      int y2 = events[i].y2;
      borders.erase(events[i].y1);
      borders.erase(events[i].y2);
      if (has_intersection_1d(borders, y1, y2)) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;
  vector<rectangle> rectangles(n);
  for (auto& r : rectangles) {
    cin >> r.x1 >> r.y1 >> r.x2 >> r.y2;
  }
  cout << has_intersection(rectangles) << '\n';
}
