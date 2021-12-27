#ifndef MAT32_H
#define MAT32_H

#include <stdint.h>

namespace math {
    template <typename T> struct vec2;
    template <typename T> struct vec3;
    template <typename T> struct mat2;
    template <typename T> struct mat32;
    template <typename T> struct mat3;
    template <typename T> struct mat34;
    template <typename T> struct mat42;
    template <typename T> struct mat43;
    template <typename T> struct mat4;

    template <typename T>
    struct mat32 {
    private:
        vec2<T> value[3];
    public:
        mat32();
        mat32(T s);
        mat32(T x0, T y0, T x1, T y1, T x2, T y2);
        mat32(const vec2<T>& v0, const vec2<T>& v1,
            const vec2<T>& v2);
        mat32(const mat32<T>& m);
        mat32(const mat3<T>& m);
        mat32(const mat34<T>& m);
        mat32(const mat42<T>& m);
        mat32(const mat43<T>& m);
        mat32(const mat4<T>& m);

        mat23<T> transpose();

        mat32<T>& operator=(const mat32& m);
        const vec3<T>& operator[](size_t i) const;
        vec3<T>& operator[](size_t i);
        mat32<T>& operator+=(T s);
        mat32<T>& operator+=(const mat32<T>& m);
        mat32<T>& operator-=(T s);
        mat32<T>& operator-=(const mat32<T>& m);
        mat32<T>& operator*=(T s);
        mat32<T>& operator*=(const mat32<T>& m);
        mat32<T>& operator/=(T s);
        mat32<T>& operator/=(const mat32<T>& m);
        mat32<T>& operator++();
        mat32<T>& operator--();
        mat32<T> operator++(int);
        mat32<T> operator--(int);
    };

    template <typename T>
    mat32<T>::mat32() {
        this->value[0] = vec2<T>(1, 0);
        this->value[1] = vec2<T>(0, 1);
        this->value[2] = vec2<T>(0, 0);
    }

    template <typename T>
    mat32<T>::mat32(T s) {
        this->value[0] = vec2<T>(s, 0);
        this->value[1] = vec2<T>(0, s);
        this->value[2] = vec2<T>(0, 0);
    }

    template <typename T>
    mat32<T>::mat32(T x0, T y0, T x1, T y1, T x2, T y2) {
        this->value[0] = vec2<T>(x0, y0);
        this->value[1] = vec2<T>(x1, y1);
        this->value[2] = vec2<T>(x2, y2);
    }

    template <typename T>
    mat32<T>::mat32(const vec2<T>& v0, const vec2<T>& v1,
        const vec2<T>& v2) {
        this->value[0] = v0;
        this->value[1] = v1;
        this->value[2] = v2;
    }

    template <typename T>
    mat32<T>::mat32(const mat32<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
    }

    template <typename T>
    mat32<T>::mat32(const mat3<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
    }

    template <typename T>
    mat32<T>::mat32(const mat34<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
    }

    template <typename T>
    mat32<T>::mat32(const mat42<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
    }

    template <typename T>
    mat32<T>::mat32(const mat43<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
    }

    template <typename T>
    mat32<T>::mat32(const mat4<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
    }

    template <typename T>
    mat23<T> mat32<T>::transpose() {
        mat23<T> result;
        result[0][0] = this->value[0][0];
        result[0][1] = this->value[1][0];
        result[0][2] = this->value[2][0];

        result[1][0] = this->value[0][1];
        result[1][1] = this->value[1][1];
        result[1][2] = this->value[2][1];
        return result;
    }

    template <typename T>
    mat32<T>& mat32<T>::operator=(const mat32& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
        return *this;
    }

    template <typename T>
    vec3<T>& mat32<T>::operator[](size_t i) {
        return this->value[i];
    }

    template <typename T>
    const vec3<T>& mat32<T>::operator[](size_t i) const{
        return this->value[i];
    }

    template <typename T>
    mat32<T>& mat32<T>::operator+=(T s) {
        this->value[0] += s;
        this->value[1] += s;
        this->value[2] += s;
        return *this;
    }

    template <typename T>
    mat32<T>& mat32<T>::operator+=(const mat32<T>& m) {
        this->value[0] += m[0];
        this->value[1] += m[1];
        this->value[2] += m[2];
    }

    template <typename T>
    mat32<T>& mat32<T>::operator-=(T s) {
        this->value[0] -= s;
        this->value[1] -= s;
        this->value[2] -= s;
        return *this;
    }

    template <typename T>
    mat32<T>& mat32<T>::operator-=(const mat32<T>& m) {
        this->value[0] -= m[0];
        this->value[1] -= m[1];
        this->value[1] -= m[1];
        return *this;
    }

    template <typename T>
    mat32<T>& mat32<T>::operator*=(T s) {
        this->value[0] *= s;
        this->value[1] *= s;
        this->value[2] *= s;
        return *this;
    }

    template <typename T>
    mat32<T>& mat32<T>::operator*=(const mat32<T>& m) {
        return *this = *this * m;
    }

