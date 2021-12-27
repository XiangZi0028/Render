#pragma once
#include <stdint.h>

namespace math {
    template <typename T> struct vec2;
    template <typename T> struct mat23;
    template <typename T> struct mat24;
    template <typename T> struct mat32;
    template <typename T> struct mat3;
    template <typename T> struct mat34;
    template <typename T> struct mat42;
    template <typename T> struct mat43;
    template <typename T> struct mat4;

    template <typename T>
    struct mat2 {
    private:
        vec2<T> value[2];
    public:
        mat2();
        mat2(T s);
        mat2(T x0, T y0, T x1, T y1);
        mat2(const vec2<T>& v0, const vec2<T>& v1);
        mat2(const mat2<T>& m);
        mat2(const mat23<T>& m);
        mat2(const mat24<T>& m);
        mat2(const mat32<T>& m);
        mat2(const mat3<T>& m);
        mat2(const mat34<T>& m);
        mat2(const mat42<T>& m);
        mat2(const mat43<T>& m);
        mat2(const mat4<T>& m);

        mat2<T> inverse();
        mat2<T> transpose();
        
        mat2<T>& operator=(const mat2& m);
        vec2<T>& operator[](size_t i);
        const vec2<T>& operator[](size_t i)const;
        mat2<T>& operator+=(T s);
        mat2<T>& operator+=(const mat2<T>& m);
        mat2<T>& operator-=(T s);
        mat2<T>& operator-=(const mat2<T>& m);
        mat2<T>& operator*=(T s);
        mat2<T>& operator*=(const mat2<T>& m);
        mat2<T>& operator/=(T s);
        mat2<T>& operator/=(const mat2<T>& m);
        mat2<T>& operator++();
        mat2<T>& operator--();
        mat2<T> operator++(int);
        mat2<T> operator--(int);
    };

    template <typename T>
    mat2<T>::mat2() {
        this->value[0] = vec2<T>(1, 0);
        this->value[1] = vec2<T>(0, 1);
    }

    template <typename T>
    mat2<T>::mat2(T s) {
        this->value[0] = vec2<T>(s, 0);
        this->value[1] = vec2<T>(0, s);
    }

    template <typename T>
    mat2<T>::mat2(T x0, T y0, T x1, T y1) {
        this->value[0] = vec2<T>(x0, y0);
        this->value[1] = vec2<T>(x1, y1);
    }

    template <typename T>
    mat2<T>::mat2(const vec2<T>& v0, const vec2<T>& v1) {
        this->value[0] = v0;
        this->value[1] = v1;
    }

    template <typename T>
    mat2<T>::mat2(const mat2<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
    }

    template <typename T>
    mat2<T>::mat2(const mat23<T>& m) {
        this->value[0] = vec2<T>(m[0]);
        this->value[1] = vec2<T>(m[1]);
    }

    template <typename T>
    mat2<T>::mat2(const mat24<T>& m) {
        this->value[0] = vec2<T>(m[0]);
        this->value[1] = vec2<T>(m[1]);
    }

    template <typename T>
    mat2<T>::mat2(const mat32<T>& m) {
        this->value[0] = vec2<T>(m[0]);
        this->value[1] = vec2<T>(m[1]);
    }

    template <typename T>
    mat2<T>::mat2(const mat3<T>& m) {
        this->value[0] = vec2<T>(m[0]);
        this->value[1] = vec2<T>(m[1]);
    }

    template <typename T>
    mat2<T>::mat2(const mat34<T>& m) {
        this->value[0] = vec2<T>(m[0]);
        this->value[1] = vec2<T>(m[1]);
    }

    template <typename T>
    mat2<T>::mat2(const mat42<T>& m) {
        this->value[0] = vec2<T>(m[0]);
        this->value[1] = vec2<T>(m[1]);
    }

    template <typename T>
    mat2<T>::mat2(const mat43<T>& m) {
        this->value[0] = vec2<T>(m[0]);
        this->value[1] = vec2<T>(m[1]);
    }

    template <typename T>
    mat2<T>::mat2(const mat4<T>& m) {
        this->value[0] = vec2<T>(m[0]);
        this->value[1] = vec2<T>(m[1]);
    }

    template <typename T>
    mat2<T> mat2<T>::inverse() {
        T determinant = this->value[0][0] * this->value[1][1] - this->value[1][0] * this->value[0][1];
        return mat2<T>(this->value[1][1] / determinant,
            this->value[1][0] / determinant,
            this->value[0][1] / determinant,
            this->value[0][0] / determinant);
    }

    template <typename T>
    mat2<T> mat2<T>::transpose() {
        mat2<T> result;
        result[0][0] = this->value[0][0];
        result[0][1] = this->value[1][0];

        result[1][0] = this->value[0][1];
        result[1][1] = this->value[1][1];
        return result;
    }

    template <typename T>
    mat2<T>& mat2<T>::operator=(const mat2<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        return *this;
    }

    template <typename T>
    vec2<T>& mat2<T>::operator[](size_t i) {
        return this->value[i];
    }

    template <typename T>
    const vec2<T>& mat2<T>::operator[](size_t i) const {
        return this->value[i];
    }

