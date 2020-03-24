// 3d vector geometry (rotation around plane touching origin), ternary search
// https://codingcompetitions.withgoogle.com/codejam/round/00000000000000cb/00000000000079cc
// 2018 GCJ Qualification

#include <bits/stdc++.h>
using namespace std;

using ld = long double;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)a.size()
#define PB push_back

constexpr auto PI = acos(-1);
constexpr auto MAX_AREA_WITH_ONE_ROTATION = 1.414213;

vector<int> signs{-1, 1};
constexpr auto EPS = 1e-9L;

template <typename T> struct Point3D {
    typedef Point3D P;
    typedef const P& R;
    T x, y, z;
    explicit Point3D(T x=0, T y=0, T z=0) : x(x), y(y), z(z) {}
    bool operator<(R p) const {
        return tie(x, y, z) < tie(p.x, p.y, p.z); }
    bool operator==(R p) const {
        return tie(x, y, z) == tie(p.x, p.y, p.z); }
    P operator+(R p) const { return P(x+p.x, y+p.y, z+p.z); }
    P operator-(R p) const { return P(x-p.x, y-p.y, z-p.z); }
    P operator*(T d) const { return P(x*d, y*d, z*d); }
    P operator/(T d) const { return P(x/d, y/d, z/d); }
    T dot(R p) const { return x*p.x + y*p.y + z*p.z; }
    P cross(R p) const {
        return P(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
    }
    T dist2() const { return x*x + y*y + z*z; }
    double dist() const { return sqrt((double)dist2()); }
    P unit() const { return *this/(T)dist(); } //makes dist()=1
    //returns point rotated 'angle' radians ccw around axis
    P rotate(double angle, P axis) const {
        double s = sin(angle), c = cos(angle); P u = axis.unit();
        return u*dot(u)*(1-c) + (*this)*c - cross(u)*s;
    }
};

template <typename T> ostream& operator << (ostream& os, const Point3D<T>& p) {
    return os << p.x << " " << p.y << " " << p.z;
}

using ptT = double;
using pt = Point3D<ptT>;
using poly = vector<pt>;

pt project_y(pt p){ return pt{p.x, 0, p.z}; }
ptT cross2(pt a, pt b) { return a.cross(b).y; }
int orientation(pt a, pt b, pt c) {
    auto cp = cross2(b - a, c - b);
    return (cp > 0) ? 1 : (cp < -0 ? -1 : 0);
}

poly giftwrap(vector<pt> ps) {
    auto o = *min_element(all(ps));
    vector<pt> res;
    auto other = [&](pt p){return ps[0] == p ? ps[1] : ps[0];};
    for (pt p = o, q = other(p); !(q == o); p = q) {
        q = other(p);
        rep(i, 0, sz(ps))
            if (orientation(p, q, ps[i]) == -1)
                q = ps[i];
        res.PB(p);
    }
    return res;
}
ptT area(const poly& ps) {
    auto acc = 0.L;
    rep(i, 0, sz(ps))
        acc += cross2(ps[i], ps[(i + 1) % sz(ps)]);
    return acc / 2;
}

ptT shadow(const poly& shape, ld angx, ld angz, poly* out = nullptr) {
    auto alien = shape;
    trav(p, alien)
        p = p.rotate(angx, pt{1, 0, 0}).rotate(angz, pt{0, 0, 1});
    if (out) *out = alien;   
    trav(p, alien) p = project_y(p);
    return area(giftwrap(alien));
}

pt center(const poly& ps) {return accumulate(all(ps), pt{}) / sz(ps);}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    poly cube;
    trav(x, signs) trav(y, signs) trav(z, signs)
        cube.PB(pt{0.5 * x, 0.5 * y, 0.5 * z});
    
    int T;
    cin >> T;
    for (int test = 1; test <= T; test++) {
        ld a;
        cin >> a;
        ld angle_x{0}, angle_z{0};
        if (a > MAX_AREA_WITH_ONE_ROTATION) angle_x = PI / 4;
        ld lo = 0.L, hi = PI / 4 + EPS;
        rep(it, 0, 60) {
            auto lh = lo + (hi - lo) / 3;
            auto uh = hi - (hi - lo) / 3;
            auto lv = abs(shadow(cube, angle_x, lh) - a);
            auto uv = abs(shadow(cube, angle_x, uh) - a);
            if (lv > uv) {
                lo = lh;
            } else {
                hi = uh;
            }
        }
        angle_z = lo;
        poly alien{};
        shadow(cube, angle_x, angle_z, &alien);
        auto sol = vector<pt>{center({alien[4], alien[5], alien[6], alien[7]}),
                              center({alien[2], alien[3], alien[6], alien[7]}),
                              center({alien[1], alien[3], alien[5], alien[7]})};
        cout << "Case #" << test << ":" << '\n';
        trav(p, sol) cout << fixed << setprecision(10) << p << '\n';
    }    
}
