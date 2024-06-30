#include "mainwindow.h"

#include <QPainter>
#include <QTimer>
#include <iostream>

#include "./ui_mainwindow.h"
#include "gif.h"

MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : MainWindow(parent) {
  controller_ = controller;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  loadSettings();
  connect(ui->gl_model, SIGNAL(changeScale(double)), this,
          SLOT(changeObjScale(double)));
  connect(ui->gl_model, SIGNAL(changeRotationX(double)), this,
          SLOT(changeObjRotationX(double)));
  connect(ui->gl_model, SIGNAL(changeRotationY(double)), this,
          SLOT(changeObjRotationY(double)));
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::on_open_btn_clicked() {
  QString file = QFileDialog::getOpenFileName(
      this, "Выбрать файл", QDir::homePath(), "Obj files (*.obj)");
  std::string file_name = file.toUtf8().toStdString();
  const QFileInfo fileInfo(file);
  if (!file.isEmpty()) {
    ui->file_name->setText(fileInfo.fileName());
    std::string file_name = file.toUtf8().toStdString();
    openFile(file_name);
  }
}

void MainWindow::on_bg_color_btn_clicked() {
  QColor new_bg_color = QColorDialog::getColor(Qt::white, this);
  if (new_bg_color.isValid()) {
    ui->gl_model->setBgColor(new_bg_color);
    ui->gl_model->update();
  }
}

void MainWindow::on_line_color_btn_clicked() {
  QColor new_line_color = QColorDialog::getColor(Qt::white, this);
  if (new_line_color.isValid()) {
    ui->gl_model->setLineColor(new_line_color);
    ui->gl_model->update();
  }
}

void MainWindow::on_line_type_currentIndexChanged(int index) {
  ui->gl_model->setLineType(index);
  ui->gl_model->update();
}

void MainWindow::on_line_width_valueChanged(int value) {
  ui->gl_model->setLineWidth(value);
  ui->gl_model->update();
}

void MainWindow::on_vertex_color_btn_clicked() {
  QColor new_vertex_color = QColorDialog::getColor(Qt::white, this);
  if (new_vertex_color.isValid()) {
    ui->gl_model->setVertexColor(new_vertex_color);
    ui->gl_model->update();
  }
}

void MainWindow::on_vertex_type_currentIndexChanged(int index) {
  ui->gl_model->setVertexType(index);
  ui->gl_model->update();
}

void MainWindow::on_vertex_size_valueChanged(int value) {
  ui->gl_model->setVertexSize(value);
  ui->gl_model->update();
}

void MainWindow::on_projection_type_currentIndexChanged(int index) {
  ui->gl_model->setProjectionType(index);
  ui->gl_model->update();
}

void MainWindow::on_scale_valueChanged(int value) {
  if (ui->gl_model->getDataObj()) {
    int sc = value - old_scale_slider_pos_;
    changeObjScale(sc);
    old_scale_slider_pos_ = value;
  }
}

void MainWindow::changeObjScale(double value) {
  if (value > 0) {
    if (abs(value) + ui->gl_model->getScale() <= 500) {
      controller_->ScaleModel((abs(value) + ui->gl_model->getScale()) /
                              ui->gl_model->getScale());
      ui->gl_model->setScale(ui->gl_model->getScale() + abs(value));
    }
  } else if (value < 0) {
    if (ui->gl_model->getScale() - abs(value) >= 1) {
      controller_->ScaleModel((ui->gl_model->getScale() - abs(value)) /
                              ui->gl_model->getScale());
      ui->gl_model->setScale(ui->gl_model->getScale() - abs(value));
    }
  }
}

void MainWindow::on_rotate_x_valueChanged(int value) {
  if (ui->gl_model->getDataObj()) {
    controller_->RotateModelX(value - ui->gl_model->getRotateX());
    ui->gl_model->setRotateX(value);
  }
}

void MainWindow::on_rotate_y_valueChanged(int value) {
  if (ui->gl_model->getDataObj()) {
    controller_->RotateModelY(value - ui->gl_model->getRotateY());
    ui->gl_model->setRotateY(value);
  }
}

void MainWindow::on_rotate_z_valueChanged(int value) {
  if (ui->gl_model->getDataObj()) {
    controller_->RotateModelZ(value - ui->gl_model->getRotateZ());
    ui->gl_model->setRotateZ(value);
  }
}

void MainWindow::changeObjRotationY(double value) {
  controller_->RotateModelY(value);
}
void MainWindow::changeObjRotationX(double value) {
  controller_->RotateModelX(value);
}

void MainWindow::on_move_x_valueChanged(int value) {
  int move_val = ui->gl_model->getMoveX() + (value - old_move_x_slider_pos_);
  if (move_val <= 100 && move_val >= -100) {
    ui->gl_model->setMoveX(move_val);
    ui->gl_model->update();
  }
  old_move_x_slider_pos_ = value;
}

void MainWindow::on_move_y_valueChanged(int value) {
  int move_val = ui->gl_model->getMoveY() + (value - old_move_y_slider_pos_);
  if (move_val <= 100 && move_val >= -100) {
    ui->gl_model->setMoveY(move_val);
    ui->gl_model->update();
  }
  old_move_y_slider_pos_ = value;
}

void MainWindow::on_move_z_valueChanged(int value) {
  ui->gl_model->setMoveZ(value);
  ui->gl_model->update();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) { event->accept(); }

void MainWindow::dropEvent(QDropEvent *event) {
  const QMimeData *mimeData = event->mimeData();
  if (mimeData->hasUrls()) {
    const QList<QUrl> urlList = mimeData->urls();
    const QString file = urlList.first().toLocalFile();
    const QFileInfo fileInfo(file);
    if (fileInfo.suffix().toLower() == "obj") {
      event->acceptProposedAction();
      ui->file_name->setText(fileInfo.fileName());
      std::string file_name = file.toUtf8().toStdString();
      openFile(file_name);
      return;
    }
  }
  event->ignore();
}

void MainWindow::openFile(std::string file_name) {
  controller_->OpenFile(file_name);
  setDefaultSettings();
}

void MainWindow::update(Context *context) {
  if (!context->message.empty()) {
    ui->gl_model->setDataObj(nullptr);
    QMessageBox::information(this, "ERROR",
                             QString::fromStdString(context->message));
  }
  if (context->object_ != nullptr) {
    ui->gl_model->setDataObj(context->object_);
    ui->num_of_vertex->setText(
        QString::number(ui->gl_model->getDataObj()->vertexes.size()));
    ui->num_of_ribs->setText(
        QString::number(ui->gl_model->getDataObj()->vertex_indexes.size() / 4));
    ui->gl_model->update();
  }
}

void MainWindow::setDefaultSettings() {
  old_scale_slider_pos_ = 100;
  old_move_x_slider_pos_ = 0;
  old_move_y_slider_pos_ = 0;
  old_rotation_x_slider_pos = 0;
  old_rotation_y_slider_pos = 0;
  ui->gl_model->setMoveX(0);
  ui->gl_model->setMoveY(0);
  ui->gl_model->setMoveZ(0);
  ui->gl_model->setRotateX(0);
  ui->gl_model->setRotateY(0);
  ui->gl_model->setRotateZ(0);
  ui->gl_model->setScale(100);
  ui->move_x->setSliderPosition(0);
  ui->move_y->setSliderPosition(0);
  ui->move_z->setSliderPosition(0);
  ui->scale->setSliderPosition(100);
  ui->rotate_x->setSliderPosition(0);
  ui->rotate_y->setSliderPosition(0);
  ui->rotate_z->setSliderPosition(0);
}

void MainWindow::saveSettings() {
  QSettings settings(QCoreApplication::applicationDirPath() + "/settings.ini",
                     QSettings::IniFormat);
  settings.beginGroup("Settings");
  settings.setValue("background_color", ui->gl_model->getBackGroundColor());
  settings.setValue("vertex_color", ui->gl_model->getVertexColor());
  settings.setValue("line_color", ui->gl_model->getLineColor());
  settings.setValue("vertex_size", ui->gl_model->getVertexSize());
  settings.setValue("vertex_type", ui->gl_model->getVertexType());
  settings.setValue("line_width", ui->gl_model->getLineWidth());
  settings.setValue("line_type", ui->gl_model->getLineType());
  settings.setValue("projection_type", ui->gl_model->getProjectionType());
  settings.endGroup();
}

void MainWindow::loadSettings() {
  QSettings settings(QCoreApplication::applicationDirPath() + "/settings.ini",
                     QSettings::IniFormat);
  settings.beginGroup("Settings");
  ui->gl_model->setBgColor(
      settings.value("background_color", QColor(Qt::white)).value<QColor>());
  ui->gl_model->setVertexColor(
      settings.value("vertex_color", QColor(Qt::black)).value<QColor>());
  ui->gl_model->setLineColor(
      settings.value("line_color", QColor(Qt::black)).value<QColor>());
  ui->gl_model->setVertexSize(settings.value("vertex_size", 40).toInt());
  ui->gl_model->setVertexType(settings.value("vertex_type", 0).toInt());
  ui->gl_model->setLineWidth(settings.value("line_width", 40).toInt());
  ui->gl_model->setLineType(settings.value("line_type", 0).toInt());
  ui->gl_model->setProjectionType(settings.value("projection_type", 0).toInt());

  ui->vertex_size->setValue(settings.value("vertex_size", 40).toInt());
  ui->vertex_type->setCurrentIndex(settings.value("vertex_type", 0).toInt());
  ui->line_width->setValue(settings.value("line_width", 40).toInt());
  ui->line_type->setCurrentIndex(settings.value("line_type", 0).toInt());
  ui->projection_type->setCurrentIndex(
      settings.value("projection_type", 0).toInt());
  settings.endGroup();
}

void MainWindow::on_save_file_btn_clicked() {
  std::string file_path;
  std::string filter;
  if (ui->save_file_extension->currentText() == "bmp") {
    file_path = "~/Downloads/file.bmp";
    filter = "Images (*.bmp)";
  } else if (ui->save_file_extension->currentText() == "jpeg") {
    file_path = "~/Downloads/file.jpeg";
    filter = "Images (*.jpeg)";
  } else if (ui->save_file_extension->currentText() == "jpeg") {
    file_path = "~/Downloads/file.gif";
    filter = "Images (*.gif)";
  }

  QString fileName = QFileDialog::getSaveFileName(
      this, "Сохранить файл", QString::fromStdString(file_path),
      filter.c_str());

  if (ui->save_file_extension->currentText() == "jpeg" ||
      ui->save_file_extension->currentText() == "bmp") {
    QImage img(ui->gl_model->size(), QImage::Format_RGB32);
    QPainter painter(&img);
    ui->gl_model->render(&painter);
    img.save(fileName);
  }
  if (ui->save_file_extension->currentText() == "gif") {
    this->gifPath = fileName.toStdString();
    createGif();
  }
}

void MainWindow::createGif() {
  this->gifTimeStart = 0.0;
  this->gifTimeEnd = 100.0;
  this->counter = 0;
  connect(&timer, SIGNAL(timeout()), this, SLOT(updateGif()));
  this->timer.start(static_cast<int>(this->gifTimeEnd));
}
void MainWindow::convertGif() {
  GifWriter creator{};
  try {
    GifBegin(&creator, this->gifPath.c_str(), ui->gl_model->grab().width(),
             ui->gl_model->grab().height(), 10);
    for (int i = 0; i < this->counter; i++) {
      QImage *image = new QImage(QString::fromStdString(
          std::filesystem::temp_directory_path().generic_string() +
          std::to_string(i) + ".jpeg"));

      GifWriteFrame(
          &creator, image->convertToFormat(QImage::Format_RGBA8888).constBits(),
          ui->gl_model->grab().width(), ui->gl_model->grab().height(), 10);
    }
    GifEnd(&creator);
  } catch (std::exception &e) {
    QMessageBox::warning(this, "Save gif", "Something went wrong");
  }
}

void MainWindow::updateGif() {
  if (this->gifTimeStart == this->gifTimeEnd) {
    auto image = ui->gl_model->grabFramebuffer();

    image.save(QString::fromStdString(
        std::filesystem::temp_directory_path().generic_string() +
        std::to_string(this->counter) + ".jpeg"));
    this->counter++;

    this->gifTimeEnd += 100.0;
  }
  if (this->gifTimeStart == 5000) {
    convertGif();
    timer.stop();
    timer.disconnect();
  }
  this->gifTimeStart += 100.0;
}