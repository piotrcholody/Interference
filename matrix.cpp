#include "matrix.h"

Matrix4::Matrix4(double vert, double hor) {
    double r_x = vert * M_PI / 200;
	double r_y = 0;
	double r_z = hor * M_PI / 50;
	
    data[0][0] = cos(r_y) * cos(r_z); 
    data[0][1] = -cos(r_y) * sin(r_z); 
    data[0][2] = -sin(r_y); 
    data[0][3] = 0.0;
    
    data[1][0] = cos(r_x) * sin(r_z) - sin(r_y) * cos(r_z) * sin(r_x); 
    data[1][1] = sin(r_y) * sin(r_x) * sin(r_z) + cos(r_x) * cos(r_z); 
    data[1][2] = -sin(r_x) * cos(r_y); 
    data[1][3] = 0.0;
    
    data[2][0] = cos(r_x) * sin(r_y) * cos(r_z) + sin(r_x) * sin(r_z); 
    data[2][1] = -sin(r_z) * cos(r_x) * sin(r_y) + sin(r_x) * cos(r_z); 
    data[2][2] = cos(r_x) * cos(r_y); 
    data[2][3] = 0.0;
    
    data[3][0] = 0.0; 
    data[3][1] = 0.0; 
    data[3][2] = 0.0; 
    data[3][3] = 0.0; 
}

Vector4 operator*(const Matrix4 M, const Vector4 V) {
    Vector4 tmp;
    for(int i = 0; i < 4; i++) {
        tmp.data[i] = 0.0;
        for(int j = 0; j < 4; j++) {
            tmp.data[i] = tmp.data[i] + (M.data[i][j] * V.data[j]);
        }
    }
    return tmp;
}
