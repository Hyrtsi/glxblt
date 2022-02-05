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
    
    return p;
}

Mat4d perspectiveMatrix2(double fovRad, double near, double far)
{
    const double S = 1.0 / (tan(fovRad*0.5));
    const double foo = -(far+near) / (far-near);
    const double bar = (-2.0 * far * near) / (far-near);
    
    Mat4d p;
    p << S, 0.0, 0.0, 0.0,
        0.0, S, 0.0, 0.0,
        0.0, 0.0, foo, -1.0,
        0.0, 0.0, bar, 0.0;
    
    return p;
}

Mat4d cameraMatrix(Vec3d from, Vec3d to, Vec3d up)
{
    Mat4d p;

    // construct the base vectors
    const Vec3d a = (to - from).normalized();
    const Vec3d b = a.cross(up.normalized());
    const Vec3d c = b.cross(a);
    
    Mat3d rot;
    rot << b, c, -a;

    p <<    rot.transpose(), -from,
            Vec3d(0.0, 0.0, 0.0).transpose(), 1.0;

    return p;
}