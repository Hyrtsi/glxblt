#include "matutils.hpp"

Mat4d perspectiveMatrix(double fovRad, double near, double far)
{
    const double S = 1.0 / (tan(fovRad*0.5));
    const double foo = -(far) / (far-near);
    const double bar = (-far * near) / (far-near);
    
    Mat4d p;
    p << S, 0.0, 0.0, 0.0,
        0.0, S, 0.0, 0.0,
        0.0, 0.0, foo, -1.0,
        0.0, 0.0, bar, 0.0;
    
    return p.transpose();
}

// todo const reference
Mat4d cameraMatrix(Vec3d from, Vec3d to, Vec3d up)
{
    Mat4d p;

    // construct the base vectors
    const Vec3d negz = (to - from).normalized();
    const Vec3d x = negz.cross(up.normalized());
    const Vec3d y = x.cross(negz);
    
    Mat3d rot;
    rot << x, y, -negz;

    p <<    rot, from,
            Vec3d(0.0, 0.0, 0.0).transpose(), 1.0;

    return p.inverse();
}

Mat4d transformationMatrix(const Vec3d& pos, const Vec3d& eulerAngles)
{
    Mat4d p;

    Eigen::AngleAxisd rollAngle(eulerAngles(0), Eigen::Vector3d::UnitZ());
    Eigen::AngleAxisd yawAngle(eulerAngles(1), Eigen::Vector3d::UnitY());
    Eigen::AngleAxisd pitchAngle(eulerAngles(2), Eigen::Vector3d::UnitX());

    Eigen::Quaternion<double> q = rollAngle * yawAngle * pitchAngle;

    Mat3d rot{q.matrix()};

    p <<    rot, pos,
            Vec3d(0.0, 0.0, 0.0).transpose(), 1.0;
    return p;
}