#ifndef MAT42_H
#define MAT42_H

#include <stdint.h>

namespace math {
    template <typename T> struct vec2;
    template <typename T> struct vec4;
    template <typename T> struct mat2;
    template <typename T> struct mat32;
    template <typename T> struct mat42;
    template <typename T> struct mat43;
    template <typename T> struct mat4;

    template <typename T>
    struct mat42 {
    private:
        vec2<T> value[4];
    public:
        mat42();
        mat42(T s);
        mat42(T x0, T y0, T x1, T y1,
            T x2, T y2, T x3, T y3);
        mat42(const vec2<T>& v0, const vec2<T>& v1,
            const vec2<T>& v2, const vec2<T>& v3);
        mat42(const mat42<T>& m);
        mat42(const mat43<T>& m);
        mat42(const mat4<T>& m);

        mat24<T> transpose();

        mat42<T>& operator=(const mat42& m);
        vec2<T>& operator[](size_t i);
        const vec2<T>& operator[](size_t i) const;
        mat42<T>& operator+=(T s);
        mat42<T>& operator+=(const mat42<T>& m);
        mat42<T>& operator-=(T s);
        mat42<T>& operator-=(const mat42<T>& m);
        mat42<T>& operator*=(T s);
        mat42<T>& operator*=(const mat42<T>& m);
        mat42<T>& operator/=(T s);
        mat42<T>& operator/=(const mat42<T>& m);
        mat42<T>& operator++();
        mat42<T>& operator--();
        mat42<T> operator++(int);
        mat42<T> operator--(int);
    };

    template <typename T>
    mat42<T>::mat42() {
        this->value[0] = vec2<T>(1, 0);
        this->value[1] = vec2<T>(0, 1);
        this->value[2] = vec2<T>(0, 0);
        this->value[3] = vec2<T>(0, 0);
    }

    template <typename T>
    mat42<T>::mat42(T s) {
        this->value[0] = vec2<T>(s, 0);
        this->value[1] = vec2<T>(0, s);
        this->value[2] = vec2<T>(0, 0);
        this->value[3] = vec2<T>(0, 0);
    }

    template <typename T>
    mat42<T>::mat42(
        T x0, T y0,
        T x1, T y1,
        T x2, T y2,
        T x3, T y3) {
        this->value[0] = vec2<T>(x0, y0);
        this->value[1] = vec2<T>(x1, y1);
        this->value[2] = vec2<T>(x2, y2);
        this->value[3] = vec2<T>(x3, y3);
    }

    template <typename T>
    mat42<T>::mat42(const vec2<T>& v0, const vec2<T>& v1,
        const vec2<T>& v2, const vec2<T>& v3) {
        this->value[0] = v0;
        this->value[1] = v1;
        this->value[2] = v2;
        this->value[3] = v3;
    }

    template <typename T>
    mat42<T>::mat42(const mat42<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
        this->value[3] = m[3];
    }

    template <typename T>
    mat42<T>::mat42(const mat43<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
        this->value[3] = m[3];
    }

    template <typename T>
    mat42<T>::mat42(const mat4<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
        this->value[3] = m[3];
    }

    template <typename T>
    mat24<T> mat42<T>::transpose() {
        mat24<T> result;
        result[0][0] = this->value[0][0];
        result[0][1] = this->value[1][0];
        result[0][2] = this->value[2][0];
        result[0][3] = this->value[3][0];

        result[1][0] = this->value[0][1];
        result[1][1] = this->value[1][1];
        result[1][2] = this->value[2][1];
        result[1][3] = this->value[3][1];
        return result;
    }

    template <typename T>
    mat42<T>& mat42<T>::operator=(const mat42& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
        this->value[3] = m[3];
        return *this;
    }

    template <typename T>
    vec2<T>& mat42<T>::operator[](size_t i) {
        return this->value[i];
    }

    template <typename T>
    const vec2<T>& mat42<T>::operator[](size_t i) const {
        return this->value[i];
    }

    template <typename T>
    mat42<T>& mat42<T>::operator+=(T s) {
        this->value[0] += s;
        this->value[1] += s;
        this->value[2] += s;
        this->value[3] += s;
        return *this;
    }

    template <typename T>
    mat42<T>& mat42<T>::operator+=(const mat42<T>& m) {
        this->value[0] += m[0];
        this->value[1] += m[1];
        this->value[2] += m[2];
        this->value[3] += m[3];
    }

    template <typename T>
    mat42<T>& mat42<T>::operator-=(T s) {
        this->value[0] -= s;
        this->value[1] -= s;
        this->value[2] -= s;
        this->value[3] -= s;
        return *this;
    }

    template <typename T>
    mat42<T>& mat42<T>::operator-=(const mat42<T>& m) {
        this->value[0] -= m[0];
        this->value[1] -= m[1];
        this->value[1] -= m[1];
        this->value[1] -= m[1];
        return *this;
    }

    template <typename T>
    mat42<T>& mat42<T>::operator*=(T s) {
        this->value[0] *= s;
        this->value[1] *= s;
        this->value[2] *= s;
        this->value[3] *= s;
        return *this;
    }

    template <typename T>
    mat42<T>& mat42<T>::operator*=(const mat42<T>& m) {
        return *this = *this * m;
    }

    template <typename T>
    mat42<T>& mat42<T>::operator/=(T s) {
        this->value[0] /= s;
        this->value[1] /= s;
        this->value[2] /= s;
        this->value[3] /= s;
        return *this;
    }

