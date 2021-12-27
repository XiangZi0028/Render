#ifndef MAT44_H
#define MAT44_H

namespace math {
    template <typename T> struct vec4;
    template <typename T> struct mat24;
    template <typename T> struct mat34;

    template <typename T>
    struct mat4 {
    private:
        vec4<T> value[4];
    public:
        mat4();
        mat4(T s);
        mat4(T x0, T y0, T z0, T w0,
            T x1, T y1, T z1, T w1,
            T x2, T y2, T z2, T w2,
            T x3, T y3, T z3, T w3);
        mat4(const vec4<T>& v0, const vec4<T>& v1, 
            const vec4<T>& v2, const vec4<T>& v3);
        mat4(const mat4<T>& m);

        mat4<T> inverse();
        mat4<T> transpose();

        mat4<T>& operator=(const mat4& m);
        const vec4<T>& operator[](size_t i) const;
        vec4<T>& operator[](size_t i);
        mat4<T>& operator+=(T s);
        mat4<T>& operator+=(const mat4<T>& m);
        mat4<T>& operator-=(T s);
        mat4<T>& operator-=(const mat4<T>& m);
        mat4<T>& operator*=(T s);
        mat4<T>& operator*=(const mat4<T>& m);
        mat4<T>& operator/=(T s);
        mat4<T>& operator/=(const mat4<T>& m);
        mat4<T>& operator++();
        mat4<T>& operator--();
        mat4<T> operator++(int);
        mat4<T> operator--(int);
    };

    template <typename T>
    mat4<T>::mat4() {
        this->value[0] = vec4<T>(1, 0, 0, 0);
        this->value[1] = vec4<T>(0, 1, 0, 0);
        this->value[2] = vec4<T>(0, 0, 1, 0);
        this->value[3] = vec4<T>(0, 0, 0, 1);
    }

    template <typename T>
    mat4<T>::mat4(T s) {
        this->value[0] = vec4<T>(s, 0, 0, 0);
        this->value[1] = vec4<T>(0, s, 0, 0);
        this->value[2] = vec4<T>(0, 0, s, 0);
        this->value[3] = vec4<T>(0, 0, 0, s);
    }

    template <typename T>
    mat4<T>::mat4(
        T x0, T y0, T z0, T w0,
        T x1, T y1, T z1, T w1,
        T x2, T y2, T z2, T w2,
        T x3, T y3, T z3, T w3) {
        this->value[0] = vec4<T>(x0, y0, z0, w0);
        this->value[1] = vec4<T>(x1, y1, z1, w1);
        this->value[2] = vec4<T>(x2, y2, z2, w2);
        this->value[3] = vec4<T>(x3, y3, z3, w3);
    }

    template <typename T>
    mat4<T>::mat4(const vec4<T>& v0, const vec4<T>& v1,
        const vec4<T>& v2, const vec4<T>& v3) {
        this->value[0] = v0;
        this->value[1] = v1;
        this->value[2] = v2;
        this->value[3] = v3;
    }

    template <typename T>
    mat4<T>::mat4(const mat4<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
        this->value[3] = m[3];
    }

