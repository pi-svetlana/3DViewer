#ifndef CPP4_3DVIEWER_V2_0_1_SRC_MAINWINDOW_H
#define CPP4_3DVIEWER_V2_0_1_SRC_MAINWINDOW_H

#include <QColor>
#include <QColorDialog>
#include <QDir>
#include <QDragEnterEvent>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QMimeData>
#include <QMouseEvent>
#include <QSettings>
#include <QTimer>

#include "../controller/controller.h"
#include "../observer/observer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public virtual Observer {
  Q_OBJECT
 public:
  MainWindow(Controller *controller, QWidget *parent = nullptr);
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void update(Context *context) override;

 private slots:
  void on_open_btn_clicked();
  void on_bg_color_btn_clicked();
  void dragEnterEvent(QDragEnterEvent *event) override;
  void dropEvent(QDropEvent *event) override;
  void on_line_color_btn_clicked();
  void on_vertex_color_btn_clicked();
  void setDefaultSettings();
  void saveSettings();
  void loadSettings();

  void on_line_type_currentIndexChanged(int index);
  void on_line_width_valueChanged(int value);
  void on_vertex_type_currentIndexChanged(int index);
  void on_vertex_size_valueChanged(int value);
  void on_projection_type_currentIndexChanged(int index);
  void on_scale_valueChanged(int value);
  void on_rotate_x_valueChanged(int value);
  void on_rotate_y_valueChanged(int value);
  void on_rotate_z_valueChanged(int value);
  void on_move_x_valueChanged(int value);
  void on_move_y_valueChanged(int value);
  void on_move_z_valueChanged(int value);
  void openFile(std::string);
  void changeObjScale(double value);
  void changeObjRotationY(double value);
  void changeObjRotationX(double value);
  void on_save_file_btn_clicked();
  void updateGif();

 private:
  Ui::MainWindow *ui;
  Controller *controller_;
  int old_scale_slider_pos_ = 100;
  int old_move_x_slider_pos_ = 0;
  int old_move_y_slider_pos_ = 0;
  int old_rotation_x_slider_pos = 0;
  int old_rotation_y_slider_pos = 0;
  void createGif();
  void convertGif();
  QTimer timer;
  std::string gifPath;
  int counter;
  double gifTimeStart;
  double gifTimeEnd;
};
#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MAINWINDOW_H
