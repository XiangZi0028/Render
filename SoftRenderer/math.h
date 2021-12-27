#pragma once

#include <cmath>

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat22.h"
#include "mat23.h"
#include "mat24.h"
#include "mat32.h"
#include "mat33.h"
#include "mat34.h"
#include "mat42.h"
#include "mat43.h"
#include "mat44.h"

namespace math {
    template <typename T>
    T min(T n1, T n2) {
        return n1 < n2 ? n1 : n2;
    }

    template <typename T>
    T min(T n1, T n2, T n3) {
        return n1 < n2 ? min(n1, n3) : min(n2, n3);
    }

    template <typename T>
    T max(T n1, T n2) {
        return n1 > n2 ? n1 : n2;
    }

    template <typename T>
    T max(T n1, T n2, T n3) {
        return n1 > n2 ? max(n1, n3) : max(n2, n3);
    }

    template <typename T>
    vec2<T> normalize(const vec2<T>& v) {
        return v / sqrt(v.x * v.x + v.y * v.y);
    }

    template <typename T>
    vec3<T> normalize(const vec3<T>& v) {
        return v / sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    template <typename T>
    vec4<T> normalize(const vec4<T>& v) {
        return v / sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    }

    template <typename T>
    vec3<T> cross(const vec3<T>& v1, const vec3<T>& v2) {
        return vec3<T>(
            v1.y * v2.z - v2.y * v1.z,
            v1.z * v2.x - v2.z * v1.x,
            v1.x * v2.y - v2.x * v1.y);
    }

    template <typename T>
    T dot(const vec3<T>& v1, const vec3<T>& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    template <typename T>
    T dot(const vec2<T>& v1, const vec2<T>& v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    template <typename T> 
	mat2<T> inverseTranspose(mat2<T> const & m) {
		T Determinant = m[0][0] * m[1][1] - m[1][0] * m[0][1];

		mat2<T> Inverse(
			+ m[1][1] / Determinant,
			- m[0][1] / Determinant,
			- m[1][0] / Determinant, 
			+ m[0][0] / Determinant);

		return Inverse;
	}

	template <typename T> 
	mat3<T> inverseTranspose(mat3<T> const & m) {
		T Determinant = 
			+ m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
			- m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
			+ m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

		mat3<T> Inverse;
		Inverse[0][0] = + (m[1][1] * m[2][2] - m[2][1] * m[1][2]);
		Inverse[0][1] = - (m[1][0] * m[2][2] - m[2][0] * m[1][2]);
		Inverse[0][2] = + (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
		Inverse[1][0] = - (m[0][1] * m[2][2] - m[2][1] * m[0][2]);
		Inverse[1][1] = + (m[0][0] * m[2][2] - m[2][0] * m[0][2]);
		Inverse[1][2] = - (m[0][0] * m[2][1] - m[2][0] * m[0][1]);
		Inverse[2][0] = + (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
		Inverse[2][1] = - (m[0][0] * m[1][2] - m[1][0] * m[0][2]);
		Inverse[2][2] = + (m[0][0] * m[1][1] - m[1][0] * m[0][1]);
		Inverse /= Determinant;

		return Inverse;
	}

	template <typename T> 
	mat4<T> inverseTranspose(mat4<T> const & m) {
		T SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		T SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		T SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		T SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		T SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		T SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		T SubFactor06 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		T SubFactor07 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		T SubFactor08 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		T SubFactor09 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		T SubFactor10 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		T SubFactor11 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		T SubFactor12 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		T SubFactor13 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
		T SubFactor14 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
		T SubFactor15 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
		T SubFactor16 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
		T SubFactor17 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
		T SubFactor18 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		mat4<T> Inverse;
		Inverse[0][0] = + (m[1][1] * SubFactor00 - m[1][2] * SubFactor01 + m[1][3] * SubFactor02);
		Inverse[0][1] = - (m[1][0] * SubFactor00 - m[1][2] * SubFactor03 + m[1][3] * SubFactor04);
		Inverse[0][2] = + (m[1][0] * SubFactor01 - m[1][1] * SubFactor03 + m[1][3] * SubFactor05);
		Inverse[0][3] = - (m[1][0] * SubFactor02 - m[1][1] * SubFactor04 + m[1][2] * SubFactor05);

		Inverse[1][0] = - (m[0][1] * SubFactor00 - m[0][2] * SubFactor01 + m[0][3] * SubFactor02);
		Inverse[1][1] = + (m[0][0] * SubFactor00 - m[0][2] * SubFactor03 + m[0][3] * SubFactor04);
		Inverse[1][2] = - (m[0][0] * SubFactor01 - m[0][1] * SubFactor03 + m[0][3] * SubFactor05);
		Inverse[1][3] = + (m[0][0] * SubFactor02 - m[0][1] * SubFactor04 + m[0][2] * SubFactor05);

		Inverse[2][0] = + (m[0][1] * SubFactor06 - m[0][2] * SubFactor07 + m[0][3] * SubFactor08);
		Inverse[2][1] = - (m[0][0] * SubFactor06 - m[0][2] * SubFactor09 + m[0][3] * SubFactor10);
		Inverse[2][2] = + (m[0][0] * SubFactor11 - m[0][1] * SubFactor09 + m[0][3] * SubFactor12);
		Inverse[2][3] = - (m[0][0] * SubFactor08 - m[0][1] * SubFactor10 + m[0][2] * SubFactor12);

		Inverse[3][0] = - (m[0][1] * SubFactor13 - m[0][2] * SubFactor14 + m[0][3] * SubFactor15);
		Inverse[3][1] = + (m[0][0] * SubFactor13 - m[0][2] * SubFactor16 + m[0][3] * SubFactor17);
		Inverse[3][2] = - (m[0][0] * SubFactor14 - m[0][1] * SubFactor16 + m[0][3] * SubFactor18);
		Inverse[3][3] = + (m[0][0] * SubFactor15 - m[0][1] * SubFactor17 + m[0][2] * SubFactor18);

		T Determinant = 
			+ m[0][0] * Inverse[0][0] 
			+ m[0][1] * Inverse[0][1] 
			+ m[0][2] * Inverse[0][2] 
			+ m[0][3] * Inverse[0][3];

		Inverse /= Determinant;
    
		return Inverse;
	}

    template <typename T>
    mat4<T> translate(const mat4<T>& m, const vec3<T>& v) {
        mat4<T> result;
        result[0] = m[0] * v[0];
        result[1] = m[1] * v[1];
        result[2] = m[2] * v[2];
        result[3] = m[3];
        return result;
    }

    template <typename T>
    mat4<T> scale(const mat4<T>& m, const vec3<T>& v) {
        mat4<T> result;
        result[0] = m[0] * v[0];
        result[1] = m[1] * v[1];
        result[2] = m[2] * v[2];
        result[3] = m[3];
        return result;
    }

    template <typename T>
    mat4<T> rotate(const mat4<T>& m, T theta, const vec3<T>& v) {
        T a = theta / 57.29577951;
		T c = cos(a);
		T s = sin(a);

		vec3<T> axis = normalize(v);

		vec3<T> temp = (T(1) - c) * axis;

		mat4<T> Rotate;
		Rotate[0][0] = c + temp[0] * axis[0];
		Rotate[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
		Rotate[0][2] = 0 + temp[0] * axis[2] - s * axis[1];

		Rotate[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
		Rotate[1][1] = c + temp[1] * axis[1];
		Rotate[1][2] = 0 + temp[1] * axis[2] + s * axis[0];

		Rotate[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
		Rotate[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
		Rotate[2][2] = c + temp[2] * axis[2];

		mat4<T> Result;
		Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
		Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
		Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
		Result[3] = m[3];
		return Result;
        
        // T t = theta / 57.29577951; // 角度转弧度
        // T c = cos(t);
        // T s = sin(t);
        // vec3<T> A = normalize(v);

        // T Rotate00 = c + (T(1) - c) * A.x * A.x;
        // T Rotate01 = 0 + (T(1) - c) * A.x * A.y + s * A.z;
        // T Rotate02 = 0 + (T(1) - c) * A.x * A.z - s * A.y;

        // T Rotate10 = 0 + (T(1) - c) * A.y * A.x - s * A.z;
        // T Rotate11 = c + (T(1) - c) * A.y * A.y;
        // T Rotate12 = 0 + (T(1) - c) * A.y * A.z + s * A.x;

        // T Rotate20 = 0 + (T(1) - c) * A.z * A.x + s * A.y;
        // T Rotate21 = 0 + (T(1) - c) * A.z * A.y - s * A.x;
        // T Rotate22 = c + (T(1) - c) * A.z * A.z;

        // mat4<T> Result;
        // Result[0] = m[0] * Rotate00 + m[1] * Rotate01 + m[2] * Rotate02;
		// Result[1] = m[0] * Rotate10 + m[1] * Rotate11 + m[2] * Rotate12;
		// Result[2] = m[0] * Rotate20 + m[1] * Rotate21 + m[2] * Rotate22;
		// Result[3] = m[3];
        // return Result;
    }

    template <typename T>
    mat4<T> lookAt(const vec3<T>& eye, const vec3<T>& center, const vec3<T>& up) {
        vec3<T> f = normalize(center - eye);
        vec3<T> u = normalize(up);
        vec3<T> s = normalize(cross(f, u));
        u = cross(s, f);

        mat4<T> Result;
        Result[0][0] = s.x;
        Result[1][0] = s.y;
        Result[2][0] = s.z;
        Result[0][1] = u.x;
        Result[1][1] = u.y;
        Result[2][1] = u.z;
        Result[0][2] = -f.x;
        Result[1][2] = -f.y;
        Result[2][2] = -f.z;
        Result[3][0] = -dot(s, eye);
        Result[3][1] = -dot(u, eye);
        Result[3][2] = dot(f, eye);
        return Result;
    }

    template <typename T>
    mat4<T> perspective(T fovy, T aspect, T near, T far) {
        T range = tan(fovy / T(2)) * near;
        T n = near;
        T f = far;
        T t = range;
        T b = -range;
        T l = -range * aspect;
        T r = range * aspect;

        mat4<T> Result(0);
        Result[0][0] = T(2) * n / (r - l);
        Result[1][1] = T(2) * n / (t - b);
        Result[1][2] = (t + b) / (t - b);
        Result[2][0] = (r + l) / (r - l);
        Result[2][1] = (r + b) / (t - b);
        Result[2][2] = -(f + n) / (f - n);
        Result[2][3] = -1.0;
        Result[3][2] = -T(2) * n * f / (f - n);
        return Result;
    }

    template <typename T>
    mat4<T> ortho(T left, T right, T button, T top, T near, T far) {
        T l = left;
        T r = right;
        T b = button;
        T t = top;
        T n = -near;
        T f = -far;

        return mat4<T>(
            T(2) / (r - l), 0, 0, 0,
            0, T(2) / (t - b), 0, 0,
            0, 0, -T(2) / (f - n), 0,
            -(r + l) / (r - l), -(t + b) / (t - b), -(f + n) / (f - n), 1
            );
    }
}