#pragma once

namespace math {
    template <typename T>
    struct vec2;
    template <typename T>
    struct vec4;

    template <typename T>
    struct vec3 {
        union
        {
            struct { T x, y, z; };
            struct { T r, g, b; };
            struct { T s, t, p; };
        };

        vec3();
        vec3(T x);
        vec3(T x, T y, T z);
        vec3(const vec2<T>& _xy, T z);

        vec3(T x, const vec2<T>& _yz);

        vec3(const vec3<T>& v);

        vec3(const vec4<T>& v);

        vec3<T>& operator=(const vec3<T>& v);
        T& operator[](size_t i);
        const T& operator[](size_t i)const;
        vec3<T>& operator+=(const vec3<T>& v);
        vec3<T>& operator+=(T x);
        vec3<T>& operator-=(const vec3<T>& v);
        vec3<T>& operator-=(T x);
        vec3<T>& operator*=(const vec3<T>& v);
        vec3<T>& operator*=(T x);
        vec3<T>& operator/=(const vec3<T>& v);
        vec3<T>& operator/=(T x);
        vec3<T>& operator++();
        vec3<T>& operator--();
        vec3<T> operator++(int);
        vec3<T> operator--(int);
    };

    template <typename T>
    vec3<T>::vec3()
        : x(0), y(0), z(0)
    {}

    template <typename T>
    vec3<T>::vec3(T x)
        : x(x), y(x), z(x)
    {}

    template <typename T>
    vec3<T>::vec3(T x, T y, T z)
        : x(x), y(y), z(z)
    {}

    template <typename T>
    vec3<T>::vec3(const vec2<T>& _xy, T z)
        : x(_xy.x), y(_xy.y), z(z)
    {}

    template <typename T>
    vec3<T>::vec3(T x, const vec2<T>& _yz)
        : x(x), y(_yz.x), z(_yz.y)
    {}

    template <typename T>
    vec3<T>::vec3(const vec3<T>& v)
        : x(v.x), y(v.y), z(v.z)
    {}

    template <typename T>
    vec3<T>::vec3(const vec4<T>& v)
        : x(v.x), y(v.y), z(v.z)
    {}

    template <typename T>
    vec3<T>& vec3<T>::operator=(const vec3<T>& v) {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        return *this;
    }

    template <typename T>
    T& vec3<T>::operator[](size_t i) {
        return (&x)[i];
    }

    template <typename T>
    const T& vec3<T>::operator[](size_t i) const {
        return (&x)[i];
    }

    template <typename T>
    vec3<T>& vec3<T>::operator+=(const vec3<T>& v) {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        return *this;
    }

    template <typename T>
    vec3<T>& vec3<T>::operator+=(T x) {
        *this += vec3<T>(x);
        return *this;
    }

    template <typename T>
    vec3<T>& vec3<T>::operator-=(const vec3<T>& v) {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        return *this;
    }

    template <typename T>
    vec3<T>& vec3<T>::operator-=(T x) {
        *this -= vec3<T>(x);
        return *this;
    }

    template <typename T>
    vec3<T>& vec3<T>::operator*=(const vec3<T>& v) {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        return *this;
    }

    template <typename T>
    vec3<T>& vec3<T>::operator*=(T x) {
        *this *= vec3<T>(x);
        return *this;
    }

    template <typename T>
    vec3<T>& vec3<T>::operator/=(const vec3<T>& v) {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        return *this;
    }

    template <typename T>
    vec3<T>& vec3<T>::operator/=(T x) {
        *this /= vec3<T>(x);
        return *this;
    }

    template <typename T>
    vec3<T>& vec3<T>::operator++() {
        ++this->x;
        ++this->y;
        ++this->z;
        return *this;
    }

    template <typename T>
    vec3<T>& vec3<T>::operator--() {
        --this->x;
        --this->y;
        --this->z;
        return *this;
    }

    template <typename T>
    vec3<T> vec3<T>::operator++(int) {
        vec3<T> temp = *this;
        ++* this;
        return temp;
    }

    template <typename T>
    vec3<T> vec3<T>::operator--(int) {
        vec3<T> temp = *this;
        --* this;
        return temp;
    }

    template <typename T>
    vec3<T> operator+(const vec3<T>& v) {
        return v;
    }

    template <typename T>
    vec3<T> operator+(const vec3<T>& v1, const vec3<T>& v2) {
        return vec3<T>(v1) += v2;
    }

    template <typename T>
    vec3<T> operator+(T x, const vec3<T>& v) {
        return vec3<T>(x) += v;
    }

    template <typename T>
    vec3<T> operator+(const vec3<T>& v, T x) {
        return vec3<T>(v) += x;
    }

    template <typename T>
    vec3<T> operator-(const vec3<T>& v) {
        return vec3<T>(0) -= v;
    }

    template <typename T>
    vec3<T> operator-(const vec3<T>& v1, const vec3<T>& v2) {
        return vec3<T>(v1) -= v2;
    }

    template <typename T>
    vec3<T> operator-(T x, const vec3<T>& v) {
        return vec3<T>(x) -= v;
    }

    template <typename T>
    vec3<T> operator-(const vec3<T>& v, T x) {
        return vec3<T>(v) -= x;
    }

    template <typename T>
    vec3<T> operator*(const vec3<T>& v1, const vec3<T>& v2) {
        return vec3<T>(v1) *= v2;
    }

    template <typename T>
    vec3<T> operator*(T x, const vec3<T>& v) {
        return vec3<T>(x) *= v;
    }

    template <typename T>
    vec3<T> operator*(const vec3<T>& v, T x) {
        return vec3<T>(v) *= x;
    }

    template <typename T>
    vec3<T> operator/(const vec3<T>& v1, const vec3<T>& v2) {
        return vec3<T>(v1) /= v2;
    }

    template <typename T>
    vec3<T> operator/(T x, const vec3<T>& v) {
        return vec3<T>(x) /= v;
    }

    template <typename T> 
    vec3<T> operator/(const vec3<T>& v, T x) {
        return vec3<T>(v) /= x;
    }
}