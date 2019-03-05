// Copyright 2019 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <array>
#include <cmath>
#include <type_traits>

// Tiny matrix/vector library.
// Used for things like Free-Look in the gfx backend.

namespace Common
{
template <typename T>
union TVec3
{
  TVec3() = default;
  TVec3(T _x, T _y, T _z) : data{_x, _y, _z} {}

  T Dot(const TVec3& other) const { return x * other.x + y * other.y + z * other.z; }
  T LengthSquared() const { return Dot(*this); }
  T Length() const { return std::sqrt(LengthSquared()); }
  TVec3 Normalized() const { return *this / Length(); }

  TVec3& operator+=(const TVec3& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  TVec3& operator-=(const TVec3& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  TVec3& operator*=(const TVec3& rhs)
  {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
  }

  TVec3& operator/=(const TVec3& rhs)
  {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    return *this;
  }

  TVec3 operator-() const { return {-x, -y, -z}; }

  std::array<T, 3> data = {};

  struct
  {
    T x;
    T y;
    T z;
  };
};

template <typename T>
TVec3<T> operator+(TVec3<T> lhs, const TVec3<T>& rhs)
{
  return lhs += rhs;
}

template <typename T>
TVec3<T> operator-(TVec3<T> lhs, const TVec3<T>& rhs)
{
  return lhs -= rhs;
}

template <typename T>
TVec3<T> operator*(TVec3<T> lhs, const TVec3<T>& rhs)
{
  return lhs *= rhs;
}

template <typename T>
inline TVec3<T> operator/(TVec3<T> lhs, const TVec3<T>& rhs)
{
  return lhs /= rhs;
}

template <typename T>
TVec3<T> operator*(TVec3<T> lhs, std::common_type_t<T> scalar)
{
  return lhs *= TVec3<T>{scalar, scalar, scalar};
}

template <typename T>
TVec3<T> operator/(TVec3<T> lhs, std::common_type_t<T> scalar)
{
  return lhs /= TVec3<T>{scalar, scalar, scalar};
}

using Vec3 = TVec3<float>;
using DVec3 = TVec3<double>;

template <typename T>
union TVec4
{
  TVec4() = default;
  TVec4(TVec3<T> _vec, T _w) : TVec4{_vec.x, _vec.y, _vec.z, _w} {}
  TVec4(T _x, T _y, T _z, T _w) : data{_x, _y, _z, _w} {}

  TVec4& operator*=(const TVec4& rhs)
  {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    w *= rhs.w;
    return *this;
  }

  TVec4& operator/=(const TVec4& rhs)
  {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    w /= rhs.w;
    return *this;
  }

  TVec4& operator*=(T scalar) { return *this *= TVec4{scalar, scalar, scalar, scalar}; }
  TVec4& operator/=(T scalar) { return *this /= TVec4{scalar, scalar, scalar, scalar}; }

  std::array<T, 4> data = {};

  struct
  {
    T x;
    T y;
    T z;
    T w;
  };
};

template <typename T>
TVec4<T> operator*(TVec4<T> lhs, std::common_type_t<T> scalar)
{
  return lhs *= scalar;
}

template <typename T>
TVec4<T> operator/(TVec4<T> lhs, std::common_type_t<T> scalar)
{
  return lhs /= scalar;
}

using Vec4 = TVec4<float>;
using DVec4 = TVec4<double>;

template <typename T>
union TVec2
{
  TVec2() = default;
  TVec2(T _x, T _y) : data{_x, _y} {}

  T Cross(const TVec2& rhs) const { return (x * rhs.y) - (y * rhs.x); }
  T Dot(const TVec2& rhs) const { return (x * rhs.x) + (y * rhs.y); }
  T LengthSquared() const { return Dot(*this); }
  T Length() const { return std::sqrt(LengthSquared()); }
  TVec2 Normalized() const { return *this / Length(); }

  TVec2& operator+=(const TVec2& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  TVec2& operator-=(const TVec2& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  TVec2& operator*=(T scalar)
  {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  TVec2& operator/=(T scalar)
  {
    x /= scalar;
    y /= scalar;
    return *this;
  }

  TVec2 operator-() const { return {-x, -y}; }

  std::array<T, 2> data = {};

  struct
  {
    T x;
    T y;
  };
};

template <typename T>
TVec2<T> operator+(TVec2<T> lhs, const TVec2<T>& rhs)
{
  return lhs += rhs;
}

template <typename T>
TVec2<T> operator-(TVec2<T> lhs, const TVec2<T>& rhs)
{
  return lhs -= rhs;
}

template <typename T>
TVec2<T> operator*(TVec2<T> lhs, T scalar)
{
  return lhs *= scalar;
}

template <typename T>
TVec2<T> operator/(TVec2<T> lhs, T scalar)
{
  return lhs /= scalar;
}

using Vec2 = TVec2<float>;
using DVec2 = TVec2<double>;

class Matrix33
{
public:
  static Matrix33 Identity();

  // Return a rotation matrix around the x,y,z axis
  static Matrix33 RotateX(float rad);
  static Matrix33 RotateY(float rad);
  static Matrix33 RotateZ(float rad);

  static Matrix33 Scale(const Vec3& vec);

  // set result = a x b
  static void Multiply(const Matrix33& a, const Matrix33& b, Matrix33* result);
  static void Multiply(const Matrix33& a, const Vec3& vec, Vec3* result);

  Matrix33& operator*=(const Matrix33& rhs)
  {
    Multiply(*this, rhs, this);
    return *this;
  }

  // Note: Row-major storage order.
  std::array<float, 9> data;
};

inline Matrix33 operator*(Matrix33 lhs, const Matrix33& rhs)
{
  return lhs *= rhs;
}

inline Vec3 operator*(const Matrix33& lhs, Vec3 rhs)
{
  Matrix33::Multiply(lhs, rhs, &rhs);
  return rhs;
}

class Matrix44
{
public:
  static Matrix44 Identity();
  static Matrix44 FromMatrix33(const Matrix33& m33);
  static Matrix44 FromArray(const std::array<float, 16>& arr);

  static Matrix44 Translate(const Vec3& vec);
  static Matrix44 Shear(const float a, const float b = 0);
  static Matrix44 Perspective(float fov_y, float aspect_ratio, float z_near, float z_far);

  static void Multiply(const Matrix44& a, const Matrix44& b, Matrix44* result);
  static void Multiply(const Matrix44& a, const Vec4& vec, Vec4* result);

  // For when a vec4 isn't needed a multiplication function that takes a Vec3 and w:
  Vec3 Transform(const Vec3& point, float w) const;

  Matrix44& operator*=(const Matrix44& rhs)
  {
    Multiply(*this, rhs, this);
    return *this;
  }

  // Note: Row-major storage order.
  std::array<float, 16> data;
};

inline Matrix44 operator*(Matrix44 lhs, const Matrix44& rhs)
{
  return lhs *= rhs;
}

inline Vec4 operator*(const Matrix44& lhs, Vec4 rhs)
{
  Matrix44::Multiply(lhs, rhs, &rhs);
  return rhs;
}

}  // namespace Common
