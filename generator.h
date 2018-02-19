#pragma once
#include <math.h>

class Generator {
    public:
        Generator(int x, int y, double freq, double amp, double wvl, double t0);
        double returnValue(int x, int y, double t);
        double returnAmplitude();
    private:
        int _x, _y;
        double _freq, _amp, _wvl;
        long _t0;
        double r[300][300];
};

