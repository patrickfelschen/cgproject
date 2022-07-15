//
//  Matrix.h
//  RealtimeRending
//
//  Created by Philipp Lensing on 03.11.14.
//  Copyright (c) 2014 Philipp Lensing. All rights reserved.
//

#ifndef __RealtimeRending__Matrix__
#define __RealtimeRending__Matrix__

#include <iostream>
#include "Vector3f.h"

class Matrix {
public:
    union {
        struct {
            float m00, m10, m20, m30;
            float m01, m11, m21, m31;
            float m02, m12, m22, m32;
            float m03, m13, m23, m33;
        };
        struct {
            float m[16];
        };
    };

    Matrix();

    Matrix(float _00, float _01, float _02, float _03,
           float _10, float _11, float _12, float _13,
           float _20, float _21, float _22, float _23,
           float _30, float _31, float _32, float _33);


    operator float *();

    operator const float *const();

    Matrix operator*(const Matrix &M) const;

    Matrix &operator*=(const Matrix &M);

    Vector3f operator*(const Vector3f &v) const;

    bool operator==(const Matrix &M);

    bool operator!=(const Matrix &M);

    Vector3f left() const;

    Vector3f right() const;

    Vector3f up() const;

    Vector3f down() const;

    Vector3f forward() const;

    Vector3f backward() const;

    Vector3f translation() const;

    void up(const Vector3f &v);

    void forward(const Vector3f &v);

    void right(const Vector3f &v);

    Matrix &multiply(const Matrix &M);

    Matrix &translation(float X, float Y, float Z);

    Matrix &translation(const Vector3f &XYZ);

    Matrix &rotationX(float Angle);

    Matrix &rotationY(float Angle);

    Matrix &rotationZ(float Angle);

    Matrix &rotationYawPitchRoll(float Yaw, float Pitch, float Roll);

    Matrix &rotationYawPitchRoll(const Vector3f &Angles);

    Matrix &rotationAxis(const Vector3f &Axis, float Angle);

    Matrix &scale(float ScaleX, float ScaleY, float ScaleZ);

    Matrix &scale(const Vector3f &Scalings);

    Matrix &scale(float Scaling);

    Matrix &identity();

    Matrix &transpose();

    Matrix &invert();

    Matrix &lookAt(const Vector3f &Target, const Vector3f &Up, const Vector3f &Position);

    Matrix &perspective(float Fovy, float AspectRatio, float NearPlane, float FarPlane);

    Matrix &orthographic(float Width, float Height, float Near, float Far);

    Vector3f transformVec4x4(const Vector3f &v) const;

    Vector3f transformVec3x3(const Vector3f &v) const;

    float determinat();
};


#endif /* defined(__RealtimeRending__Matrix__) */
