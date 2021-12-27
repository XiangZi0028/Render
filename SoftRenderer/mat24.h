#ifndef MAT24_H
#define MAT24_H

#include <stdint.h>

namespace math {
    template <typename T> struct vec2;
    template <typename T> struct vec4;
    template <typename T> struct mat2;
    template <typename T> struct mat32;
    template <typename T> struct mat3;
    template <typename T> struct mat34;
    template <typename T> struct mat42;
    template <typename T> struct mat43;
    template <typename T> struct mat4;

    template <typename T>
    struct mat24 {
    private:
        vec4<T> value[2];

    public:
        mat24();
        mat24(T s);
        mat24(T x0, T y0, T z0, T w0, T x1, T y1, T z1, T w1);
        mat24(const vec4<T>& v1, const vec4<T>& v2);
        mat24(const mat24<T>& m);
        mat24(const mat34<T>& m);
        mat24(const mat4<T>& m);

        mat42<T> transpose();

        mat24<T>& operator=(const mat24<T>& m);
        vec4<T>& operator[] (size_t i);
        const vec4<T>& operator[] (size_t i) const;
        mat24<T>& operator+=(T s);
        mat24<T>& operator+=(const mat24<T>& m);
        mat24<T>& operator-=(T s);
        mat24<T>& operator-=(const mat24<T>& m);
        mat24<T>& operator*=(T s);
        mat24<T>& operator*=(const mat24<T>& m);
        mat24<T>& operator/=(T s);
        mat24<T>& operator++();
        mat24<T>& operator--();
        mat24<T>& operator++(int);
        mat24<T>& operator--(int);
    };

    template <typename T>
    mat24<T>::mat24() {
        this->value[0] = vec4<T>(1, 0, 0, 0);
        this->value[1] = vec4<T>(0, 1, 0, 0);
    }

    template <typename T>
    mat24<T>::mat24(T s) {
        this->value[0] = vec4<T>(s, 0, 0, 0);
        this->value[1] = vec4<T>(0, s, 0, 0);
    }

    template <typename T>
    mat24<T>::mat24(T x0, T y0, T z0, T w0, T x1, T y1, T z1, T w1) {
        this->value[0] = vec4<T>(x0, y0, z0, w0);
        this->value[1] = vec4<T>(x1, y1, z1, w1);
    }

    template <typename T>
    mat24<T>::mat24(const vec4<T>& v1, const vec4<T>& v2) {
        this->value[0] = v1;
        this->value[1] = v2;
    }

    template <typename T>
    mat24<T>::mat24(const mat24<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
    }

    template <typename T>
    mat24<T>::mat24(const mat34<T>& m) {
        this->value[0] = vec3<T>(m[0]);
        this->value[1] = vec3<T>(m[1]);
    }

    template <typename T>
    mat24<T>::mat24(const mat4<T>& m) {
        this->value[0] = vec3<T>(m[0]);
        this->value[1] = vec3<T>(m[1]);
    }

    template <typename T>
    mat42<T> mat24<T>::transpose() {
        mat42<T> result;
        result[0][0] = this->value[0][0];
        result[0][1] = this->value[1][0];

        result[1][0] = this->value[0][1];
        result[1][1] = this->value[1][1];

        result[2][0] = this->value[0][2];
        result[2][1] = this->value[1][2];

        result[3][0] = this->value[0][3];
        result[3][1] = this->value[1][3];
        return result;
    }

    template <typename T>
    mat24<T>& mat24<T>::operator=(const mat24<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        return *this;
    }

    template <typename T>
    vec4<T>& mat24<T>::operator[] (size_t i) {
        return this->value[i];
    }

    template <typename T>
    const vec4<T>& mat24<T>::operator[] (size_t i) const{
        return this->value[i];
    }

    template <typename T>
    mat24<T>& mat24<T>::operator+=(T s) {
        this->value[0] += s;
        this->value[1] += s;
        return *this;
    }

    template <typename T>
    mat24<T>& mat24<T>::operator+=(const mat24<T>& m) {
        this->value[0] += m[0];
        this->value[1] += m[1];
        return *this;
    }

    template <typename T>
    mat24<T>& mat24<T>::operator-=(T s) {
        this->value[0] -= s;
        this->value[1] -= s;
        return *this;
    }

    template <typename T>
    mat24<T>& mat24<T>::operator-=(const mat24<T>& m) {
        this->value[0] -= m[0];
        this->value[1] -= m[1];
        return *this;
    }

    template <typename T>
    mat24<T>& mat24<T>::operator*=(T s) {
        this->value[0] *= s;
        this->value[1] *= s;
        return *this;
    }

    template <typename T>
    mat24<T>& mat24<T>::operator*=(const mat24<T>& m) {
        return mat24<T>();
    }

    template <typename T>
    mat24<T>& mat24<T>::operator/=(T s) {
        this->value[0] /= s;
        this->value[1] /= s;
        return *this;
    }

    template <typename T>
    mat24<T>& mat24<T>::operator++() {
        ++* this->value[0];
        ++* this->value[1];
        return *this;
    }

    template <typename T>
    mat24<T>& mat24<T>::operator--() {
        --* this->value[0];
        --* this->value[1];
        return *this;
    }