    template <typename T>
    mat4<T> mat4<T>::inverse() {
        // Calculate all mat2 determinants
        T SubFactor00 = this->value[2][2] * this->value[3][3] - this->value[3][2] * this->value[2][3];
        T SubFactor01 = this->value[2][1] * this->value[3][3] - this->value[3][1] * this->value[2][3];
        T SubFactor02 = this->value[2][1] * this->value[3][2] - this->value[3][1] * this->value[2][2];
        T SubFactor03 = this->value[2][0] * this->value[3][3] - this->value[3][0] * this->value[2][3];
        T SubFactor04 = this->value[2][0] * this->value[3][2] - this->value[3][0] * this->value[2][2];
        T SubFactor05 = this->value[2][0] * this->value[3][1] - this->value[3][0] * this->value[2][1];
        T SubFactor06 = this->value[1][2] * this->value[3][3] - this->value[3][2] * this->value[1][3];
        T SubFactor07 = this->value[1][1] * this->value[3][3] - this->value[3][1] * this->value[1][3];
        T SubFactor08 = this->value[1][1] * this->value[3][2] - this->value[3][1] * this->value[1][2];
        T SubFactor09 = this->value[1][0] * this->value[3][3] - this->value[3][0] * this->value[1][3];
        T SubFactor10 = this->value[1][0] * this->value[3][2] - this->value[3][0] * this->value[1][2];
        T SubFactor11 = this->value[1][1] * this->value[3][3] - this->value[3][1] * this->value[1][3];
        T SubFactor12 = this->value[1][0] * this->value[3][1] - this->value[3][0] * this->value[1][1];
        T SubFactor13 = this->value[1][2] * this->value[2][3] - this->value[2][2] * this->value[1][3];
        T SubFactor14 = this->value[1][1] * this->value[2][3] - this->value[2][1] * this->value[1][3];
        T SubFactor15 = this->value[1][1] * this->value[2][2] - this->value[2][1] * this->value[1][2];
        T SubFactor16 = this->value[1][0] * this->value[2][3] - this->value[2][0] * this->value[1][3];
        T SubFactor17 = this->value[1][0] * this->value[2][2] - this->value[2][0] * this->value[1][2];
        T SubFactor18 = this->value[1][0] * this->value[2][1] - this->value[2][0] * this->value[1][1];

        mat4<T> Inverse(
            +this->value[1][1] * SubFactor00 - this->value[1][2] * SubFactor01 + this->value[1][3] * SubFactor02,
            -this->value[1][0] * SubFactor00 + this->value[1][2] * SubFactor03 - this->value[1][3] * SubFactor04,
            +this->value[1][0] * SubFactor01 - this->value[1][1] * SubFactor03 + this->value[1][3] * SubFactor05,
            -this->value[1][0] * SubFactor02 + this->value[1][1] * SubFactor04 - this->value[1][2] * SubFactor05,

            -this->value[0][1] * SubFactor00 + this->value[0][2] * SubFactor01 - this->value[0][3] * SubFactor02,
            +this->value[0][0] * SubFactor00 - this->value[0][2] * SubFactor03 + this->value[0][3] * SubFactor04,
            -this->value[0][0] * SubFactor01 + this->value[0][1] * SubFactor03 - this->value[0][3] * SubFactor05,
            +this->value[0][0] * SubFactor02 - this->value[0][1] * SubFactor04 + this->value[0][2] * SubFactor05,

            +this->value[0][1] * SubFactor06 - this->value[0][2] * SubFactor07 + this->value[0][3] * SubFactor08,
            -this->value[0][0] * SubFactor06 + this->value[0][2] * SubFactor09 - this->value[0][3] * SubFactor10,
            +this->value[0][0] * SubFactor11 - this->value[0][1] * SubFactor09 + this->value[0][3] * SubFactor12,
            -this->value[0][0] * SubFactor08 + this->value[0][1] * SubFactor10 - this->value[0][2] * SubFactor12,

            -this->value[0][1] * SubFactor13 + this->value[0][2] * SubFactor14 - this->value[0][3] * SubFactor15,
            +this->value[0][0] * SubFactor13 - this->value[0][2] * SubFactor16 + this->value[0][3] * SubFactor17,
            -this->value[0][0] * SubFactor14 + this->value[0][1] * SubFactor16 - this->value[0][3] * SubFactor18,
            +this->value[0][0] * SubFactor15 - this->value[0][1] * SubFactor17 + this->value[0][2] * SubFactor18);

        T Determinant =
            + this->value[0][0] * Inverse[0][0]
            + this->value[0][1] * Inverse[1][0]
            + this->value[0][2] * Inverse[2][0]
            + this->value[0][3] * Inverse[3][0];

        Inverse /= Determinant;
        return Inverse;
    }

