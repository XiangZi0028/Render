#ifndef MAT33_H
#define MAT33_H

#include <stdint.h>

namespace math {
    template <typename T> struct vec4;
    template <typename T> struct mat24;
    template <typename T> struct mat34;
    template <typename T> struct mat43;
    template <typename T> struct mat4;

    template <typename T>
    struct mat3 {
    private:
        vec3<T> value[3];
    public:
        mat3();
        mat3(T s);
        mat3(T x0, T y0, T z0,
            T x1, T y1, T z1,
            T x2, T y2, T z2);
        mat3(const vec3<T>& v0, const vec3<T>& v1,
            const vec3<T>& v2);
        mat3(const mat3<T>& m);
        mat3(const mat34<T>& m);
        mat3(const mat43<T>& m);
        mat3(const mat4<T>& m);

        mat3<T> inverse();
        mat3<T> transpose();

        mat3<T>& operator=(const mat3& m);
        vec3<T>& operator[](size_t i);
        const vec3<T>& operator[](size_t i) const;
        mat3<T>& operator+=(T s);
        mat3<T>& operator+=(const mat3<T>& m);
        mat3<T>& operator-=(T s);
        mat3<T>& operator-=(const mat3<T>& m);
        mat3<T>& operator*=(T s);
        mat3<T>& operator*=(const mat3<T>& m);
        mat3<T>& operator/=(T s);
        mat3<T>& operator/=(const mat3<T>& m);
        mat3<T>& operator++();
        mat3<T>& operator--();
        mat3<T> operator++(int);
        mat3<T> operator--(int);
    };

    template <typename T>
    mat3<T>::mat3() {
        this->value[0] = vec3<T>(1, 0, 0);
        this->value[1] = vec3<T>(0, 1, 0);
        this->value[2] = vec3<T>(0, 0, 1);
    }

    template <typename T>
    mat3<T>::mat3(T s) {
        this->value[0] = vec3<T>(s, 0, 0);
        this->value[1] = vec3<T>(0, s, 0);
        this->value[2] = vec3<T>(0, 0, s);
    }

    template <typename T>
    mat3<T>::mat3(
        T x0, T y0, T z0,
        T x1, T y1, T z1,
        T x2, T y2, T z2) {
        this->value[0] = vec3<T>(x0, y0, z0);
        this->value[1] = vec3<T>(x1, y1, z1);
        this->value[2] = vec3<T>(x2, y2, z2);
    }

    template <typename T>
    mat3<T>::mat3(const vec3<T>& v0, const vec3<T>& v1,
        const vec3<T>& v2) {
        this->value[0] = v0;
        this->value[1] = v1;
        this->value[2] = v2;
    }

    template <typename T>
    mat3<T>::mat3(const mat3<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
    }

    template <typename T>
    mat3<T>::mat3(const mat34<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
    }

    template <typename T>
    mat3<T>::mat3(const mat43<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
    }

    template <typename T>
    mat3<T>::mat3(const mat4<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
    }

    template <typename T>
    mat3<T> mat3<T>::inverse() {
        T S00 = value[0][0];
        T S01 = value[0][1];
        T S02 = value[0][2];

        T S10 = value[1][0];
        T S11 = value[1][1];
        T S12 = value[1][2];

        T S20 = value[2][0];
        T S21 = value[2][1];
        T S22 = value[2][2];

        mat3<T> Inverse(
            S11 * S22 - S21 * S12,
            S12 * S20 - S22 * S10,
            S10 * S21 - S20 * S11,
            S02 * S21 - S01 * S22,
            S00 * S22 - S02 * S20,
            S01 * S20 - S00 * S21,
            S12 * S01 - S11 * S02,
            S10 * S02 - S12 * S00,
            S11 * S00 - S10 * S01);

        T Determinant = S00 * (S11 * S22 - S21 * S12)
            - S10 * (S01 * S22 - S21 * S02)
            + S20 * (S01 * S12 - S11 * S02);

        Inverse /= Determinant;
        return Inverse;
    }

