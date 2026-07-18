#include "template.h"

/**
 * A vector of reals.
 */
template<typename T>
struct Vector {
    vec<T> v;

    Vector() = default;
    explicit Vector(size_t n) : v(n, T(0)) {}
    Vector(initializer_list<T> il) : v(il) {}

    size_t size() const noexcept { return v.size(); }

    T& operator[](size_t i) { return v[i]; }
    const T& operator[](size_t i) const { return v[i]; }

    Vector operator+(const Vector& o) const {
        if(size() != o.size()) throw invalid_argument("Vector sizes must match: " + to_string(size()) + " vs " + to_string(o.size()));
        Vector r(size());
        for (int i = 0; i < size(); i++) r.v[i] = v[i] + o.v[i];
        return r;
    }

    Vector operator-(const Vector& o) const {
        if(size() != o.size()) throw invalid_argument("Vector sizes must match: " + to_string(size()) + " vs " + to_string(o.size()));
        Vector r(size());
        for (int i = 0; i < size(); i++) r.v[i] = v[i] - o.v[i];
        return r;
    }

    T operator*(const Vector& o) const {
        if(size() != o.size()) throw invalid_argument("Vector sizes must match: " + to_string(size()) + " vs " + to_string(o.size()));
        T s = 0;
        for (int i = 0; i < size(); i++) s += v[i] * o.v[i];
        return s;
    }

    Vector operator*(T s) const {
        Vector r(size());
        for (int i = 0; i < size(); i++) r.v[i] = v[i] * s;
        return r;
    }

    Vector operator/(T s) const {
        if (s == T(0)) throw domain_error("Division by zero");
        Vector r(size());
        for (int i = 0; i < size(); i++) r.v[i] = v[i] / s;
        return r;
    }

    Vector& operator+=(const Vector& o) { 
        if(size() != o.size()) throw invalid_argument("Vector sizes must match: " + to_string(size()) + " vs " + to_string(o.size())); 
        for(int i = 0; i < size(); i++) v[i] += o.v[i]; 
        return *this; 
    }
    
    Vector& operator-=(const Vector& o) { 
        if(size() != o.size()) throw invalid_argument("Vector sizes must match: " + to_string(size()) + " vs " + to_string(o.size())); 
        for(int i = 0; i < size(); i++) v[i] -= o.v[i]; 
        return *this; 
    }
    
    Vector& operator*=(T s) { 
        for(int i = 0; i < size(); i++) v[i] *= s; 
        return *this; 
    }
    
    Vector& operator/=(T s) { 
        if (s == T(0)) throw domain_error("Division by zero"); 
        for(int i = 0; i < size(); i++) v[i] /= s; 
        return *this; 
    }

    T norm2() const { return (*this) * (*this); }
    auto norm() const { return sqrt(norm2()); }

    bool same_size(const Vector& o) const noexcept { return size() == o.size(); }
};

template<typename T>
inline Vector<T> operator*(T s, const Vector<T>& a) { return a * s; }

template<typename T>
struct Matrix {
    ll n, m;
    vec<vec<T>> mat;

    Matrix() : n(0), m(0) {}

    Matrix(ll N, ll M) : n(N), m(M), mat(N, vec<T>(M, T(0))) {}

    Matrix(vec<vec<T>> a) : mat(move(a)) {
        n = mat.size();
        m = n ? mat[0].size() : 0;
    }

    Matrix(const vec<Vector<T>>& vecs) {
        n = vecs.size();
        m = n ? vecs[0].size() : 0;
        mat.assign(n, vec<T>(m, T(0)));
        for (int i = 0; i < n; i++) {
            if (vecs[i].size() != m) {
                throw invalid_argument("All vecs must have the same size to form a matrix.");
            }
            for (int j = 0; j < m; j++) {
                mat[i][j] = vecs[i][j];
            }
        }
    }

    static Matrix identity(ll dim) {
        Matrix out(dim, dim);
        for (int i = 0; i < dim; i++) {
            out.mat[i][i] = T(1);
        }
        return out;
    }

    size_t rows() const noexcept { return n; }
    size_t cols() const noexcept { return m; }

    Matrix operator+(const Matrix &o) const {
        if (n != o.n || m != o.m) {
            throw invalid_argument("Dimension mismatch for addition: (" + to_string(n) + "x" + to_string(m) + ") vs (" + to_string(o.n) + "x" + to_string(o.m) + ")");
        }
        Matrix out(n, m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                out.mat[i][j] = mat[i][j] + o.mat[i][j];
            }
        }
        return out;
    }

    Matrix operator-(const Matrix &o) const {
        if (n != o.n || m != o.m) {
            throw invalid_argument("Dimension mismatch for subtraction: (" + to_string(n) + "x" + to_string(m) + ") vs (" + to_string(o.n) + "x" + to_string(o.m) + ")");
        }
        Matrix out(n, m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                out.mat[i][j] = mat[i][j] - o.mat[i][j];
            }
        }
        return out;
    }

    Matrix operator*(const Matrix &o) const {
        if (m != o.n) {
            throw invalid_argument("Dimension mismatch for multiplication: columns of first (" + to_string(m) + ") must match rows of second (" + to_string(o.n) + ")");
        }
        Matrix out(n, o.m);
        for(int i = 0; i < n; i++) {
            for(int k = 0; k < m; k++) {
                T val = mat[i][k];
                if (val == T(0)) continue; 
                for(int j = 0; j < o.m; j++) {
                    out.mat[i][j] += val * o.mat[k][j];
                }
            }
        }
        return out;
    }

    Matrix& operator+=(const Matrix &o) {
        if (n != o.n || m != o.m) {
            throw invalid_argument("Dimension mismatch for addition: (" + to_string(n) + "x" + to_string(m) + ") vs (" + to_string(o.n) + "x" + to_string(o.m) + ")");
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                mat[i][j] += o.mat[i][j];
            }
        }
        return *this;
    }

    Matrix& operator-=(const Matrix &o) {
        if (n != o.n || m != o.m) {
            throw invalid_argument("Dimension mismatch for subtraction: (" + to_string(n) + "x" + to_string(m) + ") vs (" + to_string(o.n) + "x" + to_string(o.m) + ")");
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                mat[i][j] -= o.mat[i][j];
            }
        }
        return *this;
    }

    Matrix& operator*=(const Matrix &o) {
        return *this = *this * o;
    }

    Matrix operator%(T mod) const {
        if (mod == T(0)) throw domain_error("Modulo by zero");
        Matrix out(n, m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                out.mat[i][j] = mat[i][j] % mod;
            }
        }
        return out;
    }

    Matrix& operator%=(T mod) {
        if (mod == T(0)) throw domain_error("Modulo by zero");
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                mat[i][j] %= mod;
            }
        }
        return *this;
    }
};