    template <typename T>
    mat42<T>& mat42<T>::operator/=(const mat42<T>& m) {
        this->value[0] /= m[0];
        this->value[1] /= m[1];
        this->value[2] /= m[2];
        this->value[3] /= m[3];
        return *this;
    }

    template <typename T>
    mat42<T>& mat42<T>::operator++() {
        ++this->value[0];
        ++this->value[1];
        ++this->value[2];
        ++this->value[3];
        return *this;
    }

    template <typename T>
    mat42<T>& mat42<T>::operator--() {
        --this->value[0];
        --this->value[1];
        --this->value[2];
        --this->value[3];
        return *this;
    }

    template <typename T>
    mat42<T> mat42<T>::operator++(int) {
        mat42<T> temp = *this;
        ++* this;
        return temp;
    }

    template <typename T>
    mat42<T> mat42<T>::operator--(int) {
        mat42<T> temp = *this;
        --* this;
        return temp;
    }

    template <typename T>
    mat42<T> operator+(const mat42<T>& m, T s) {
        return mat42<T>(m) += s;
    }

    template <typename T>
    mat42<T> operator+(T s, const mat42<T>& m) {
        return mat42<T>(s) += m;
    }

    template <typename T>
    mat42<T> operator+(const mat42<T>& m, const vec2<T>& v) {
        return mat42<T>(m[0] + v, m[1] + v, m[2] + v, m[3] + v);
    }

    template <typename T>
    mat42<T> operator+(const vec2<T>& v, const mat42<T>& m) {
        return mat42<T>(v + m[0], v + m[1], v + m[2], v + m[3]);
    }

    template <typename T>
    mat42<T> operator+(const mat42<T>& m1, const mat42<T>& m2) {
        return mat42<T>(m1) += m2;
    }

    template <typename T>
    mat42<T> operator-(const mat42<T>& m, T s) {
        return mat42<T>(m) -= s;
    }

    template <typename T>
    mat42<T> operator-(const mat42<T>& m) {
        return mat42<T>(-m[0], -m[1], -m[2], -m[3]);
    }

    template <typename T>
    mat42<T> operator-(T s, const mat42<T>& m) {
        return mat42<T>(s) -= m;
    }

    template <typename T>
    mat42<T> operator-(const mat42<T>& m, const vec2<T>& v) {
        return mat42<T>(m[0] - v, m[1] - v, m[2] - v, m[3] - v);
    }

    template <typename T>
    mat42<T> operator-(const vec2<T>& v, const mat42<T>& m) {
        return mat42<T>(v - m[0], v - m[1], v - m[2], v - m[3]);
    }

    template <typename T>
    mat42<T> operator*(const mat42<T>& m, T s) {
        return mat42<T>(m[0] * s, m[1] * s, m[2] * s, m[3] * s);
    }

    template <typename T>
    mat42<T> operator*(T s, const mat42<T>& m) {
        return m * s;
    }

    // ����Ԫ
    template <typename T>
    vec2<T> operator*(const mat42<T>& m, const vec4<T>& v) {
        return vec2<T>(
            m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
            m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w);
    }

    // ����Ԫ
    template <typename T>
    vec4<T> operator*(const vec2<T>& v, const mat42<T>& m) {
        return vec4<T>(
            v.x * m[0][0] + v.y * m[0][1],
            v.x * m[1][0] + v.y * m[1][1],
            v.x * m[2][0] + v.y * m[2][1],
            v.x * m[3][0] + v.y * m[3][1]);
    }

    // ����Ԫ
    template <typename T>
    mat42<T> operator*(const mat42<T>& m1, const mat4<T>& m2) {
        return mat42<T>(
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
            m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
            m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
            m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
            m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] + m1[3][0] * m2[2][3],
            m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] + m1[3][1] * m2[2][3],
            m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1] + m1[2][0] * m2[3][2] + m1[3][0] * m2[3][3],
            m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1] + m1[2][1] * m2[3][2] + m1[3][1] * m2[3][3]);
    }

    // ����Ԫ
    template <typename T>
    mat32<T> operator*(mat42<T> const& m1, mat34<T> const& m2) {
        return mat32<T>(
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
            m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
            m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
            m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
            m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] + m1[3][0] * m2[2][3],
            m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] + m1[3][1] * m2[2][3]);
    }

    // ����Ԫ
    template <typename T>
    mat2<T> operator*(const mat42<T>& m1, const mat24<T>& m2) {
        T const SrcA00 = m1[0][0];
        T const SrcA01 = m1[0][1];
        T const SrcA10 = m1[1][0];
        T const SrcA11 = m1[1][1];
        T const SrcA20 = m1[2][0];
        T const SrcA21 = m1[2][1];
        T const SrcA30 = m1[3][0];
        T const SrcA31 = m1[3][1];

        T const SrcB00 = m2[0][0];
        T const SrcB01 = m2[0][1];
        T const SrcB02 = m2[0][2];
        T const SrcB03 = m2[0][3];
        T const SrcB10 = m2[1][0];
        T const SrcB11 = m2[1][1];
        T const SrcB12 = m2[1][2];
        T const SrcB13 = m2[1][3];

        mat2<T> Result();
        Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02 + SrcA30 * SrcB03;
        Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02 + SrcA31 * SrcB03;
        Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12 + SrcA30 * SrcB13;
        Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12 + SrcA31 * SrcB13;
        return Result;
    }

    template <typename T>
    mat42<T> operator/(const mat42<T>& m, T s) {
        return mat42<T>(m) /= s;
    }
}

#endif // !MAT42_H
