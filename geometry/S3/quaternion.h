/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef QUATERNION_H
#define QUATERNION_H

#include "geometry/E3/vector_e3.h"
#include <cmath>
#include <iostream>
using std::ostream;
using std::istream;

template<typename NT>
class Quaternion;

template<typename NT>
ostream & operator<< (ostream & os, const Quaternion<NT> & p);

template<typename NT>
istream & operator>> (istream & is, Quaternion<NT> & p);

template<typename NT>
class Quaternion
{
    NT _r, _vi, _vj, _vk;
public:
    Quaternion(const NT & r, const NT & vi, const NT & vj, const NT & vk)
        : _r(r), _vi(vi), _vj(vj), _vk(vk) {}
    Quaternion()
        : _r(1), _vi(0), _vj(0), _vk(0) {}
    Quaternion(const NT & theta, const Vector_E3<NT> & V)
    {
        NT c = cos(theta/2.0);
        NT s = sin(theta/2.0);
        _r = c;
        _vi = s * V.x();
        _vj = s * V.y();
        _vk = s * V.z();
    }

    NT norm() const { return _r*_r + _vi*_vi + _vj*_vj + _vk*_vk; }

    NT magnitude() const { return std::sqrt(norm()); }

    NT r()  const { return _r; }
    NT vi() const { return _vi; }
    NT vj() const { return _vj; }
    NT vk() const { return _vk; }

    NT real() const { return _r; }
    Vector_E3<NT> imaginary() const { return Vector_E3<NT>(_vi, _vj, _vk); }

    Quaternion<NT>
    conjugate() const {
        return Quaternion<NT>(_r, -_vi, -_vj, -_vk);
    }

    Quaternion<NT>
    inverse() const {
        return (conjugate() / norm());
    }

    bool operator==(const Quaternion<NT> & q) const {
        return (this == &q) ||
            (_r == q._r && _vi == q._vi && _vj == q._vj && _vk == _vk);
    }
    bool operator!=(const Quaternion<NT> & q) const { return !operator==(q); }

    Quaternion<NT>
    operator+(const Quaternion<NT> & q2) const
    {
        return Quaternion(_r+q2._r, _vi+q2._vi, _vj+q2._vj, _vk+q2._vk);
    }
    Quaternion<NT>
    operator-(const Quaternion<NT> & q2) const
    {
        return Quaternion(_r-q2._r, _vi-q2._vi, _vj-q2._vj, _vk-q2._vk);
    }
    Quaternion<NT>
    operator*(const NT & k) const
    {
        return Quaternion(_r * k, _vi * k, _vj * k, _vk * k);
    }
    Quaternion<NT>
    operator/(const NT & k) const
    {
        return Quaternion(_r/k, _vi/k, _vj/k, _vk/k);
    }

    Quaternion<NT>
    operator*(const Quaternion<NT> & q2) const
    {
        // ii = jj = kk = -1
        NT newr  = _r * q2._r  - _vi * q2._vi - _vj * q2._vj - _vk * q2._vk;
        // jk = -kj = i;  ki = -ik = j;  ij = -ji = k
        NT newvi = _r * q2._vi + _vi * q2._r  + _vj * q2._vk - _vk * q2._vj;
        NT newvj = _r * q2._vj + _vj * q2._r  + _vk * q2._vi - _vi * q2._vk;
        NT newvk = _r * q2._vk + _vk * q2._r  + _vi * q2._vj - _vj * q2._vi;
        return Quaternion(newr, newvi, newvj, newvk);
    }

    // Use Transformation_S2 instead.
    // Quaternion<NT>
    // rotate(const Vector_E3<NT> & V) const
    // {
    //     Quaternion<NT> v(0, V);
    //     Quaternion<NT> inv = this->inverse();
    //     Quaternion<NT> vr = inv * v * (*this);
    //     return vr;
    // }

    friend ostream & operator<< <>(ostream & os, const Quaternion<NT> & q);
    friend istream & operator>> <>(istream & is, Quaternion<NT> & q);
};

template<typename NT>
ostream & operator<< (ostream & os, const Quaternion<NT> & q)
{
    return os << q._r << " " << q._vi << " " << q._vj << " " << q._vk;
}

template<typename NT>
istream & operator>> (istream & is, Quaternion<NT> & q)
{
    return is >> q._r >> q._vi >> q._vj >> q._vk;
}

template<class S>
S
dot_product(const Quaternion<S> & q1, const Quaternion<S> & q2)
{
    return q1.r() * q2.r() + q1.vi() * q2.vi() + q1.vj() * q2.vj() + q1.vk() * q2.vk();
}

#endif // QUATERNION_H
