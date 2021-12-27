#pragma once

namespace math 
{
    template <typename T> struct vec2;
    template <typename T> struct vec3;

    template <typename T>
    struct vec4 {
        union
        {
            struct { T x, y, z, w; };
            struct { T r, g, b, a; };
            struct { T s, t, p, q; };
        };

        vec4();
        vec4(T x);
        vec4(T x, T y, T z, T w);
        vec4(const vec2<T>& v0, const vec2<T>& v1);
        vec4(const vec2<T>& _xy, T z, T w);
        vec4(T x, const vec2<T>& _yz, T w);
        vec4(T x, T y, const vec2<T>& _zw);
        vec4(const vec3<T>& _xyz, T w);
        vec4(T x, const vec3<T>& _yzw);
        vec4(const vec4<T>& v);

        vec4<T>& operator=(const vec4<T>& v);
        T& operator[](size_t i);
        const T& operator[](size_t i) const;
        vec4<T>& operator+=(const vec4<T>& v);
        vec4<T>& operator+=(T x);
        vec4<T>& operator-=(const vec4<T>& v);
        vec4<T>& operator-=(T x);
        vec4<T>& operator*=(const vec4<T>& v);
        vec4<T>& operator*=(T x);
        vec4<T>& operator/=(const vec4<T>& v);
        vec4<T>& operator/=(T x);
        vec4<T>& operator++();
        vec4<T>& operator--();
        vec4<T> operator++(int);
        vec4<T> operator--(int);
    };

    template <typename T>
    vec4<T>::vec4()
        : x(0), y(0), z(0), w(0)
    {}

    template <typename T>
    vec4<T>::vec4(T x)
        : x(x), y(x), z(x), w(x)
    {}

    template <typename T>
    vec4<T>::vec4(T x, T y, T z, T w)
        : x(x), y(y), z(z), w(w)
    {}

    template <typename T>
    vec4<T>::vec4(const vec2<T>& v0, const vec2<T>& v1)
        : x(v0.x), y(v0.y), z(v1.x), w(v1.y)
    {}

    template <typename T>
    vec4<T>::vec4(const vec2<T>& _xy, T z, T w)
        : x(_xy.x), y(_xy.y), z(z), w(w)
    {}

    template <typename T>
    vec4<T>::vec4(T x, const vec2<T>& _yz, T w)
        : x(x), y(_yz.y), z(_yz.z), w(w)
    {}

    template <typename T>
    vec4<T>::vec4(T x, T y, const vec2<T>& _zw)
        : x(x), y(y), z(_zw.z), w(_zw.w)
    {}

    template <typename T>
    vec4<T>::vec4(const vec3<T>& _xyz, T w)
        : x(_xyz.x), y(_xyz.y), z(_xyz.z), w(w)
    {}

    template <typename T>
    vec4<T>::vec4(T x, const vec3<T>& _yzw)
        : x(x), y(_yzw.x), z(_yzw.y), w(_yzw.z)
    {}

    template <typename T>
    vec4<T>::vec4(const vec4<T>& v)
        : x(v.x), y(v.y), z(v.z), w(v.w)
    {}

    template <typename T>
    vec4<T>& vec4<T>::operator=(const vec4& v) {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        this->w = v.w;
        return *this;
    }

    template <typename T>
    T& vec4<T>::operator[](size_t i) {
        return (&x)[i];
    }

    template <typename T>
    const T& vec4<T>::operator[](size_t i) const {
        return (&x)[i];
    }

    template <typename T>
    vec4<T>& vec4<T>::operator+=(const vec4& v) {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        this->w += v.w;
        return *this;
    }

    template <typename T>
    vec4<T>& vec4<T>::operator+=(T x) {
        *this += vec4(x);
        return *this;
    }

    template <typename T>
    vec4<T>& vec4<T>::operator-=(const vec4& v) {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        this->w -= v.w;
        return *this;
    }

    template <typename T>
    vec4<T>& vec4<T>::operator-=(T x) {
        *this -= vec4(x);
        return *this;
    }

    template <typename T>
    vec4<T>& vec4<T>::operator*=(const vec4& v) {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        this->w *= v.w;
        return *this;
    }

    template <typename T>
    vec4<T>& vec4<T>::operator*=(T x) {
        *this *= vec4(x);
        return *this;
    }

    template <typename T>
    vec4<T>& vec4<T>::operator/=(const vec4& v) {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        this->w /= v.w;
        return *this;
    }

    template <typename T>
    vec4<T>& vec4<T>::operator/=(T x) {
        *this /= vec4(x);
        return *this;
    }

    template <typename T>
    vec4<T>& vec4<T>::operator++() {
        ++this->x;
        ++this->y;
        ++this->z;
        ++this->w;
        return *this;
    }

    template <typename T>
    vec4<T>& vec4<T>::operator--() {
        --this->x;
        --this->y;
        --this->z;
        --this->w;
        return *this;
    }

    template <typename T>
    vec4<T> vec4<T>::operator++(int) {
        vec4 temp = *this;
        ++* this;
        return temp;
    }

    template <typename T>
    vec4<T> vec4<T>::operator--(int) {
        vec4 temp = *this;
        --* this;
        return temp;
    }

    template <typename T>
    vec4<T> operator+(const vec4<T>& v) {
        return v;
    }

    template <typename T>
    vec4<T> operator+(const vec4<T>& v1, const vec4<T>& v2) {
        return  vec4<T>(v1) += v2;
    }

    template <typename T>
    vec4<T> operator+(const vec4<T>& v, T x) {
        return vec4<T>(v) += x;
    }

    template <typename T>
    vec4<T> operator+(T x, const vec4<T>& v) {
        return vec4<T>(x) += v;
    }

    template <typename T>
    vec4<T> operator-(const vec4<T>& v) {
        return vec4<T>(0) -= v;
    }

    template <typename T>
    vec4<T> operator-(const vec4<T>& v1, const vec4<T>& v2) {
        return vec4<T>(v1) -= v2;
    }

    template <typename T>
    vec4<T> operator-(const vec4<T>& v, T x) {
        return vec4<T>(v) -= x;
    }

    template <typename T>
    vec4<T> operator-(T x, const vec4<T>& v) {
        return vec4<T>(x) -= v;
    }

    template <typename T>
    vec4<T> operator*(const vec4<T>& v1, const vec4<T>& v2) {
        return vec4<T>(v1) *= v2;
    }

    template <typename T>
    vec4<T> operator*(const vec4<T>& v, T x) {
        return vec4<T>(v) * vec4<T>(x);
    }

    template <typename T>
    vec4<T> operator*(T x, const vec4<T>& v) {
        return vec4<T>(x) *= v;
    }

    template <typename T>
    vec4<T> operator/(const vec4<T>& v1, const vec4<T>& v2) {
        return vec4<T>(v1) /= v2;
    }

    template <typename T>
    vec4<T> operator/(const vec4<T>& v, T x) {
        return vec4<T>(v) /= x;
    }

    template <typename T>
    vec4<T> operator/(T x, const vec4<T>& v) {
        return vec4<T>(x) /= v;
    }
}
