#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qpushbutton.h"
#include <QMainWindow>
#include "spielfeld.h"
#include "ki.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  spieler Spieler;
  spielfeld Feld;
  ki Gegner;

private slots:

  void on_pb1_1_clicked();

  void on_pb1_2_clicked();

  void on_pb1_3_clicked();

  void on_pb2_1_clicked();

  void on_pb2_2_clicked();

  void on_pb2_3_clicked();

  void on_pb3_1_clicked();

  void on_pb3_2_clicked();

  void on_pb3_3_clicked();

  void on_pbStartGame_clicked();

private:
  void buttonpressed(int i, int j, QPushButton *&Button);
  void togglebuttonstatus(QPushButton *&Button, QString Text);
  void togglebuttonstatus(QPushButton *&Button);
  void togglebuttonstatus(int i, int j);
  void toggleallbuttons();
  void kimove();
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
