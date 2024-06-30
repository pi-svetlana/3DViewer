#define GL_SILENCE_DEPRECATION
#include "viewer.h"

#include <iostream>

Viewer::Viewer(QWidget* parent) : QOpenGLWidget{parent} {}

void Viewer::initializeGL() { initializeOpenGLFunctions(); }

void Viewer::paintGL() {
  glEnable(GL_DEPTH_TEST);
  glClearColor(bg_color_.redF(), bg_color_.greenF(), bg_color_.blueF(), 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  setProjection();
  if (data_ != nullptr) {
    glVertexPointer(3, GL_DOUBLE, 0, &(data_->vertexes[0].x));
    glTranslated(move_x_ / 100, 0, 0);
    glTranslated(0, move_y_ / 100, 0);
    glTranslated(0, 0, move_z_ / 100);
    glPointSize(vertex_size_ / 5);
    if (vertex_type_ == 0) {  // круглые точки
      glEnable(GL_POINT_SMOOTH);
    }
    if (vertex_type_ != 2) {  // 2 = не отображать

      glColor3d(vertex_color_.redF(), vertex_color_.greenF(),
                vertex_color_.blueF());
      glEnableClientState(GL_VERTEX_ARRAY);
      glDrawArrays(GL_POINTS, 0, data_->vertexes.size());
      glDisableClientState(GL_VERTEX_ARRAY);
    }
    if (vertex_type_ == 0) {
      glDisable(GL_POINT_SMOOTH);
    }
    if (line_type_ == 1) {  // пунктирные линии
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, dot_set_);
    }
    glLineWidth(line_width_ / 20);
    if (line_type_ != 2) {  // 2 = не отображать
      glColor3d(line_color_.redF(), line_color_.greenF(), line_color_.blueF());
      glEnableClientState(GL_VERTEX_ARRAY);
      glDrawElements(GL_LINES, static_cast<int>(data_->vertex_indexes.size()),
                     GL_UNSIGNED_INT, data_->vertex_indexes.data());
      glDisableClientState(GL_VERTEX_ARRAY);
      if (line_type_ == 1) glDisable(GL_LINE_STIPPLE);
    }
  }
}

void Viewer::resizeGL(int w, int h) {
  if (w < h) {
    resize(w, w);
  } else {
    resize(h, h);
  }
}

void Viewer::setProjection() {
  if (projection_type_ == 0) {
    glOrtho(-1, 1, -1, 1, 0, 15);
    glTranslated(0, 0, -6);
  } else {
    glFrustum(-1, 1, -1, 1, 5, 20);
    glTranslated(0, 0, -8);
  }
}

void Viewer::wheelEvent(QWheelEvent* event) {
  if (data_) {
    QPoint numPixels = event->pixelDelta();
    QPoint numDegrees = event->angleDelta() / 8;
    if (!numPixels.isNull()) {
      emit changeScale(numPixels.y());
    } else if (!numDegrees.isNull()) {
      emit changeScale(numDegrees.y());
    }
  }
}

void Viewer::mousePressEvent(QMouseEvent* event) {
  mouse_position_ = event->pos();
}

void Viewer::mouseMoveEvent(QMouseEvent* event) {
  if (data_) {
    new_pos_ = QPoint(mouse_position_ - event->pos());
    if (event->buttons() & Qt::LeftButton) {
      if (move_x_ - new_pos_.x() / 60 >= -100 &&
          move_x_ - new_pos_.x() / 60 <= 100 &&
          move_y_ + new_pos_.y() / 60 >= -100 &&
          move_y_ + new_pos_.y() / 60 <= 100) {
        move_x_ += -new_pos_.x() / 60;
        move_y_ += new_pos_.y() / 60;
        update();
      }
    } else if (event->buttons() & Qt::RightButton) {
      emit changeRotationY(-new_pos_.x() * 0.01 - rotate_y_);
      emit changeRotationX(-new_pos_.y() * 0.01 - rotate_x_);
      rotate_x_ = new_pos_.y() * 0.01;
      rotate_y_ = new_pos_.x() * 0.01;
    }
  }
}

QColor Viewer::getBackGroundColor() { return bg_color_; }
QColor Viewer::getVertexColor() { return vertex_color_; }
QColor Viewer::getLineColor() { return line_color_; }
float Viewer::getVertexSize() { return vertex_size_; }
int Viewer::getVertexType() { return vertex_type_; }
float Viewer::getLineWidth() { return line_width_; }
int Viewer::getLineType() { return line_type_; }
double Viewer::getMoveX() { return move_x_; }
double Viewer::getMoveY() { return move_y_; }
double Viewer::getMoveZ() { return move_z_; }
double Viewer::getRotateX() { return rotate_x_; }
double Viewer::getRotateY() { return rotate_y_; }
double Viewer::getRotateZ() { return rotate_z_; }
double Viewer::getScale() { return scale_; }
int Viewer::getProjectionType() { return projection_type_; }
ObjData* Viewer::getDataObj() { return data_; }

void Viewer::setBgColor(QColor color) { bg_color_ = color; }
void Viewer::setLineColor(QColor color) { line_color_ = color; }
void Viewer::setVertexColor(QColor color) { vertex_color_ = color; }
void Viewer::setVertexSize(float value) { vertex_size_ = value; }
void Viewer::setVertexType(int value) { vertex_type_ = value; }
void Viewer::setLineWidth(float value) { line_width_ = value; }
void Viewer::setLineType(int value) { line_type_ = value; }
void Viewer::setMoveX(double value) { move_x_ = value; }
void Viewer::setMoveY(double value) { move_y_ = value; }
void Viewer::setMoveZ(double value) { move_z_ = value; }
void Viewer::setRotateX(double value) { rotate_x_ = value; }
void Viewer::setRotateY(double value) { rotate_y_ = value; }
void Viewer::setRotateZ(double value) { rotate_z_ = value; }
void Viewer::setScale(double value) { scale_ = value; }
void Viewer::setProjectionType(int value) { projection_type_ = value; }
void Viewer::setDataObj(ObjData* data) { data_ = data; }