    template <typename T>
    mat2<T>& mat2<T>::operator+=(T s) {
        this->value[0] += s;
        this->value[1] += s;
        return *this;
    }

    template <typename T>
    mat2<T>& mat2<T>::operator+=(const mat2<T>& m) {
        this->value[0] += m[0];
        this->value[1] += m[1];
    }

    template <typename T>
    mat2<T>& mat2<T>::operator-=(T s) {
        this->value[0] -= s;
        this->value[1] -= s;
        return *this;
    }

    template <typename T>
    mat2<T>& mat2<T>::operator-=(const mat2<T>& m) {
        this->value[0] -= m[0];
        this->value[1] -= m[1];
        return *this;
    }

    template <typename T>
    mat2<T>& mat2<T>::operator*=(T s) {
        this->value[0] *= s;
        this->value[1] *= s;
        return *this;
    }

    template <typename T>
    mat2<T>& mat2<T>::operator*=(const mat2<T>& m) {
        return *this = *this * m;
    }

    template <typename T>
    mat2<T>& mat2<T>::operator/=(T s) {
        this->value[0] /= s;
        this->value[1] /= s;
        return *this;
    }

    template <typename T>
    mat2<T>& mat2<T>::operator/=(const mat2<T>& m) {
        this->value[0] /= m[0];
        this->value[1] /= m[1];
        return *this;
    }

    template <typename T>
    mat2<T>& mat2<T>::operator++() {
        ++this->value[0];
        ++this->value[1];
        return *this;
    }

    template <typename T>
    mat2<T>& mat2<T>::operator--() {
        --this->value[0];
        --this->value[1];
        return *this;
    }

    template <typename T>
    mat2<T> mat2<T>::operator++(int) {
        mat2<T> temp = *this;
        ++* this;
        return temp;
    }

    template <typename T>
    mat2<T> mat2<T>::operator--(int) {
        mat2<T> temp = *this;
        --* this;
        return temp;
    }

    template <typename T>
    mat2<T> operator+(const mat2<T>& m, T s) {
        return mat2<T>(m) += s;
    }

    template <typename T>
    mat2<T> operator+(T s, const mat2<T>& m) {
        return mat2<T>(s) += m;
    }

    template <typename T>
    mat2<T> operator+(const mat2<T>& m, const vec2<T>& v) {
        return mat2<T>(m[0] + v, m[1] + v);
    }

    template <typename T>
    mat2<T> operator+(const vec2<T>& v, const mat2<T>& m) {
        return mat2<T>(v + m[0], v + m[1]);
    }

    template <typename T>
    mat2<T> operator+(const mat2<T>& m1, const mat2<T>& m2) {
        return mat2<T>(m1) += m2;
    }

    template <typename T>
    mat2<T> operator-(const mat2<T>& m) {
        return mat2<T>(-m[0], -m[1]);
    }

    template <typename T>
    mat2<T> operator-(const mat2<T>& m, T s) {
        return mat2<T>(m) -= s;
    }

    template <typename T>
    mat2<T> operator-(T s, const mat2<T>& m) {
        return mat2<T>(s) -= m;
    }

    template <typename T>
    mat2<T> operator-(const mat2<T>& m, const vec2<T>& v) {
        return mat2<T>(m[0] - v, m[1] - v);
    }

    template <typename T>
    mat2<T> operator-(const vec2<T>& v, const mat2<T>& m) {
        return mat2<T>(v - m[0], v - m[1]);
    }

    template <typename T>
    mat2<T> operator*(const mat2<T>& m, T s) {
        return mat2<T>(m[0] * s, m[1] * s);
    }

    template <typename T>
    mat2<T> operator*(T s, const mat2<T>& m) {
        return m * s;
    }

    // ����Ԫ
    template <typename T>
    vec2<T> operator*(const mat2<T>& m, const vec2<T>& v) {
        return vec2<T>(
            m[0][0] * v.x + m[1][0] * v.y,
            m[0][1] * v.x + m[1][1] * v.y);
    }

    // ����Ԫ
    template <typename T>
    vec2<T> operator*(const vec2<T>& v, const mat2<T>& m) {
        return vec2<T>(
            v.x * m[0][0] + v.y * m[0][1],
            v.x * m[1][0] + v.y * m[1][1]);
    }

    // ����Ԫ
    template <typename T>
    mat2<T> operator*(const mat2<T>& m1, const mat2<T>& m2) {
        return mat2<T>(
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
            m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
            m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
            m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1]);
    }

    // ����Ԫ
    template <typename T>
    mat32<T> operator*(mat2<T> const& m1, mat32<T> const& m2) {
        return mat32<T>(
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
            m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
            m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
            m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
            m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1],
            m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1]);
    }

    // ����Ԫ
    template <typename T>
    mat42<T> operator*(const mat2<T>& m1, const mat42<T>& m2) {
        return mat42<T>(
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
            m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
            m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
            m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
            m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1],
            m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1],
            m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1],
            m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1]);
    }

    template <typename T>
    mat2<T> operator/(const mat2<T>& m, T s) {
        return mat2<T>(m) /= s;
    }

    template <typename T>
    mat2<T> operator/(const mat2<T>& m1, const mat2<T>& m2) {
        return m1 * m2.inverse();
    }
}