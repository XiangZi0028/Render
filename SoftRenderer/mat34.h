#ifndef MAT34_H
#define MAT34_H

#include <stdint.h>

namespace math {
    template <typename T> struct vec3;
    template <typename T> struct vec4;
    template <typename T> struct mat23;
    template <typename T> struct mat3;
    template <typename T> struct mat43;
    template <typename T> struct mat4;

    template <typename T>
    struct mat34 {
    private:
        vec4<T> value[3];
    public:
        mat34();
        mat34(T s);
        mat34(
            T x0, T y0, T z0, T w0, 
            T x1, T y1, T z1, T w1, 
            T x2, T y2, T z2, T w2);
        mat34(const vec4<T>& v0, const vec4<T>& v1,
            const vec4<T>& v2);
        mat34(const mat34<T>& m);
        mat34(const mat4<T>& m);

        mat43<T> transpose();

        mat34<T>& operator=(const mat34& m);
        vec3<T>& operator[](size_t i);
        const vec3<T>& operator[](size_t i) const;
        mat34<T>& operator+=(T s);
        mat34<T>& operator+=(const mat34<T>& m);
        mat34<T>& operator-=(T s);
        mat34<T>& operator-=(const mat34<T>& m);
        mat34<T>& operator*=(T s);
        mat34<T>& operator*=(const mat34<T>& m);
        mat34<T>& operator/=(T s);
        mat34<T>& operator/=(const mat34<T>& m);
        mat34<T>& operator++();
        mat34<T>& operator--();
        mat34<T> operator++(int);
        mat34<T> operator--(int);
    };

    template <typename T>
    mat34<T>::mat34() {
        this->value[0] = vec4<T>(1, 0, 0, 0);
        this->value[1] = vec4<T>(0, 1, 0, 0);
        this->value[2] = vec4<T>(0, 0, 1, 0);
    }

    template <typename T>
    mat34<T>::mat34(T s) {
        this->value[0] = vec4<T>(s, 0, 0, 0);
        this->value[1] = vec4<T>(0, s, 0, 0);
        this->value[2] = vec4<T>(0, 0, s, 0);
    }

    template <typename T>
    mat34<T>::mat34(
        T x0, T y0, T z0, T w0,
        T x1, T y1, T z1, T w1,
        T x2, T y2, T z2, T w2) {
        this->value[0] = vec4<T>(x0, y0, z0, w0);
        this->value[1] = vec4<T>(x1, y1, z1, w1);
        this->value[2] = vec4<T>(x2, y2, z2, w2);
    }

    template <typename T>
    mat34<T>::mat34(const vec4<T>& v0, const vec4<T>& v1, const vec4<T>& v2) {
        this->value[0] = v0;
        this->value[1] = v1;
        this->value[2] = v2;
    }

    template <typename T>
    mat34<T>::mat34(const mat34<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
    }

    template <typename T>
    mat34<T>::mat34(const mat4<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
    }

    template <typename T>
    mat43<T> mat34<T>::transpose() {
        mat43<T> result;
        result[0][0] = this->value[0][0];
        result[0][1] = this->value[1][0];
        result[0][2] = this->value[2][0];

        result[1][0] = this->value[0][1];
        result[1][1] = this->value[1][1];
        result[1][2] = this->value[2][1];

        result[2][0] = this->value[0][2];
        result[2][1] = this->value[1][2];
        result[2][2] = this->value[2][2];

        result[3][0] = this->value[0][3];
        result[3][1] = this->value[1][3];
        result[3][2] = this->value[2][3];
        return result;
    }

    template <typename T>
    mat34<T>& mat34<T>::operator=(const mat34& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
        return *this;
    }

    template <typename T>
    vec3<T>& mat34<T>::operator[](size_t i) {
        return this->value[i];
    }

    template <typename T>
    const vec3<T>& mat34<T>::operator[](size_t i) const {
        return this->value[i];
    }

    template <typename T>
    mat34<T>& mat34<T>::operator+=(T s) {
        this->value[0] += s;
        this->value[1] += s;
        this->value[2] += s;
        return *this;
    }

