#include "generator.h"

Generator::Generator(int x, int y, double freq, double amp, double wvl, double t0)
    : _x(x)
    , _y(y)
    , _freq(freq)
    , _t0(t0)
    , _amp(amp)
    , _wvl(wvl)
{
    for(int x = 0; x < 300; x++) {
        for(int y = 0; y < 300; y++) {
            r[x][y] = sqrt((x - _x) * (x - _x) + (y - _y) * (y - _y));
        }
    }
}
    
double Generator::returnValue(int x, int y, double t) {
    double dt = (t - _t0)/1000.0;
    if (r[x][y] / _freq / _wvl < dt ) {
        return _amp * sin(2 * M_PI * _freq * dt - 2 * M_PI * r[x][y] / _wvl);
    }
    else{
        return 0;
    }
}

double Generator::returnAmplitude() {
    return _amp;
}
