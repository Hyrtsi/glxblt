#include "matutils.hpp"

Mat4d perspectiveMatrix(double fovRad, double near, double far)
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