    template <typename T>
    mat4<T> mat4<T>::transpose() {
        mat4<T> result;
        result[0][0] = this->value[0][0];
        result[0][1] = this->value[1][0];
        result[0][2] = this->value[2][0];
        result[0][3] = this->value[3][0];

        result[1][0] = this->value[0][1];
        result[1][1] = this->value[1][1];
        result[1][2] = this->value[2][1];
        result[1][3] = this->value[3][1];

        result[2][0] = this->value[0][2];
        result[2][1] = this->value[1][2];
        result[2][2] = this->value[2][2];
        result[2][3] = this->value[3][2];

        result[3][0] = this->value[0][3];
        result[3][1] = this->value[1][3];
        result[3][2] = this->value[2][3];
        result[3][3] = this->value[3][3];
        return result;
    }

    template <typename T>
    mat4<T>& mat4<T>::operator=(const mat4<T>& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
        this->value[3] = m[3];
        return *this;
    }

    template <typename T>
    const vec4<T>& mat4<T>::operator[](size_t i) const {
        return this->value[i];
    }

    template <typename T>
    vec4<T>& mat4<T>::operator[](size_t i){
        return this->value[i];
    }

    template <typename T>
    mat4<T>& mat4<T>::operator+=(T s) {
        this->value[0] += s;
        this->value[1] += s;
        this->value[2] += s;
        this->value[3] += s;
        return *this;
    }

    template <typename T>
    mat4<T>& mat4<T>::operator+=(const mat4<T>& m) {
        this->value[0] += m[0];
        this->value[1] += m[1];
        this->value[2] += m[2];
        this->value[3] += m[3];
    }

    template <typename T>
    mat4<T>& mat4<T>::operator-=(T s) {
        this->value[0] -= s;
        this->value[1] -= s;
        this->value[2] -= s;
        this->value[3] -= s;
        return *this;
    }

    template <typename T>
    mat4<T>& mat4<T>::operator-=(const mat4<T>& m) {
        this->value[0] -= m[0];
        this->value[1] -= m[1];
        this->value[1] -= m[1];
        this->value[1] -= m[1];
        return *this;
    }

    template <typename T>
    mat4<T>& mat4<T>::operator*=(T s) {
        this->value[0] *= s;
        this->value[1] *= s;
        this->value[2] *= s;
        this->value[3] *= s;
        return *this;
    }

    template <typename T>
    mat4<T>& mat4<T>::operator*=(const mat4<T>& m) {
        return *this = *this * m;
    }

    template <typename T>
    mat4<T>& mat4<T>::operator/=(T s) {
        this->value[0] /= s;
        this->value[1] /= s;
        this->value[2] /= s;
        this->value[3] /= s;
        return *this;
    }

    template <typename T>
    mat4<T>& mat4<T>::operator/=(const mat4<T>& m) {
        this->value[0] /= m[0];
        this->value[1] /= m[1];
        this->value[2] /= m[2];
        this->value[3] /= m[3];
        return *this;
    }

    template <typename T>
    mat4<T>& mat4<T>::operator++() {
        ++this->value[0];
        ++this->value[1];
        ++this->value[2];
        ++this->value[3];
        return *this;
    }

    template <typename T>
    mat4<T>& mat4<T>::operator--() {
        --this->value[0];
        --this->value[1];
        --this->value[2];
        --this->value[3];
        return *this;
    }

    template <typename T>
    mat4<T> mat4<T>::operator++(int) {
        mat4<T> temp = *this;
        ++* this;
        return temp;
    }

    template <typename T>
    mat4<T> mat4<T>::operator--(int) {
        mat4<T> temp = *this;
        --* this;
        return temp;
    }

    template <typename T>
    mat4<T> operator+(const mat4<T>& m, T s) {
        return mat4<T>(m) += s;
    }

    template <typename T>
    mat4<T> operator+(T s, const mat4<T>& m) {
        return mat4<T>(s) += m;
    }

    template <typename T>
    mat4<T> operator+(const mat4<T>& m, const vec2<T>& v) {
        return mat4<T>(m[0] + v, m[1] + v, m[2] + v, m[3] + v);
    }