    template <typename T>
    mat3<T> mat3<T>::transpose() {
        mat3<T> result;
        result[0][0] = this->value[0][0];
        result[0][1] = this->value[1][0];
        result[0][2] = this->value[2][0];

        result[1][0] = this->value[0][1];
        result[1][1] = this->value[1][1];
        result[1][2] = this->value[2][1];

        result[2][0] = this->value[0][2];
        result[2][1] = this->value[1][2];
        result[2][2] = this->value[2][2];
        return result;
    }

    template <typename T>
    mat3<T>& mat3<T>::operator=(const mat3& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
        return *this;
    }

    template <typename T>
    vec3<T>& mat3<T>::operator[](size_t i) {
        return this->value[i];
    }

    template <typename T>
    const vec3<T>& mat3<T>::operator[](size_t i) const {
        return this->value[i];
    }

    template <typename T>
    mat3<T>& mat3<T>::operator+=(T s) {
        this->value[0] += s;
        this->value[1] += s;
        this->value[2] += s;
        return *this;
    }

    template <typename T>
    mat3<T>& mat3<T>::operator+=(const mat3<T>& m) {
        this->value[0] += m[0];
        this->value[1] += m[1];
        this->value[2] += m[2];
    }

    template <typename T>
    mat3<T>& mat3<T>::operator-=(T s) {
        this->value[0] -= s;
        this->value[1] -= s;
        this->value[2] -= s;
        return *this;
    }

    template <typename T>
    mat3<T>& mat3<T>::operator-=(const mat3<T>& m) {
        this->value[0] -= m[0];
        this->value[1] -= m[1];
        this->value[1] -= m[1];
        return *this;
    }

    template <typename T>
    mat3<T>& mat3<T>::operator*=(T s) {
        this->value[0] *= s;
        this->value[1] *= s;
        this->value[2] *= s;
        return *this;
    }

    template <typename T>
    mat3<T>& mat3<T>::operator*=(const mat3<T>& m) {
        return *this = *this * m;
    }

    template <typename T>
    mat3<T>& mat3<T>::operator/=(T s) {
        this->value[0] /= s;
        this->value[1] /= s;
        this->value[2] /= s;
        return *this;
    }

    template <typename T>
    mat3<T>& mat3<T>::operator/=(const mat3<T>& m) {
        this->value[0] /= m[0];
        this->value[1] /= m[1];
        this->value[2] /= m[2];
        return *this;
    }

    template <typename T>
    mat3<T>& mat3<T>::operator++() {
        ++this->value[0];
        ++this->value[1];
        ++this->value[2];
        return *this;
    }

    template <typename T>
    mat3<T>& mat3<T>::operator--() {
        --this->value[0];
        --this->value[1];
        --this->value[2];
        return *this;
    }

    template <typename T>
    mat3<T> mat3<T>::operator++(int) {
        mat3<T> temp = *this;
        ++* this;
        return temp;
    }

    template <typename T>
    mat3<T> mat3<T>::operator--(int) {
        mat3<T> temp = *this;
        --* this;
        return temp;
    }

    template <typename T>
    mat3<T> operator+(const mat3<T>& m, T s) {
        return mat3<T>(m) += s;
    }

    template <typename T>
    mat3<T> operator+(T s, const mat3<T>& m) {
        return mat3<T>(s) += m;
    }

    template <typename T>
    mat3<T> operator+(const mat3<T>& m, const vec3<T>& v) {
        return mat3<T>(m[0] + v, m[1] + v, m[2] + v, m[3] + v);
    }

    template <typename T>
    mat3<T> operator+(const vec3<T>& v, const mat3<T>& m) {
        return mat3<T>(v + m[0], v + m[1], v + m[2]);
    }

    template <typename T>
    mat3<T> operator+(const mat3<T>& m1, const mat3<T>& m2) {
        return mat3<T>(m1) += m2;
    }

    template <typename T>
    mat3<T> operator-(const mat3<T>& m) {
        return mat3<T>(-m[0], -m[1], -m[2]);
    }

