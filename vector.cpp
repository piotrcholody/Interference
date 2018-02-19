#include "vector.h"

void Vector4::set(int x, int y ,double z) {
    data[0] = x;
    data[1] = y;
    data[2] = z;
    data[3] = 0.0;
}
