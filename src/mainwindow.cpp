#include "mainwindow.h"

#include <iostream>

#include "ui_mainwindow.h"

MainWindow::MainWindow(s21::Controller& controller_arg, QWidget* parent)
    : QMainWindow(parent), controller_(controller_arg), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(geometry().width(), geometry().height());
  ui->info->setReadOnly(true);
  ui->jpeg->setChecked(true);
  settings = new QSettings("3dviewer", "3D_Viewer", this);
  loadSettings();
  ui->openGLWidget->controller_ = &controller_;
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::saveSettings() {
  settings->setValue("background color", ui->bColor->currentIndex());
  settings->setValue("vertex color", ui->vColor->currentIndex());
  settings->setValue("facet color", ui->fColor->currentIndex());
  settings->setValue("vertex size", ui->vSize->value());
  settings->setValue("facet width", ui->fWidth->value());
  settings->setValue("vertex type", ui->vType->currentIndex());
  settings->setValue("facet type", ui->fType->currentIndex());
  settings->setValue("projection type", ui->pType->currentIndex());
}

void MainWindow::loadSettings() {
  ui->bColor->setCurrentIndex(settings->value("background color", "0").toInt());
  ui->vColor->setCurrentIndex(settings->value("vertex color", "0").toInt());
  ui->fColor->setCurrentIndex(settings->value("facet color", "0").toInt());
  ui->vSize->setValue(settings->value("vertex size", "1").toInt());
  ui->fWidth->setValue(settings->value("facet width", "1").toInt());
  ui->vType->setCurrentIndex(settings->value("vertex type", "0").toInt());
  ui->fType->setCurrentIndex(settings->value("facet type", "0").toInt());
  ui->pType->setCurrentIndex(settings->value("projection type", "0").toInt());
}

void MainWindow::on_file_button_clicked() {
  on_CLEAN_clicked();
  ui->openGLWidget->xRot = 0.;
  ui->openGLWidget->yRot = 0.;
  ui->info->clear();
  QString full_filename = QFileDialog::getOpenFileName(
      this, "Choose file...", QDir::homePath(), "*.obj");
  on_applySettings_clicked();
  std::string filename = full_filename.toStdString();
  controller_.ReadFile(filename);
  ui->info->setText(QString::fromStdString(controller_.get_state_info()));
}

void MainWindow::on_OK_clicked() {
  float x_rot = ui->rotate_x->text().toFloat(),
        y_rot = ui->rotate_y->text().toFloat(),
        z_rot = ui->rotate_z->text().toFloat();
  float x_move = ui->move_x->text().toFloat(),
        y_move = ui->move_y->text().toFloat(),
        z_move = ui->move_z->text().toFloat();
  float scale = ui->scale->text().toFloat();
  controller_.rotate(x_rot, y_rot, z_rot);
  controller_.move(x_move, y_move, z_move);
  controller_.scale(scale);
  ui->openGLWidget->update();
}

void MainWindow::on_CLEAN_clicked() {
  ui->move_x->setValue(0.0);
  ui->move_y->setValue(0.0);
  ui->move_z->setValue(0.0);
  ui->rotate_x->setValue(0.0);
  ui->rotate_y->setValue(0.0);
  ui->rotate_z->setValue(0.0);
  ui->scale->setValue(1.0);
}

void MainWindow::on_saveImage_clicked() {
  QString filename;
  if (ui->jpeg->isChecked()) {
    filename = QFileDialog::getSaveFileName(this, "Save as..", "name.jpeg",
                                            "JPEG (*.jpeg *.jpg)");
  } else if (ui->bmp->isChecked()) {
    filename = QFileDialog::getSaveFileName(this, "Save as..", "name.bmp",
                                            "BMP (*.bmp)");
  }
  ui->openGLWidget->grabFramebuffer().save(filename, nullptr, 100);
}

void MainWindow::on_applySettings_clicked() {
  ui->openGLWidget->backColor = ui->bColor->currentIndex();
  ui->openGLWidget->vertexColor = ui->vColor->currentIndex();
  ui->openGLWidget->facetColor = ui->fColor->currentIndex();
  ui->openGLWidget->pointSize = ui->vSize->value();
  ui->openGLWidget->facetWigth = ui->fWidth->value();
  ui->openGLWidget->vertexType = ui->vType->currentIndex();
  ui->openGLWidget->facetType = ui->fType->currentIndex();
  ui->openGLWidget->pType = ui->pType->currentIndex();
  ui->openGLWidget->update();
}

void MainWindow::on_defaultSettings_clicked() {
  ui->bColor->setCurrentIndex(0);
  ui->vColor->setCurrentIndex(0);
  ui->fColor->setCurrentIndex(0);
  ui->vSize->setValue(1);
  ui->fWidth->setValue(1);
  ui->vType->setCurrentIndex(0);
  ui->fType->setCurrentIndex(0);
  ui->pType->setCurrentIndex(0);
}

void MainWindow::on_RESET_clicked() {
  ui->openGLWidget->xRot = 0.;
  ui->openGLWidget->yRot = 0.;
  ui->openGLWidget->update();
}