    template <typename T>
    mat24<T>& mat24<T>::operator++(int) {
        mat24<T> temp = *this;
        ++* this;
        return temp;
    }

    template <typename T>
    mat24<T>& mat24<T>::operator--(int) {
        mat24<T> temp = *this;
        --* this;
        return temp;
    }

    template <typename T>
    mat24<T> operator+(const mat24<T>& m, T s) {
        return mat24<T>(m[0] + s, m[1] + s);
    }

    template <typename T>
    mat24<T> operator+(T s, const mat24<T>& m) {
        return mat24<T>(s + m[0], s + m[1]);
    }

    template <typename T>
    mat24<T> operator+(const mat24<T>& m1, const mat24<T>& m2) {
        return mat24<T>(m1[0] + m2[0], m1[1] + m2[1]);
    }

    template <typename T>
    mat24<T> operator-(const mat24<T>& m) {
        return mat24<T>(-m[0], -m[1]);
    }

    template <typename T>
    mat24<T> operator-(const mat24<T>& m, T s) {
        return mat24<T>(m[0] - s, m[1] - s);
    }

    template <typename T>
    mat24<T> operator-(T s, const mat24<T>& m) {
        return mat24<T>(s - m[0], s - m[1]);
    }

    template <typename T>
    mat24<T> operator-(const mat24<T>& m1, const mat24<T>& m2) {
        return mat24<T>(m1[0] - m2[0], m1[1] - m2[1]);
    }

    template <typename T>
    mat24<T> operator*(const mat24<T>& m, T s) {
        return mat24<T>(m[0] * s, m[1] * s);
    }

    template <typename T>
    mat24<T> operator*(T s, const mat24<T>& m) {
        return mat24<T>(s * m[0], s * m[1]);
    }

    template <typename T>
    vec4<T> operator*(const mat24<T>& m, const vec2<T>& v) {
        return vec4<T>(m[0][0] * v.x + m[1][0] * v.y,
            m[0][1] * v.x + m[1][1] * v.y,
            m[0][2] * v.x + m[1][2] * v.y,
            m[0][3] * v.x + m[1][3] * v.y);
    }

    template <typename T>
    vec2<T> operator*(const vec4<T>& v, const mat24<T>& m) {
        return vec2<T>(v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + v.w * m[0][3],
            v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + v.w * m[1][3]);
    }

    template <typename T>
    mat24<T> operator*(const mat24<T>& m1, const mat2<T>& m2) {
        return mat24<T>(
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
            m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
            m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1],
            m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1],
            m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
            m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
            m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1],
            m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1]);
    }

    template <typename T>
    mat4<T> operator*(const mat24<T>& m1, const mat42<T>& m2) {
        T SrcA00 = m1[0][0];
        T SrcA01 = m1[0][1];
        T SrcA02 = m1[0][2];
        T SrcA03 = m1[0][3];
        T SrcA10 = m1[1][0];
        T SrcA11 = m1[1][1];
        T SrcA12 = m1[1][2];
        T SrcA13 = m1[1][3];

        T SrcB00 = m2[0][0];
        T SrcB01 = m2[0][1];
        T SrcB10 = m2[1][0];
        T SrcB11 = m2[1][1];
        T SrcB20 = m2[2][0];
        T SrcB21 = m2[2][1];
        T SrcB30 = m2[3][0];
        T SrcB31 = m2[3][1];

        mat4<T> Result();
        Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01;
        Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01;
        Result[0][2] = SrcA02 * SrcB00 + SrcA12 * SrcB01;
        Result[0][3] = SrcA03 * SrcB00 + SrcA13 * SrcB01;
        Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11;
        Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11;
        Result[1][2] = SrcA02 * SrcB10 + SrcA12 * SrcB11;
        Result[1][3] = SrcA03 * SrcB10 + SrcA13 * SrcB11;
        Result[2][0] = SrcA00 * SrcB20 + SrcA10 * SrcB21;
        Result[2][1] = SrcA01 * SrcB20 + SrcA11 * SrcB21;
        Result[2][2] = SrcA02 * SrcB20 + SrcA12 * SrcB21;
        Result[2][3] = SrcA03 * SrcB20 + SrcA13 * SrcB21;
        Result[3][0] = SrcA00 * SrcB30 + SrcA10 * SrcB31;
        Result[3][1] = SrcA01 * SrcB30 + SrcA11 * SrcB31;
        Result[3][2] = SrcA02 * SrcB30 + SrcA12 * SrcB31;
        Result[3][3] = SrcA03 * SrcB30 + SrcA13 * SrcB31;
        return Result;
    }

    template <typename T>
    mat43<T> operator*(const mat24<T>& m1, const mat32<T>& m2) {
        return mat43<T>(
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
            m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
            m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1],
            m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1],
            m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
            m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
            m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1],
            m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1],
            m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1],
            m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1],
            m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1],
            m1[0][3] * m2[2][0] + m1[1][3] * m2[2][1]);
    }

    template <typename T>
    mat24<T> operator/(const mat24<T>& m, T s) {
        return mat24<T>(m[0] / s, m[1] / s);
    }

    template <typename T>
    mat24<T> operator/(T s, const mat24<T>& m) {
        return mat24<T>(s / m[0], s / m[1]);
    }
}

#endif // !MAT24_H
