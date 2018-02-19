#pragma once
#include <math.h>
#include "vector.h"

class Matrix4 {
    private:
        double data[4][4];
    public:
        Matrix4(double vert, double hor);
        friend Vector4 operator*(const Matrix4, const Vector4);
};
