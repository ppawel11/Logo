#include "DrawingController.h"

void DrawingController::draw_line(int length) {
    double new_x = x + length * cos(angle * M_PI / 180 );
    double new_y = y + length * sin(angle * M_PI / 180);
    std::cout<< std::setprecision(5) << "drawing line from: " << x << ", " << y << " to: " << new_x << ", " << new_y << std::endl;
    x = new_x;
    y = new_y;
}

void DrawingController::draw_circle( int radius ) {
    std::cout<<"drawing line in: " << x << ", " << y << " radius: " << radius << std::endl;
}

void DrawingController::reset() {
    std::cout<<"reseting marker position to 0,0"<<std::endl;
    x = 0.0;
    y = 0.0;
}

void DrawingController::clear() {
    std::cout<<"clear drawing area"<<std::endl;
}

void DrawingController::switch_mode() {
    std::cout<<"drawing mode: "<<is_drawing<<std::endl;
}

void DrawingController::turn(int degrees) {
    std::cout<<"turning from: "<<angle<<" to: "<<( angle + degrees ) % 360<<std::endl;
    angle = ( angle + degrees ) % 360;
}