    template <typename T>
    mat3<T> operator-(const mat3<T>& m, T s) {
        return mat3<T>(m) -= s;
    }

    template <typename T>
    mat3<T> operator-(T s, const mat3<T>& m) {
        return mat3<T>(s) -= m;
    }

    template <typename T>
    mat3<T> operator-(const mat3<T>& m, const vec3<T>& v) {
        return mat3<T>(m[0] - v, m[1] - v, m[2] - v);
    }

    template <typename T>
    mat3<T> operator-(const vec3<T>& v, const mat3<T>& m) {
        return mat3<T>(v - m[0], v - m[1], v - m[2]);
    }

    template <typename T>
    mat3<T> operator*(const mat3<T>& m, T s) {
        return mat3<T>(m[0] * s, m[1] * s, m[2] * s);
    }

    template <typename T>
    mat3<T> operator*(T s, const mat3<T>& m) {
        return m * s;
    }

    // ����Ԫ
    template <typename T>
    vec3<T> operator*(const mat3<T>& m, const vec3<T>& v) {
        return vec3<T>(
            m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
            m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z,
            m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z);
    }

    // ����Ԫ
    template <typename T>
    vec3<T> operator*(const vec3<T>& v, const mat3<T>& m) {
        return vec3<T>(
            m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
            m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
            m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z);
    }

    // ����Ԫ
    template <typename T>
    mat3<T> operator*(const mat3<T>& m1, const mat3<T>& m2) {
        T const SrcA00 = m1[0][0];
        T const SrcA01 = m1[0][1];
        T const SrcA02 = m1[0][2];
        T const SrcA10 = m1[1][0];
        T const SrcA11 = m1[1][1];
        T const SrcA12 = m1[1][2];
        T const SrcA20 = m1[2][0];
        T const SrcA21 = m1[2][1];
        T const SrcA22 = m1[2][2];

        T const SrcB00 = m2[0][0];
        T const SrcB01 = m2[0][1];
        T const SrcB02 = m2[0][2];
        T const SrcB10 = m2[1][0];
        T const SrcB11 = m2[1][1];
        T const SrcB12 = m2[1][2];
        T const SrcB20 = m2[2][0];
        T const SrcB21 = m2[2][1];
        T const SrcB22 = m2[2][2];

        mat3<T> Result();
        Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02;
        Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02;
        Result[0][2] = SrcA02 * SrcB00 + SrcA12 * SrcB01 + SrcA22 * SrcB02;
        Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12;
        Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12;
        Result[1][2] = SrcA02 * SrcB10 + SrcA12 * SrcB11 + SrcA22 * SrcB12;
        Result[2][0] = SrcA00 * SrcB20 + SrcA10 * SrcB21 + SrcA20 * SrcB22;
        Result[2][1] = SrcA01 * SrcB20 + SrcA11 * SrcB21 + SrcA21 * SrcB22;
        Result[2][2] = SrcA02 * SrcB20 + SrcA12 * SrcB21 + SrcA22 * SrcB22;
        return Result;
    }

    template <typename T>
    mat43<T> operator*(mat3<T> const& m1, mat43<T> const& m2) {
        return mat43<T>(
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2],
            m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2],
            m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2],
            m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2],
            m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2],
            m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2],
            m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2],
            m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2],
            m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2],
            m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1] + m1[2][0] * m2[3][2],
            m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1] + m1[2][1] * m2[3][2],
            m1[0][2] * m2[3][0] + m1[1][2] * m2[3][1] + m1[2][2] * m2[3][2]);
    }

    template <typename T>
    mat23<T> operator*(const mat3<T>& m1, const mat23<T>& m2) {
        return mat23<T>(
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2],
            m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2],
            m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2],
            m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2],
            m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2],
            m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2]);
    }

    template <typename T>
    mat3<T> operator/(const mat3<T>& m, T s) {
        return mat3<T>(m) /= s;
    }

    template <typename T>
    mat3<T> operator/(const mat3<T>& m1, const mat3<T>& m2) {
        return m1 * m2.inverse();
    }
}

#endif // !MAT33_H
