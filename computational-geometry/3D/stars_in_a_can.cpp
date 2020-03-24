// 3D convex hull, 3D projections, min enc circle
// https://open.kattis.com/problems/starsinacan
// 2017 NAIPC

#include <bits/stdc++.h>
using namespace std;

using ld = long double;
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)

const ld INF = 1e17;
constexpr auto EPS = 1e-9;
constexpr auto PI = acos(-1);

using ptT = ld;
struct P3 {
    typedef P3 P;
    ptT x, y, z;
    auto operator<(const P3& p) const {
        return tie(x, y, z) < tie(p.x, p.y, p.z); }
    auto operator==(const P3& p) const {
        return tie(x, y, z) == tie(p.x, p.y, p.z); }
    P3 operator+(const P3& p) const { return {x+p.x, y+p.y, z+p.z}; }
    P3 operator-(const P3& p) const { return {x-p.x, y-p.y, z-p.z}; }
    P3 operator-(ptT d) const {return {x - d, y - d, z - d};}
    P3 operator*(ptT d) const { return {x*d, y*d, z*d}; }
    P3 operator/(ptT d) const { return {x/d, y/d, z/d}; }
    auto dot(const P3& p) const { return x*p.x + y*p.y + z*p.z; }
    auto cross(const P3& p) const {
        return P3{y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x};
    }
    auto dist2() const { return x*x + y*y + z*z; }
    auto dist() const { return sqrt((ld)dist2()); }
    auto unit() const { return *this/dist(); }
    auto rotate(ld angle, P axis) const { // ccw around axis
        ld s = sin(angle), c = cos(angle); P u = axis.unit();
        return u*dot(u)*(1-c) + (*this)*c - cross(u)*s;
    }
    auto perp(P axis) const {return rotate(PI / 2, axis);}
};

struct PR {
    void ins(int x) { (a == -1 ? a : b) = x; }
    void rem(int x) { (a == x ? a : b) = -1; }
    int cnt() { return (a != -1) + (b != -1); }
    int a, b;
};

struct F { P3 q; int a, b, c; };

vector<F> hull3d(const vector<P3>& A) {
    assert(sz(A) >= 4);
    vector<vector<PR>> E(sz(A), vector<PR>(sz(A), {-1, -1}));
#define E(x,y) E[f.x][f.y]
    vector<F> FS;
    auto mf = [&](int i, int j, int k, int l) {
                  P3 q = (A[j] - A[i]).cross((A[k] - A[i]));
                  if (q.dot(A[l]) > q.dot(A[i]))
                      q = q * -1;
                  F f{q, i, j, k};
                  E(a,b).ins(k); E(a,c).ins(j); E(b,c).ins(i);
                  FS.push_back(f);
              };
    rep(i,0,4) rep(j,i+1,4) rep(k,j+1,4)
        mf(i, j, k, 6 - i - j - k);

    rep(i,4,sz(A)) {
        rep(j,0,sz(FS)) {
            F f = FS[j];
            if(f.q.dot(A[i]) > f.q.dot(A[f.a])) {
                E(a,b).rem(f.c);
                E(a,c).rem(f.b);
                E(b,c).rem(f.a);
                swap(FS[j--], FS.back());
                FS.pop_back();
            }
        }
        int nw = sz(FS);
        rep(j,0,nw) {
            F f = FS[j];
#define C(a, b, c) if (E(a,b).cnt() != 2) mf(f.a, f.b, i, f.c);
            C(a, b, c); C(a, c, b); C(b, c, a);
        }
    }
    trav(it, FS) if ((A[it.b] - A[it.a]).cross(
                         A[it.c] - A[it.a]).dot(it.q) <= 0) swap(it.c, it.b);
    return FS;
};

struct plane {
    P3 n; ptT d;
    plane(P3 n, P3 p) : n(n), d(n.dot(p)) {}
    ptT side(P3 p) {return (n.dot(p)) - d;}
    ld dist(P3 p) {return abs(side(p)) / n.dist();}
    P3 proj(P3 p){return p - n*side(p)/(n.dot(n));}
};

struct coords {
    P3 o, dx, dy, dz;
    coords(P3 p, P3 q, P3 r) : o(p) { // build orthonormal basis
        dx = (q - p).unit();
        dz = (dx.cross(r-p)).unit();
        dy = dz.cross(dx);
    }
    P3 pos2d(P3 p) {return {(p-o).dot(dx), (p-o).dot(dy), 0};}
};

ld ccRadius(const P3& A, const P3& B, const P3& C) {
    return (B-A).dist()*(C-B).dist()*(A-C).dist()/
        abs((B-A).cross(C-A).z)/2;
}
P3 ccCenter(const P3& A, const P3& B, const P3& C) {
    auto b = C-A, c = B-A;
    return A + (b*c.dist2()-c*b.dist2()).perp({0, 0, 1})/b.cross(c).z/2;
}

pair<P3, ld> mec(vector<P3> ps) {
    shuffle(all(ps), mt19937(time(0)));
    auto o = ps[0];
    ld r = 0, EPS = 1 + 1e-8;
    rep(i,0,sz(ps)) if ((o - ps[i]).dist() > r * EPS) {
        o = ps[i], r = 0;
        rep(j,0,i) if ((o - ps[j]).dist() > r * EPS) {
            o = (ps[i] + ps[j]) / 2;
            r = (o - ps[i]).dist();
            rep(k,0,j) if ((o - ps[k]).dist() > r * EPS) {
                o = ccCenter(ps[i], ps[j], ps[k]);
                r = (o - ps[i]).dist();
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
    vector<P3> a(n);
    trav(p, a)
        cin >> p.x >> p.y >> p.z;
    auto hull = hull3d(a);
    auto sol = INF;
    rep(it, 0, sz(hull)) {
        plane face(hull[it].q, a[hull[it].a]);
        coords basis(a[hull[it].a], a[hull[it].b], a[hull[it].c]);
        
        auto height = -INF;
        vector<P3> projected(n);
        rep(j, 0, n) {
            projected[j] = basis.pos2d(a[j]);
            height = max(height, face.dist(a[j]));
        }
        auto [center, radius] = mec(projected);
        sol = min(sol, PI * radius * radius * height);
    }
    cout << fixed << setprecision(11) << sol << '\n';
}
