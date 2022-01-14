#ifndef TKOM_DRAWINGCONTROLLER_H
#define TKOM_DRAWINGCONTROLLER_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include <QtCore/QObject>

class DrawingController: public QObject {
Q_OBJECT

    Q_PROPERTY( qreal marker_pos_x MEMBER x READ get_marker_pos_x WRITE set_marker_pos_x NOTIFY marker_pos_x_changed );
    Q_PROPERTY( qreal marker_pos_y MEMBER y READ get_marker_pos_y WRITE set_marker_pos_y NOTIFY marker_pos_y_changed );
    Q_PROPERTY( qreal marker_rotation MEMBER angle READ get_marker_rotation WRITE set_marker_rotation NOTIFY marker_rotation_changed );
    Q_PROPERTY( bool is_drawing MEMBER get_drawing READ get_drawing WRITE set_drawing NOTIFY drawing_changed );
    double x = 0.0;
    double y = 0.0;
    double angle = 45.0;
public:
    bool get_drawing() const;

    void set_drawing(bool isDrawing);

private:
    bool is_drawing = true;
public:
    explicit DrawingController(QObject * parent = nullptr): QObject{ parent } {};
    ~DrawingController() = default;

    void turn( int degrees );

    qreal get_marker_pos_x() const;

    void set_marker_pos_x(qreal new_x);
    qreal get_marker_pos_y() const;
    void set_marker_pos_y(qreal new_y);
    qreal get_marker_rotation() const;
    void set_marker_rotation(qreal new_angle);
public slots:

    void switch_mode();
    void reset();
    void clear();
    void draw_line( int length);
    void draw_circle( int radius );


signals:
    void clear_();
    void switch_();
    void reset_();
    void drawLine_( qint16 length );
    void drawCircle( qint16 radius );
    void marker_pos_x_changed();
    void marker_pos_y_changed();
    void drawing_changed();

    void marker_rotation_changed();


};


#endif //TKOM_DRAWINGCONTROLLER_H
