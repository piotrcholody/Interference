#include "draw.h"

struct Point { 
    double x; 
    double y; 
};
static double points[300][300];
static Point coord[300][300];
static std::vector<Generator> interference;
	  
void Draw::restart() 
{
	interference.clear();
}

void Draw::source(int x, int y, double t, double freq, double amp, double wvl) 
{
    int i, j;
	for(i = 0; i < 300; i++) {
		for(j = 0; j < 300; j++) {
			if(abs(coord[i][j].x - x) == 0 && abs(coord[i][j].y - y) == 0) {
                break;
            }
		}
		if(abs(coord[i][j].x - x) == 0 && abs(coord[i][j].y - y) == 0) {
            break;
        }
	}
	if (i < 300 && j < 300) {
		interference.push_back(Generator(i, j, freq/10.0, amp, wvl, t));
	}
}

void Draw::generateFunction(double t) 
{
	for(int i = 0;i < 300; i++) {
		for(int j = 0; j < 300; j++) {
			points[i][j] = 0;
			for(std::vector<Generator>::iterator iter = interference.begin(); iter != interference.end(); ++iter) {
				points[i][j] += iter->returnValue(i, j, t);
			}
		}
	}
}

void Draw::draw(double hor, wxDC* dc, double x, double y, double vert, double t) 
{
    dc->Clear();
    wxPen pen;
    pen.SetWidth(3);
    Vector4 vec;
	Matrix4 matrix(vert, hor);
    generateFunction(t);
    double maximum = 0;
    int colour;
    
    for(std::vector<Generator>::iterator iter = interference.begin(); iter != interference.end(); ++iter) {
        maximum += iter->returnAmplitude();
    }
    
    if(hor == 100 || hor < 50) {
        for(int i = 299, k = 0; k < 300; i--, k++) {
            for(int j = 299, m = 0; m < 300; j--, m++) {
                vec.set(150 - i, 150 - j, points[i][j]);
                vec = matrix * vec;
                colour = (points[i][j] / maximum + 1) * 100;
                pen.SetColour(wxColour(colour, colour, colour));
                dc->SetPen(pen);
                dc->DrawPoint(vec.data[0] + x/2, vec.data[1] + y/2);
                coord[i][j].x = vec.data[0] + x/2;
                coord[i][j].y = vec.data[1] + y/2;
            }
        }
    }
    else {
        for(int i = 0, k = 0; k < 300; i++, k++) {
            for(int j = 0, m = 0; m < 300; j++, m++) {
                vec.set(150 - i, 150 - j, points[i][j]);
                vec = matrix * vec;
                colour = (points[i][j] / maximum + 1)*100;
                pen.SetColour(wxColour(colour, colour, colour));
                dc->SetPen(pen);
                dc->DrawPoint(vec.data[0] + x/2, vec.data[1] + y/2);
                coord[i][j].x = vec.data[0] + x/2;
                coord[i][j].y = vec.data[1] + y/2;
            }
        }
    }
}
