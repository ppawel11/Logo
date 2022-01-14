#include "DrawingController.h"

void DrawingController::draw_line(int length) {
    std::cout<< std::setprecision(5) << "drawing line with length: " << length << std::endl;
    emit drawLine_( length );
}

void DrawingController::draw_circle( int radius ) {
    std::cout<<"drawing circle  in: " << x << ", " << y << " radius: " << radius << std::endl;
    emit drawCircle( radius );
}

void DrawingController::reset() {
    std::cout<<"reseting marker position"<<std::endl;
    angle = 0.0;
    emit reset_();
}

void DrawingController::clear() {
    std::cout<<"clear drawing area"<<std::endl;
    emit clear_();
}

void DrawingController::switch_mode() {
    is_drawing = !is_drawing;
    std::cout << "drawing mode: " << is_drawing << std::endl;
    emit switch_();
}

void DrawingController::turn(int degrees) {
    std::cout<<std::setprecision(5)<<"turning from: "<<angle;

    angle = angle + degrees;
    while (  angle > 360.0 )
    {
        angle = angle - 360.0;
    }

    std::cout<<std::setprecision(5)<<" to: "<<angle<<std::endl;
}

qreal DrawingController::get_marker_pos_x() const {
    return qreal(x);
}

void DrawingController::set_marker_pos_x(qreal new_x) {
    std::cout<<std::setprecision(5)<<"x axis moving from: "<<x<<" to: "<<new_x<<std::endl;
    x = double(new_x);
    emit marker_pos_x_changed();
}

qreal DrawingController::get_marker_pos_y() const {
    return qreal(y);
}

void DrawingController::set_marker_pos_y(qreal new_y) {
    std::cout<<std::setprecision(5)<<"y axis moving from: "<<y<<" to: "<<new_y<<std::endl;
    y = double(new_y);
    emit marker_pos_y_changed();
}

qreal DrawingController::get_marker_rotation() const {
    return qreal(angle);
}

void DrawingController::set_marker_rotation(qreal new_angle) {
    angle = double(new_angle);
}

bool DrawingController::get_drawing() const {
    return is_drawing;
}

void DrawingController::set_drawing(bool isDrawing) {
    is_drawing = isDrawing;
    emit drawing_changed();
}
