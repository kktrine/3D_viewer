#include <QApplication>

#include "headers/Controller.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  setenv("LC_NUMERIC", "C", 1);
  QApplication a(argc, argv);
  s21::Controller controller;
  MainWindow w(controller);

  w.show();
  return a.exec();
}