    template <typename T>
    mat34<T>& mat34<T>::operator+=(const mat34<T>& m) {
        this->value[0] += m[0];
        this->value[1] += m[1];
        this->value[2] += m[2];
    }

    template <typename T>
    mat34<T>& mat34<T>::operator-=(T s) {
        this->value[0] -= s;
        this->value[1] -= s;
        this->value[2] -= s;
        return *this;
    }

    template <typename T>
    mat34<T>& mat34<T>::operator-=(const mat34<T>& m) {
        this->value[0] -= m[0];
        this->value[1] -= m[1];
        this->value[1] -= m[1];
        return *this;
    }

    template <typename T>
    mat34<T>& mat34<T>::operator*=(T s) {
        this->value[0] *= s;
        this->value[1] *= s;
        this->value[2] *= s;
        return *this;
    }

    template <typename T>
    mat34<T>& mat34<T>::operator*=(const mat34<T>& m) {
        return *this = *this * m;
    }

    template <typename T>
    mat34<T>& mat34<T>::operator/=(T s) {
        this->value[0] /= s;
        this->value[1] /= s;
        this->value[2] /= s;
        return *this;
    }

    template <typename T>
    mat34<T>& mat34<T>::operator/=(const mat34<T>& m) {
        this->value[0] /= m[0];
        this->value[1] /= m[1];
        this->value[2] /= m[2];
        return *this;
    }

    template <typename T>
    mat34<T>& mat34<T>::operator++() {
        ++this->value[0];
        ++this->value[1];
        ++this->value[2];
        return *this;
    }

    template <typename T>
    mat34<T>& mat34<T>::operator--() {
        --this->value[0];
        --this->value[1];
        --this->value[2];
        return *this;
    }

    template <typename T>
    mat34<T> mat34<T>::operator++(int) {
        mat34<T> temp = *this;
        ++* this;
        return temp;
    }

    template <typename T>
    mat34<T> mat34<T>::operator--(int) {
        mat34<T> temp = *this;
        --* this;
        return temp;
    }

    template <typename T>
    mat34<T> operator+(const mat34<T>& m, T s) {
        return mat34<T>(m) += s;
    }

    template <typename T>
    mat34<T> operator+(T s, const mat34<T>& m) {
        return mat34<T>(s) += m;
    }

    template <typename T>
    mat34<T> operator+(const mat34<T>& m, const vec2<T>& v) {
        return mat34<T>(m[0] + v, m[1] + v, m[2] + v, m[3] + v);
    }

    template <typename T>
    mat34<T> operator+(const vec2<T>& v, const mat34<T>& m) {
        return mat34<T>(v + m[0], v + m[1], v + m[2]);
    }

    template <typename T>
    mat34<T> operator+(const mat34<T>& m1, const mat34<T>& m2) {
        return mat34<T>(m1) += m2;
    }

    template <typename T>
    mat34<T> operator-(const mat34<T>& m) {
        return mat34<T>(-m[0], -m[1], -m[2]);
    }

    template <typename T>
    mat34<T> operator-(const mat34<T>& m, T s) {
        return mat34<T>(m) -= s;
    }

    template <typename T>
    mat34<T> operator-(T s, const mat34<T>& m) {
        return mat34<T>(s) -= m;
    }

    template <typename T>
    mat34<T> operator-(const mat34<T>& m, const vec2<T>& v) {
        return mat34<T>(m[0] - v, m[1] - v, m[2] - v);
    }

    template <typename T>
    mat34<T> operator-(const vec2<T>& v, const mat34<T>& m) {
        return mat34<T>(v - m[0], v - m[1], v - m[2]);
    }

    template <typename T>
    mat34<T> operator*(const mat34<T>& m, T s) {
        return mat34<T>(m[0] * s, m[1] * s, m[2] * s);
    }

    template <typename T>
    mat34<T> operator*(T s, const mat34<T>& m) {
        return m * s;
    }

    // ����Ԫ
    template <typename T>
    vec4<T> operator*(const mat34<T>& m, const vec3<T>& v) {
        return vec4<T>(
            m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
            m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z,
            m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z,
            m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z);
    }

