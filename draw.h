#pragma once
#include <vector>
#include "vector.h"
#include "matrix.h"
#include "generator.h"
#include <wx/dcbuffer.h>

class Draw {
  public:
       static void restart();
       static void draw(double hor, wxDC* dc, double x, double y, double vert, double t);
	   static void source(int x, int y, double t, double freq, double amp, double wvl);
	   static void generateFunction(double t);
};

