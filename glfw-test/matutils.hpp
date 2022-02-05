#pragma once

#include <Eigen/Dense>


using Vec2f = Eigen::Vector2f;
using Vec3f = Eigen::Vector3f;
using Vec4f = Eigen::Vector4f;

using Mat2f = Eigen::Matrix2f;
using Mat3f = Eigen::Matrix3f;
using Mat4f = Eigen::Matrix4f;

using Vec2d = Eigen::Vector2d;
using Vec3d = Eigen::Vector3d;
using Vec4d = Eigen::Vector4d;

using Mat2d = Eigen::Matrix2d;
using Mat3d = Eigen::Matrix3d;
using Mat4d = Eigen::Matrix4d;

Mat4d perspectiveMatrix(double fovRad, double near, double far);

Mat4d cameraMatrix(Vec3d from, Vec3d to, Vec3d up);

Mat4d transformationMatrix(const Vec3d& pos, const Vec3d& eulerAngles = Vec3d(0.0, 0.0, 0.0));