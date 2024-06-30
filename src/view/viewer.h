#ifndef CPP4_3DVIEWER_V2_0_1_SRC_VIEWER_H
#define CPP4_3DVIEWER_V2_0_1_SRC_VIEWER_H

#include <QColor>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>

#include "../model/obj_data.h"

class Viewer : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT
 public:
  explicit Viewer(QWidget* parent = nullptr);

  QColor getBackGroundColor();
  QColor getVertexColor();
  QColor getLineColor();
  float getVertexSize();
  int getVertexType();
  float getLineWidth();
  int getLineType();
  double getMoveX();
  double getMoveY();
  double getMoveZ();
  double getRotateX();
  double getRotateY();
  double getRotateZ();
  double getScale();
  int getProjectionType();
  ObjData* getDataObj();

  void setBgColor(QColor);
  void setLineColor(QColor);
  void setVertexColor(QColor);
  void setVertexSize(float value);
  void setVertexType(int value);
  void setLineWidth(float value);
  void setLineType(int value);
  void setMoveX(double value);
  void setMoveY(double value);
  void setMoveZ(double value);
  void setRotateX(double value);
  void setRotateY(double value);
  void setRotateZ(double value);
  void setScale(double value);
  void setProjectionType(int value);
  void setDataObj(ObjData* data);
  void setProjection();
  void wheelEvent(QWheelEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

 signals:
  void changeScale(double value);
  void changeRotationY(double value);
  void changeRotationX(double value);

 private slots:

 private:
  ObjData* data_ = nullptr;
  QColor bg_color_ = Qt::white;
  QColor vertex_color_ = Qt::black;
  QColor line_color_ = Qt::black;

  float vertex_size_;
  int vertex_type_;

  float line_width_;
  int line_type_;

  double move_x_;
  double move_y_;
  double move_z_;

  double rotate_x_;
  double rotate_y_;
  double rotate_z_;

  double scale_;
  int projection_type_;
  int dot_set_ = 65;

  QPoint mouse_position_;
  QPoint new_pos_;
};

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_VIEWER_H
