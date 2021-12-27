#pragma once

namespace math {
    template <typename T>
    struct vec3;
    template <typename T>
    struct vec4;

    template <typename T>
    struct vec2 {
        union
        {
            struct { T x, y; };
            struct { T r, g; };
            struct { T s, t; };
        };

        vec2();
        vec2(T x);
        vec2(T x, T y);
        vec2(const vec2<T>& v);
        vec2(const vec3<T>& v);
        vec2(const vec4<T>& v);

        vec2<T>& operator=(const vec2<T>& v);
        T& operator[](size_t i) ;
        const T& operator[](size_t i) const;
        vec2<T>& operator+=(const vec2<T>& v);
        vec2<T>& operator+=(T x);
        vec2<T>& operator-=(const vec2<T>& v);
        vec2<T>& operator-=(T x);
        vec2<T>& operator*=(const vec2<T>& v);
        vec2<T>& operator*=(T x);
        vec2<T>& operator/=(const vec2<T>& v);
        vec2<T>& operator/=(T x);
        vec2<T>& operator++();
        vec2<T>& operator--();
        vec2<T> operator++(int);
        vec2<T> operator--(int);
    };

    template <typename T>
    vec2<T>::vec2()
        : x(0), y(0)
    {}

    template <typename T>
    vec2<T>::vec2(T x)
        : x(x), y(x)
    {}

    template <typename T>
    vec2<T>::vec2(T x, T y)
        : x(x), y(y)
    {}

    template <typename T>
    vec2<T>::vec2(const vec2<T>& v)
        : x(v.x), y(v.y)
    {}

    template <typename T>
    vec2<T>::vec2(const vec3<T>& v)
        : x(v.x), y(v.y)
    {}

    template <typename T>
    vec2<T>::vec2(const vec4<T>& v)
        : x(v.x), y(v.y)
    {}

    template <typename T>
    vec2<T>& vec2<T>::operator=(const vec2<T>& v) {
        this->x = v.x;
        this->y = v.y;
        return *this;
    }

    template <typename T>
    T& vec2<T>::operator[](size_t i) {
        return (&x)[i];
    }

    template <typename T>
    const T& vec2<T>::operator[](size_t i) const {
        return (&x)[i];
    }

    template <typename T>
    vec2<T>& vec2<T>::operator+=(const vec2<T>& v) {
        this->x += v.x;
        this->y += v.y;
        return *this;
    }

    template <typename T>
    vec2<T>& vec2<T>::operator+=(T x) {
        *this += vec2<T>(x);
        return *this;
    }

    template <typename T>
    vec2<T>& vec2<T>::operator-=(const vec2<T>& v) {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }

    template <typename T>
    vec2<T>& vec2<T>::operator-=(T x) {
        *this -= vec3<T>(x);
        return *this;
    }

    template <typename T>
    vec2<T>& vec2<T>::operator*=(const vec2<T>& v) {
        this->x *= v.x;
        this->y *= v.y;
        return *this;
    }

    template <typename T>
    vec2<T>& vec2<T>::operator*=(T x) {
        *this *= vec2<T>(x);
        return *this;
    }

    template <typename T>
    vec2<T>& vec2<T>::operator/=(const vec2<T>& v) {
        this->x /= v.x;
        this->y /= v.y;
        return *this;
    }

    template <typename T>
    vec2<T>& vec2<T>::operator/=(T x) {
        *this /= vec2<T>(x);
        return *this;
    }

    template <typename T>
    vec2<T>& vec2<T>::operator++() {
        ++this->x;
        ++this->y;
        return *this;
    }

    template <typename T>
    vec2<T>& vec2<T>::operator--() {
        --this->x;
        --this->y;
        return *this;
    }

    template <typename T>
    vec2<T> vec2<T>::operator++(int) {
        vec2<T> temp = *this;
        ++* this;
        return temp;
    }

    template <typename T>
    vec2<T> vec2<T>::operator--(int) {
        vec2<T> temp = *this;
        --* this;
        return temp;
    }

    template <typename T>
    vec2<T> operator+(const vec2<T>& v) {
        return v;
    }

    template <typename T>
    vec2<T> operator+(const vec2<T>& v1, const vec2<T>& v2) {
        return  vec2<T>(v1) += v2;
    }

    template <typename T>
    vec2<T> operator+(T x, const vec2<T>& v) {
        return vec2<T>(x) + v;
    }

    template <typename T>
    vec2<T> operator+(const vec2<T>& v, T x) {
        return vec2<T>(v) += x;
    }

    template <typename T>
    vec2<T> operator-(const vec2<T>& v) {
        return vec2<T>(0) -= v;
    }

    template <typename T>
    vec2<T> operator-(const vec2<T>& v1, const vec2<T>& v2) {
        return vec2<T>(v1) -= v2;
    }

    template <typename T>
    vec2<T> operator-(const vec2<T>& v, T x) {
        return vec2<T>(v) -= x;
    }

    template <typename T>
    vec2<T> operator-(T x, const vec2<T>& v) {
        return vec2<T>(x) - v;
    }

    template <typename T>
    vec2<T> operator*(const vec2<T>& v1, const vec2<T>& v2) {
        return vec2<T>(v1) *= v2;
    }

    template <typename T>
    vec2<T> operator*(const vec2<T>& v, T x) {
        return vec2<T>(v) * vec2<T>(x);
    }

    template <typename T>
    vec2<T> operator*(T x, const vec2<T>& v) {
        return vec2<T>(x) * v;
    }

    template <typename T>
    vec2<T> operator/(const vec2<T>& v1, const vec2<T>& v2) {
        return vec2<T>(v1) /= v2;
    }

    template <typename T>
    vec2<T> operator/(const vec2<T>& v, T x) {
        return vec2<T>(v) /= x;
    }

    template <typename T>
    vec2<T> operator/(T x, const vec2<T>& v) {
        return vec2<T>(x) / v;
    }
}
