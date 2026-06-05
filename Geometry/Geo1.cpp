/// TRANSFORMATIONS , ANGLES , Lines , Segments , Polygon


#define ld long double
const ld EPS = 1e-12 ;
typedef ld T;
typedef complex<T> pt;
#define x real() // _
#define y imag() // |


// Returns the squared magnitude (length²) of a vector/point.
// p: the vector or point whose squared length is computed.
T sq(pt p){
    return p.x * p.x + p.y * p.y;
}

// Returns the dot product of two vectors.
// v: first vector, w: second vector.
T dot(pt v, pt w){
    return v.x * w.x + v.y * w.y;
}

// Returns the 2D cross product of two vectors.
// v: first vector, w: second vector.
T cross(pt v, pt w){
    return v.x * w.y - v.y * w.x;
}

// Returns the sign of a floating-point value using EPS tolerance.
// val: the value to classify as positive, negative, or zero.
int sgn(T val){
    if(val > EPS) return 1;
    if(val < -EPS) return -1;
    return 0;
}

// Checks whether two vectors are perpendicular (orthogonal).
// v: first vector, w: second vector.
bool isPerp(pt v, pt w){
    return fabs(dot(v, w)) < EPS;
}

// Returns a vector rotated 90 degrees counter-clockwise.
// p: the vector to rotate.
pt prep(pt p){
    return {-p.y, p.x};
}

void getPoint(pt &p) {
    int xx , yy ; cin >> xx >> yy ;
    p={(T)xx,(T)yy} ;
}
//////////////////////////////////// TRANSFORMATIONS ///////////////////////////////////////////////

// Translates a point by a given vector.
// v: translation vector, p: point to be moved.
pt translate(pt v, pt p) {
    return p + v;
}

// Scales a point relative to a center by a scale factor.
// c: center of scaling, factor: scale multiplier, p: point to scale.
pt scale(pt c, ld factor, pt p) {
    pt ret = c + (p - c) ;
    ret *= factor ;
    return ret;
}

// Rotates a point around a center by an angle in radians.
// p: point to rotate, c: rotation center, a: angle in radians.
pt rot(pt p, pt c, ld a){
    pt v = p - c;
    pt rotate = {cos(a), sin(a)};
    return c + rotate * v;
}

// Applies a linear transformation defined by mapping p->fp and q->fq.
// p,q: original reference points, r: point to transform,
// fp,fq: transformed positions of p and q.
pt linearTransfo(pt p, pt q, pt r, pt fp, pt fq) {
    return fp + (r - p) * (fq - fp) / (q - p);
}

//////////////// ANGLES ////////////////////////

// Returns the orientation value , check if location of C when a-->b
// a,b,c: points used to determine turn direction.
T orient(pt a, pt b, pt c){
    return cross(b - a, c - a);
}

// Returns the smallest angle between two vectors in radians.
// v: first vector, w: second vector.
T angle(pt v, pt w){
    return acos(clamp(dot(v, w) / abs(v) / abs(w), (T)-1.0, (T)1.0));
}

// Returns the oriented angle ∠BAC in the range [0, 2π).
// a: angle vertex, b: first ray point, c: second ray point.
// Returned angle is in radians.
T orientedAngle(pt a, pt b, pt c){
    ld ampli = angle(b - a, c - a);
    if(orient(a, b, c) > 0) return ampli;
    else return 2 * M_PI - ampli;
}

// Returns the signed angle travelled from AB to AC.
// a: angle vertex, b: starting ray point, c: ending ray point.
// Returned angle is in radians and may be negative.
T angleTravelled(pt a, pt b, pt c){
    ld ampli = angle(b - a, c - a);
    if(orient(a, b, c) > 0) return ampli;
    else return -ampli;
}

// Checks whether point p lies inside angle BAC , there a--->b , a--->b  , c must be the left of a--->b .
// a: angle vertex, b: first side point, c: second side point, p: query point.
bool inAngle(pt a, pt b, pt c, pt p) {
    T abp = orient(a, b, p);
    T acp = orient(a, c, p);
    T abc = orient(a, b, c);

    if (abc < 0) swap(abp, acp);

    return (abp >= 0 && acp <= 0) ^ (abc < 0);
}

/////////////////////////////////////////////////// Lines //////////////////////////////////////////////////////////

struct line{

    pt v;     // Direction vector of the line , Normal = ( b , -a )
    T c;      // Line constant in the form cross(v, p) = c

    // Constructs a line from a direction vector and constant c.
    // v: direction vector, c: line constant.
    line(pt v, T c) : v(v), c(c) {}

    // Constructs a line from the equation ax + by = c.
    // a,b: coefficients of x and y, _c: right-hand side constant.
    line(T a, T b, T _c){
        v = {b, -a};
        c = _c;
    }

    // Constructs a line passing through two points.
    // p: first point, q: second point.
    line(pt p, pt q){
        v = q - p;
        c = cross(v, p);
    }