    // ����Ԫ
    template <typename T>
    vec3<T> operator*(const vec4<T>& v, const mat34<T>& m) {
        return vec3<T>(
            v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + v.w * m[0][3],
            v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + v.w * m[1][3],
            v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + v.w * m[2][3]);
    }

    // ����Ԫ
    template <typename T>
    mat4<T> operator*(const mat34<T>& m1, const mat43<T>& m2) {
        const T SrcA00 = m1[0][0];
        const T SrcA01 = m1[0][1];
        const T SrcA02 = m1[0][2];
        const T SrcA03 = m1[0][3];
        const T SrcA10 = m1[1][0];
        const T SrcA11 = m1[1][1];
        const T SrcA12 = m1[1][2];
        const T SrcA13 = m1[1][3];
        const T SrcA20 = m1[2][0];
        const T SrcA21 = m1[2][1];
        const T SrcA22 = m1[2][2];
        const T SrcA23 = m1[2][3];

        const T SrcB00 = m2[0][0];
        const T SrcB01 = m2[0][1];
        const T SrcB02 = m2[0][2];
        const T SrcB10 = m2[1][0];
        const T SrcB11 = m2[1][1];
        const T SrcB12 = m2[1][2];
        const T SrcB20 = m2[2][0];
        const T SrcB21 = m2[2][1];
        const T SrcB22 = m2[2][2];
        const T SrcB30 = m2[3][0];
        const T SrcB31 = m2[3][1];
        const T SrcB32 = m2[3][2];

        mat4<T> Result();
        Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02;
        Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02;
        Result[0][2] = SrcA02 * SrcB00 + SrcA12 * SrcB01 + SrcA22 * SrcB02;
        Result[0][3] = SrcA03 * SrcB00 + SrcA13 * SrcB01 + SrcA23 * SrcB02;
        Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12;
        Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12;
        Result[1][2] = SrcA02 * SrcB10 + SrcA12 * SrcB11 + SrcA22 * SrcB12;
        Result[1][3] = SrcA03 * SrcB10 + SrcA13 * SrcB11 + SrcA23 * SrcB12;
        Result[2][0] = SrcA00 * SrcB20 + SrcA10 * SrcB21 + SrcA20 * SrcB22;
        Result[2][1] = SrcA01 * SrcB20 + SrcA11 * SrcB21 + SrcA21 * SrcB22;
        Result[2][2] = SrcA02 * SrcB20 + SrcA12 * SrcB21 + SrcA22 * SrcB22;
        Result[2][3] = SrcA03 * SrcB20 + SrcA13 * SrcB21 + SrcA23 * SrcB22;
        Result[3][0] = SrcA00 * SrcB30 + SrcA10 * SrcB31 + SrcA20 * SrcB32;
        Result[3][1] = SrcA01 * SrcB30 + SrcA11 * SrcB31 + SrcA21 * SrcB32;
        Result[3][2] = SrcA02 * SrcB30 + SrcA12 * SrcB31 + SrcA22 * SrcB32;
        Result[3][3] = SrcA03 * SrcB30 + SrcA13 * SrcB31 + SrcA23 * SrcB32;
        return Result;
    }

    template <typename T>
    mat24<T> operator*(mat34<T> const& m1, mat23<T> const& m2) {
        return mat24<T>(
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2],
            m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2],
            m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2],
            m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2],
            m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2],
            m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2],
            m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2],
            m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2]);
    }

    template <typename T>
    mat34<T> operator*(const mat34<T>& m1, const mat3<T>& m2) {
        return mat24<T>(
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2],
            m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2],
            m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2],
            m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2],
            m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2],
            m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2],
            m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2],
            m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2],
            m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2],
            m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2],
            m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2],
            m1[0][3] * m2[2][0] + m1[1][3] * m2[2][1] + m1[2][3] * m2[2][2]);
    }

    template <typename T>
    mat34<T> operator/(const mat34<T>& m, T s) {
        return mat34<T>(m) /= s;
    }
}

#endif // !MAT34_H
