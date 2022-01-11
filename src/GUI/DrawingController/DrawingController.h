#ifndef TKOM_DRAWINGCONTROLLER_H
#define TKOM_DRAWINGCONTROLLER_H

#include <iostream>
#include <cmath>
#include <iomanip>

class DrawingController {
    double x = 0;
    double y = 0;
    int angle = 0;
    bool is_drawing = true;
public:
    DrawingController() = default;

    void draw_line( int length);
    void draw_circle( int radius );
    void turn( int degrees );
    void reset();
    void clear();
    void switch_mode();
};


#endif //TKOM_DRAWINGCONTROLLER_H
