#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "zahl.h"
#include <QMainWindow>

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

private slots:

  void on_pbZahl1_clicked();

  void on_pbZahl2_clicked();

  void on_pbZahl3_clicked();

  void on_pbZahl4_clicked();

  void on_pbZahl5_clicked();

  void on_pbZahl6_clicked();

  void on_pbZahl7_clicked();

  void on_pbZahl8_clicked();

  void on_pbZahl9_clicked();

  void on_pbZahl0_clicked();

  void on_pbZahlPunkt_clicked();

  void on_pbAddieren_clicked();

  void on_pbSubtrahieren_clicked();

  void on_pbMultiplizieren_clicked();

  void on_pbDividieren_clicked();

  void on_pbGleich_clicked();

  void on_pbInvertieren_clicked();

  void on_pbBackSpace_clicked();

  void on_pbClear_clicked();

  void on_pbAllClear_clicked();

  void on_pbBase16_clicked();

  void on_pbBase10_clicked();

  void on_pbBase2_clicked();

  void on_pbBaseX_clicked();

  void on_pbPower2_clicked();

  void on_pbPowerX_clicked();

  void on_pbRootX_clicked();

  void on_pbSquareRoot_clicked();

  void on_pbProzent_clicked();

private:
  Ui::MainWindow *ui;

  //  void Zahlhinzufuegen(QString Zahl);

  // void Rechenaktion(QString Rechenzeichen);

  void Rechnen();

  void Invertieren();

  void Anzeigeaktualisieren(const Zahl &Z1);

  void BaseUmwandeln(int i);

  enum rechenOperator {
    none,
    plus,
    minus,
    division,
    multiplication,
    power,
    root,
    percent,
  };

  void setrechenoperator(rechenOperator op);

  rechenOperator rechenZeichen = none; // speichert den letzten rechenoperator;
  rechenOperator rechenZeichen2 = none;
  bool eingabe = false; // legt fest ob eine Zahl oder . eingegeben wurde
  void addzahl(int i);

  void addzahl(char i);

  Zahl neuezahl;
  Zahl ZwischenSpeicher;
  Zahl Ergebnis;
  Zahl letztezahl;
  Zahl ZwischenSpeicher2;
};
#endif // MAINWINDOW_H
