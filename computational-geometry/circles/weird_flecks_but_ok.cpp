// minimum enclosing circle, geometry (basic projection)
// https://mausa19.kattis.com/problems/weirdflecksbutok
// 2019 Mid-Atlantic Regional

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)

const long double EPS = 1e-9;
using ld = long double;

typedef long double ptT;
struct pt
{
    ptT x, y;

    pt operator + (const pt &o) const {return {x + o.x, y + o.y};}
    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}
    pt operator * (ptT k) const {return {k * x, k * y};}
    pt operator / (ptT k) const {return {x / k, y / k};}
    ptT operator ^ (const pt &o) const {return x * o.y - y * o.x;}

    pt perpCcw() const {return {-y, x};}
    ptT norm2() const {return x * x + y * y;}
    long double dist(const pt& o) const {return sqrt((*this - o).norm2());}
};

double ccRadius(const pt& A, const pt& B, const pt& C) {
	return B.dist(A)*C.dist(B)*A.dist(C) / abs((B-A)^(C-A))/2;
}

pt ccCenter(const pt& A, const pt& B, const pt& C) {
	pt b = C-A, c = B-A;
	return A + (b*c.norm2()-c*b.norm2()).perpCcw()/(b ^ c)/2;
}

pair<pt, ld> mec(vector<pt> ps) {
	shuffle(all(ps), mt19937(time(0)));
	pt o = ps[0];
	ld r = 0, ERR = 1 + EPS; // Note: kactl uses EPS = 1e-6
	rep(i,0,sz(ps)) if (o.dist(ps[i]) > r * ERR) {
		o = ps[i], r = 0;
		rep(j,0,i) if (o.dist(ps[j]) > r * ERR) {
			o = (ps[i] + ps[j]) / 2;
			r = o.dist(ps[i]);
			rep(k,0,j) if (o.dist(ps[k]) > r * ERR) {
				o = ccCenter(ps[i], ps[j], ps[k]);
				r = o.dist(ps[i]);
			}
		}
	}
	return {o, r};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    auto pts = vector(n, vector<ld>(3));
    trav(p, pts) {
        trav(coord, p) {
            cin >> coord;
        }
    }

    const ld INF = 1e9;
    auto sol = INF;
    rep(c1, 0, 3) {
        auto c2 = (c1 + 1) % 3;
        vector<pt> proj(n);
        rep(i, 0, sz(pts)) {
            proj[i] = {pts[i][c1], pts[i][c2]};
        }
        auto [c, r] = mec(proj);
        sol = min(sol, 2 * r);
    }
    cout << fixed << setprecision(12) << sol << '\n';
}