    template <typename T>
    mat32<T>& mat32<T>::operator/=(T s) {
        this->value[0] /= s;
        this->value[1] /= s;
        this->value[2] /= s;
        return *this;
    }

    template <typename T>
    mat32<T>& mat32<T>::operator/=(const mat32<T>& m) {
        this->value[0] /= m[0];
        this->value[1] /= m[1];
        this->value[2] /= m[2];
        return *this;
    }

    template <typename T>
    mat32<T>& mat32<T>::operator++() {
        ++this->value[0];
        ++this->value[1];
        ++this->value[2];
        return *this;
    }

    template <typename T>
    mat32<T>& mat32<T>::operator--() {
        --this->value[0];
        --this->value[1];
        --this->value[2];
        return *this;
    }

    template <typename T>
    mat32<T> mat32<T>::operator++(int) {
        mat32<T> temp = *this;
        ++* this;
        return temp;
    }

    template <typename T>
    mat32<T> mat32<T>::operator--(int) {
        mat32<T> temp = *this;
        --* this;
        return temp;
    }

    template <typename T>
    mat32<T> operator+(const mat32<T>& m, T s) {
        return mat32<T>(m) += s;
    }

    template <typename T>
    mat32<T> operator+(T s, const mat32<T>& m) {
        return mat32<T>(s) += m;
    }

    template <typename T>
    mat32<T> operator+(const mat32<T>& m, const vec2<T>& v) {
        return mat32<T>(m[0] + v, m[1] + v, m[2] + v, m[3] + v);
    }

    template <typename T>
    mat32<T> operator+(const vec2<T>& v, const mat32<T>& m) {
        return mat32<T>(v + m[0], v + m[1], v + m[2]);
    }

    template <typename T>
    mat32<T> operator+(const mat32<T>& m1, const mat32<T>& m2) {
        return mat32<T>(m1) += m2;
    }

    template <typename T>
    mat32<T> operator-(const mat32<T>& m) {
        return mat32<T>(-m[0], -m[1], -m[2]);
    }

    template <typename T>
    mat32<T> operator-(const mat32<T>& m, T s) {
        return mat32<T>(m) -= s;
    }

    template <typename T>
    mat32<T> operator-(T s, const mat32<T>& m) {
        return mat32<T>(s) -= m;
    }

    template <typename T>
    mat32<T> operator-(const mat32<T>& m, const vec2<T>& v) {
        return mat32<T>(m[0] - v, m[1] - v, m[2] - v);
    }

    template <typename T>
    mat32<T> operator-(const vec2<T>& v, const mat32<T>& m) {
        return mat32<T>(v - m[0], v - m[1], v - m[2]);
    }

    template <typename T>
    mat32<T> operator*(const mat32<T>& m, T s) {
        return mat32<T>(m[0] * s, m[1] * s, m[2] * s);
    }

    template <typename T>
    mat32<T> operator*(T s, const mat32<T>& m) {
        return m * s;
    }

    // ����Ԫ
    template <typename T>
    vec2<T> operator*(const mat32<T>& m, const vec3<T>& v) {
        return vec2<T>(
            m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
            m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z);
    }

    // ����Ԫ
    template <typename T>
    vec3<T> operator*(const vec3<T>& v, const mat32<T>& m) {
        return vec3<T>(
            v.x * m[0][0] + v.y * m[0][1],
            v.x * m[1][0] + v.y * m[1][1],
            v.x * m[2][0] + v.y * m[2][1]);
    }

    // ����Ԫ
    template <typename T>
    mat32<T> operator*(const mat32<T>& m1, const mat23<T>& m2) {
        const T SrcA00 = m1[0][0];
        const T SrcA01 = m1[0][1];
        const T SrcA10 = m1[1][0];
        const T SrcA11 = m1[1][1];
        const T SrcA20 = m1[2][0];
        const T SrcA21 = m1[2][1];

        const T SrcB00 = m2[0][0];
        const T SrcB01 = m2[0][1];
        const T SrcB02 = m2[0][2];
        const T SrcB10 = m2[1][0];
        const T SrcB11 = m2[1][1];
        const T SrcB12 = m2[1][2];

        mat2<T> Result();
        Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02;
        Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02;
        Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12;
        Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12;
        return Result;
    }

    template <typename T>
    mat32<T> operator*(mat32<T> const& m1, mat3<T> const& m2) {
        return mat32<T>(
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2],
            m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2],
            m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2],
            m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2],
            m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2],
            m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2]);
    }

    template <typename T>
    mat24<T> operator*(const mat32<T>& m1, const mat43<T>& m2) {
        return mat24<T>(
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2],
            m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2],
            m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2],
            m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2],
            m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2],
            m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2],
            m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1] + m1[2][0] * m2[3][2],
            m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1] + m1[2][1] * m2[3][2]);
    }

    template <typename T>
    mat32<T> operator/(const mat32<T>& m, T s) {
        return mat32<T>(m) /= s;
    }
}

#endif // !MAT32_H