    // Returns the signed side value of point p relative to the line.
    // p: query point.
    T side(pt p) {
        return cross(v, p) - c;
    }

    // Returns the perpendicular distance from point p to the line.
    // p: query point.
    ld dist(pt p) {
        return abs(side(p)) / abs(v);
    }

    // Returns the squared perpendicular distance from point p to the line.
    // p: query point.
    double sqDist(pt p) {
        return side(p) * side(p) / (T)sq(v);
    }

    // Returns the line perpendicular to this line and passing through p.
    // p: point through which the perpendicular line passes.
    line prepThrought(pt p){
        return {p, p + prep(v)};
    }

    // Compares two points according to their projection on the line direction.
    // p,q: points to compare.
    bool cmpProj(pt p, pt q){
        return dot(v, p) < dot(v, q);
    }

    // Translates the line by vector t.
    // t: translation vector.
    line translate(pt t) {
        return {v, c + cross(v, t)};
    }

    // Shifts the line to the left by a given distance.
    // dist: signed shift distance.
    line shiftLeft(T dist) {
        return {v, c + dist * abs(v)};
    }

    // Returns the orthogonal projection of point p onto the line.
    // p: point to project.
    pt proj(pt p) {
        return p - prep(v) * side(p) / sq(v);
    }

    // Returns the reflection of point p across the line.
    // p: point to reflect.
    pt refl(pt p) {
        return p - prep(v) * (T)2.0 * side(p) / sq(v);
    }
};


// Computes the intersection point of two lines.
// l1,l2: input lines, out: intersection point if it exists.
bool inter(line l1, line l2, pt &out) {

    T d = cross(l1.v, l2.v);

    // Parallel lines have no unique intersection.
    if (fabs(d) < EPS) return false;
    // Intersection point (requires floating-point coordinates).
    out = (l2.v * l1.c - l1.v * l2.c) / d;
    return true;
}


// Returns one of the angle bisectors between two intersecting lines.
// l1,l2: input lines, interior: true for interior bisector, false for exterior bisector.
line bisector(line l1, line l2, bool interior) {
    assert(cross(l1.v, l2.v) != 0); // l1 and l2 cannot be parallel!
    ld sign = interior ? 1 :-1;
    return {l2.v/abs(l2.v) + l1.v/abs(l1.v) * sign,
            l2.c/abs(l2.v) + l1.c/abs(l1.v) * sign};
}

/** //////////////// Notes //////////////////////////////
    dist(p)      // perpendicular distance from point to line
    sqDist(p)    // squared perpendicular distance
    proj(p)      // projection of point onto line
    refl(p)      // reflection of point across line
    inter(...)   // line-line intersection
    bisector(...)// angle bisector between two lines
 */


//////////////////////////////////////////  SEGMENTS   //////////////////////////////////////////
 
bool inDisk(pt a, pt b, pt p) {
    return dot(a-p, b-p) <= EPS;
}
 
bool onSegment(pt a, pt b, pt c){
    return orient(a, b, c) == 0 && inDisk(a, b, c);
}

bool properInter(pt a, pt b, pt c, pt d, pt &out) {
    T oa = orient(c,d,a),
            ob = orient(c,d,b),
            oc = orient(a,b,c),
            od = orient(a,b,d);
// Proper intersection exists iff opposite signs
    if (sgn(oa)*sgn(ob) < 0 && sgn(oc)*sgn(od) < 0) {
        out = (a*ob - b*oa) / (ob-oa);
        return true;
    }
    return false;
}

// check the intersection of two Segments
set<pair<ld,ld>> inters(pt a, pt b, pt c, pt d) {
    set<pair<ld,ld>> s;
    pt out;
    if(a == c || a == d){
        s.insert(make_pair(a.x, a.y));
    }
    if(b == c || b == d){
        s.insert(make_pair(b.x, b.y));
    }
    if(s.size()) return s;
 
    if (properInter(a,b,c,d,out)) return {make_pair(out.x, out.y)};
    if (onSegment(c,d,a)) s.insert(make_pair(a.x, a.y));
    if (onSegment(c,d,b)) s.insert(make_pair(b.x, b.y));
    if (onSegment(a,b,c)) s.insert(make_pair(c.x, c.y));
    if (onSegment(a,b,d)) s.insert(make_pair(d.x, d.y));
 
    return s;
}

// calc the distance between point and segment
ld segPoint(pt a, pt b, pt p) {
    if (a != b) {
        line l(a,b);
        if (l.cmpProj(a,p) && l.cmpProj(p,b)) // if closest to projection
            return l.dist(p); // output distance to line
    }
    return min(abs(p-a), abs(p-b)); // otherwise distance to A or B
}

// calc the distance between two segments
ld segSeg(pt a, pt b, pt c, pt d) {
    pt dummy;
    if (properInter(a,b,c,d,dummy))
        return 0;
    return min({segPoint(a,b,c), segPoint(a,b,d),
                segPoint(c,d,a), segPoint(c,d,b)});
}