    template <typename T>
    mat4<T> operator+(const vec2<T>& v, const mat4<T>& m) {
        return mat4<T>(v + m[0], v + m[1], v + m[2], v + m[3]);
    }

    template <typename T>
    mat4<T> operator+(const mat4<T>& m1, const mat4<T>& m2) {
        return mat4<T>(m1) += m2;
    }

    template <typename T>
    mat4<T> operator-(const mat4<T>& m) {
        return mat4<T>(-m[0], -m[1], -m[2], -m[3]);
    }

    template <typename T>
    mat4<T> operator-(const mat4<T>& m, T s) {
        return mat4<T>(m) -= s;
    }

    template <typename T>
    mat4<T> operator-(T s, const mat4<T>& m) {
        return mat4<T>(s) -= m;
    }

    template <typename T>
    mat4<T> operator-(const mat4<T>& m, const vec2<T>& v) {
        return mat4<T>(m[0] - v, m[1] - v, m[2] - v, m[3] - v);
    }

    template <typename T>
    mat4<T> operator-(const vec2<T>& v, const mat4<T>& m) {
        return mat4<T>(v - m[0], v - m[1], v - m[2], v - m[3]);
    }

    template <typename T>
    mat4<T> operator*(const mat4<T>& m, T s) {
        return mat4<T>(m[0] * s, m[1] * s, m[2] * s, m[3] * s);
    }

    template <typename T>
    mat4<T> operator*(T s, const mat4<T>& m) {
        return m * s;
    }

    // ����Ԫ
    template <typename T>
    vec4<T> operator*(const mat4<T>& m, const vec4<T>& v) {
        return vec4<T>(
            m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
            m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w,
            m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w,
            m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3] * v.w);
    }

    // ����Ԫ
    template <typename T>
    vec4<T> operator*(const vec4<T>& v, const mat4<T>& m) {
        return vec4<T>(
            m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
            m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
            m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
            m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w);
    }

    // ����Ԫ
    template <typename T>
    mat4<T> operator*(const mat4<T>& m1, const mat4<T>& m2) {
        vec4<T> const SrcA0 = m1[0];
        vec4<T> const SrcA1 = m1[1];
        vec4<T> const SrcA2 = m1[2];
        vec4<T> const SrcA3 = m1[3];

        vec4<T> const SrcB0 = m2[0];
        vec4<T> const SrcB1 = m2[1];
        vec4<T> const SrcB2 = m2[2];
        vec4<T> const SrcB3 = m2[3];

        auto f = SrcB0[3];

        mat4<T> Result;
        Result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3];
        Result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3];
        Result[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3];
        Result[3] = SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3];
        return Result;
    }

    template <typename T>
    mat34<T> operator*(mat4<T> const& m1, mat34<T> const& m2) {
        return mat34<T>(
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
            m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
            m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] + m1[3][2] * m2[0][3],
            m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2] + m1[3][3] * m2[0][3],
            m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
            m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
            m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][2] * m2[1][3],
            m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2] + m1[3][3] * m2[1][3],
            m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] + m1[3][0] * m2[2][3],
            m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] + m1[3][1] * m2[2][3],
            m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2] + m1[3][2] * m2[2][3],
            m1[0][3] * m2[2][0] + m1[1][3] * m2[2][1] + m1[2][3] * m2[2][2] + m1[3][3] * m2[2][3]);
    }

    template <typename T>
    mat24<T> operator*(const mat4<T>& m1, const mat24<T>& m2) {
        return mat24<T>(
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
            m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
            m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] + m1[3][2] * m2[0][3],
            m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2] + m1[3][3] * m2[0][3],
            m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
            m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
            m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][2] * m2[1][3],
            m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2] + m1[3][3] * m2[1][3]);
    }

    template <typename T>
    mat4<T> operator/(const mat4<T>& m, T s) {
        return mat4<T>(m) /= s;
    }

    template <typename T>
    mat4<T> operator/(const mat4<T>& m1, const mat4<T>& m2) {
        return m1 * m2.inverse();
    }
}

#endif // !MAT44_H
