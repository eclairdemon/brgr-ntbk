/*
 * A Fenwick tree supporting range-add and range-sum queries.
 * Supports adding a value & finding the sum over all elements in a range.
 * Time: O(log n) per operation
 * 
 * USAGE:
 * T: data type of array, should be int, long long, mint
 * 1. Fenwick<T> fw(n);         Initializes a tree on an array with n zeros
 * 2. Fenwick<T> fw(a)          Initializes a tree on a vector a
 * 3. fw.add(l, r, x)           Adds x to a[l], a[l+1], ..., a[r]
 * 4. fw.sum(l, r)              Returns a[l] + a[l+1] + ... + a[r]
*/

template <typename T>
struct Fenwick {
    vector<T> bit1;
    vector<T> bit2;
    Fenwick(int n): bit1(n), bit2(n) {}
    Fenwick(vector<T> &arr): bit1(arr.size()), bit2(arr.size()) {
        for (int i = 0; i < arr.size(); i++) add(i, i, arr[i]);
    }

    void _padd(vector<T> &bit, int i, T x) {
        for (; i < bit.size(); i |= i+1) bit[i] += x;
    }

    T _psum(vector<T> &bit, int i) {
        T res = 0;
        for (; i > 0; i &= i-1) res += bit[i-1];
        return res;
    }

    void add(int l, int r, T x) {
        _padd(bit1, l, x);
        _padd(bit1, r+1, -x);
        _padd(bit2, l, x*l);
        _padd(bit2, r+1, -x*(r+1));
    }

    // Returns a[l] + a[l+1] + ... + a[r]
    T sum(int l, int r) {
        return _psum(bit1, r+1)*(r+1) - _psum(bit2, r+1) - _psum(bit1, l)*l + _psum(bit2, l);
    }
};
