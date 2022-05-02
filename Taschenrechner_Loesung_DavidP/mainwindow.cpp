#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zahl.h"
#include "math.h"

// bool Kommazahl = false;
// bool Rechenzeichengedrueckt = false;
// double Zahlspeicher = 0.0;
// QString letztesRechenzeichen = "";
// double aktuelleZahl;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // HotKeys

  ui->pbZahl1->setShortcut(QKeySequence(Qt::Key_1));
  ui->pbZahl2->setShortcut(QKeySequence(Qt::Key_2));
  ui->pbZahl3->setShortcut(QKeySequence(Qt::Key_3));
  ui->pbZahl4->setShortcut(QKeySequence(Qt::Key_4));
  ui->pbZahl5->setShortcut(QKeySequence(Qt::Key_5));
  ui->pbZahl6->setShortcut(QKeySequence(Qt::Key_6));
  ui->pbZahl7->setShortcut(QKeySequence(Qt::Key_7));
  ui->pbZahl8->setShortcut(QKeySequence(Qt::Key_8));
  ui->pbZahl9->setShortcut(QKeySequence(Qt::Key_9));
  ui->pbZahl0->setShortcut(QKeySequence(Qt::Key_0));
  ui->pbBackSpace->setShortcut(QKeySequence(Qt::Key_Backspace));
  ui->pbGleich->setShortcut(QKeySequence(Qt::Key_Enter)); // Qt::Key_Return
                                                          // ,Qt::Key_Enter
                                                          // funktioniert nicht
                                                          // so wie gewollt
  ui->pbAddieren->setShortcut(QKeySequence(Qt::Key_Plus));
  ui->pbSubtrahieren->setShortcut(QKeySequence(Qt::Key_Minus));
  ui->pbMultiplizieren->setShortcut(QKeySequence(Qt::Key_Asterisk));
  ui->pbDividieren->setShortcut(QKeySequence(Qt::Key_Slash));
  ui->pbClear->setShortcut(QKeySequence(Qt::Key_C));
  ui->pbAllClear->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
}

MainWindow::~MainWindow() { delete ui; }

// Funktionen

// void MainWindow::Zahlhinzufuegen(QString Zahl) {
//  if (ui->leAnzeige->text() == "0.0" || ui->leAnzeige->text() == "0" ||
//      Rechenzeichengedrueckt) { // Anzeige leeren wenn 0 oder Rechenzeichen
//                                // gedrückt
//    ui->leAnzeige->setText("");
//    Rechenzeichengedrueckt = false;
//  }
//  if (Zahl == ".") {  // differenzierte Behandlung zwischen Punkt und Zahl
//    if (!Kommazahl) { // wenn schonmal Kommazahl gedrückt keinen 2ten Punkt
//      ui->leAnzeige->setText(ui->leAnzeige->text() + Zahl);
//      Kommazahl = true;
//    }
//  } else {
//    ui->leAnzeige->setText(ui->leAnzeige->text() + Zahl);
//  }
//}

// void MainWindow::Rechenaktion(
//    QString Rechenzeichen) { // bestimmt welches Rechenzeichen gedrückt wurde
//                             // und speichert die aktuelle Zahl in eine
//                             Variabel
//  letztesRechenzeichen = Rechenzeichen;
//  Rechenzeichengedrueckt = true;
//  Zahlspeicher = ui->leAnzeige->text().toDouble();
//  Kommazahl = false;
//}

void MainWindow::Rechnen() {
  //  double Ergebnis = 0.0;
  //  if (!Rechenzeichengedrueckt) { // Werte die nur festgelegt werden beim
  //  ersten
  //                                 // mal = drücken (wenn wiederholt)
  //    aktuelleZahl = ui->leAnzeige->text().toDouble();
  //    Kommazahl = false;
  //    Rechenzeichengedrueckt = true;
  //  }
  //  if (letztesRechenzeichen == "+") {
  //    Ergebnis = Zahlspeicher + aktuelleZahl;
  //  } else if (letztesRechenzeichen == "-") {
  //    Ergebnis = Zahlspeicher - aktuelleZahl;
  //  } else if (letztesRechenzeichen == "*") {
  //    Ergebnis = Zahlspeicher * aktuelleZahl;
  //  } else {
  //    Ergebnis = Zahlspeicher / aktuelleZahl;
  //  }
  //  ui->leAnzeige->setText(QString::number(Ergebnis));
  //  Zahlspeicher =
  //      Ergebnis; // Ergebnis in Zahlspeicher speichern für wiederholtes =
  //      drücken

  switch (rechenZeichen) {

  case plus:
    Ergebnis = ZwischenSpeicher + neuezahl;
    break;
  case minus:
    Ergebnis = ZwischenSpeicher - neuezahl;
    break;
  case multiplication:
    Ergebnis = ZwischenSpeicher * neuezahl;
    break;
  case division:
    Ergebnis = ZwischenSpeicher / neuezahl;
    break;
  case power:
    Ergebnis = Ergebnis.exponent(ZwischenSpeicher, neuezahl);
    if (ZwischenSpeicher2.wert()) {
      neuezahl = Ergebnis;
      ZwischenSpeicher = ZwischenSpeicher2;
      rechenZeichen = rechenZeichen2;
      ZwischenSpeicher2.Clearnumber();
      rechenZeichen2 = none;
      Rechnen();
    }
    break;
  case root:
    Ergebnis = Ergebnis.wurzel(ZwischenSpeicher, neuezahl);
    break;
  case percent:
    Ergebnis = (ZwischenSpeicher / neuezahl) * 100;
    break;
  case none:
    ZwischenSpeicher = neuezahl;
    neuezahl.Clearnumber();
    Anzeigeaktualisieren(neuezahl);
    return;
  }
  ZwischenSpeicher =
      Ergebnis; // Ergebnis = neuer ZwischenSPeicher für weiter Kalkulationen
  Anzeigeaktualisieren(Ergebnis);
  eingabe = false;
}

void MainWindow::Invertieren() { // Invertiert die aktuell angezeigte Zahl
  if (eingabe) {
    neuezahl.invertieren();
    Anzeigeaktualisieren(neuezahl);
  } else {
    Ergebnis.invertieren();
    Anzeigeaktualisieren(Ergebnis);
  }
}

void MainWindow::Anzeigeaktualisieren(const Zahl &z1) {
  ui->leAnzeige->setText(
      z1.toString()); // aktualisiert das LineEdit Feld mit der Zahl z1
}

void MainWindow::BaseUmwandeln(int i) {
  if (eingabe) {
    ui->leAnzeige->setText(neuezahl.toBase(i));
  } else {
    ui->leAnzeige->setText(Ergebnis.toBase(i));
  }
}

void MainWindow::setrechenoperator(rechenOperator op) {
  if (eingabe) {
    Rechnen();
  }
  rechenZeichen = op;
  neuezahl.Clearnumber();
}

void MainWindow::addzahl(int i) {
  neuezahl.zahlhinzufuegen(i);
  Anzeigeaktualisieren(neuezahl);
  eingabe = true;
}

void MainWindow::addzahl(char i) {
  neuezahl.zahlhinzufuegen(i);
  Anzeigeaktualisieren(neuezahl);
  eingabe = true;
}

// PushButtons
void MainWindow::on_pbZahl1_clicked() {
  //  Zahlhinzufuegen("1");
  addzahl(1);
}

void MainWindow::on_pbZahl2_clicked() {
  //  Zahlhinzufuegen("2");
  addzahl(2);
}

void MainWindow::on_pbZahl3_clicked() {
  // Zahlhinzufuegen("3");
  addzahl(3);
}

void MainWindow::on_pbZahl4_clicked() {
  //  Zahlhinzufuegen("4");
  addzahl(4);
}

void MainWindow::on_pbZahl5_clicked() {
  // Zahlhinzufuegen("5");
  addzahl(5);
}

void MainWindow::on_pbZahl6_clicked() {
  // Zahlhinzufuegen("6");
  addzahl(6);
}

void MainWindow::on_pbZahl7_clicked() {
  // Zahlhinzufuegen("7");
  addzahl(7);
}

void MainWindow::on_pbZahl8_clicked() {
  // Zahlhinzufuegen("8");
  addzahl(8);
}

void MainWindow::on_pbZahl9_clicked() {
  // Zahlhinzufuegen("9");
  addzahl(9);
}

void MainWindow::on_pbZahl0_clicked() {
  // Zahlhinzufuegen("0");
  addzahl(0);
}

void MainWindow::on_pbZahlPunkt_clicked() {
  // Zahlhinzufuegen(".");
  addzahl('.');
}

void MainWindow::on_pbAddieren_clicked() {
  // Rechenaktion("+");
  setrechenoperator(plus);
}

void MainWindow::on_pbSubtrahieren_clicked() {
  // Rechenaktion("-");
  setrechenoperator(minus);
}

void MainWindow::on_pbMultiplizieren_clicked() {
  // Rechenaktion("*");
  setrechenoperator(multiplication);
}

void MainWindow::on_pbDividieren_clicked() {
  // Rechenaktion("/");
  setrechenoperator(division);
}

void MainWindow::on_pbPowerX_clicked() {
  if (ZwischenSpeicher.wert() && eingabe) {
    ZwischenSpeicher2 = ZwischenSpeicher;
    ZwischenSpeicher = neuezahl;
    rechenZeichen2 = rechenZeichen;
    eingabe = false;
  }

  setrechenoperator(power);
}

void MainWindow::on_pbPower2_clicked() {
  if (ZwischenSpeicher.wert() && eingabe) {
    ZwischenSpeicher2 = ZwischenSpeicher;
    ZwischenSpeicher = neuezahl;
    rechenZeichen2 = rechenZeichen;
    eingabe = false;
  } else if (eingabe == false) {
    ZwischenSpeicher = Ergebnis;
  } else {
    ZwischenSpeicher = neuezahl;
  }
  neuezahl.Clearnumber();
  neuezahl = 2;
  rechenZeichen = power;
  Rechnen();
}

void MainWindow::on_pbSquareRoot_clicked() {
  if (ZwischenSpeicher.wert() && eingabe) {
    ZwischenSpeicher2 = ZwischenSpeicher;
    ZwischenSpeicher = neuezahl;
    rechenZeichen2 = rechenZeichen;
    eingabe = false;
  } else if (eingabe == false) {
    ZwischenSpeicher = Ergebnis;
  } else {
    ZwischenSpeicher = neuezahl;
  }
  neuezahl.Clearnumber();
  neuezahl = 2;
  rechenZeichen = root;
  Rechnen();
}

void MainWindow::on_pbRootX_clicked() {
  if (ZwischenSpeicher.wert() && eingabe) {
    ZwischenSpeicher2 = ZwischenSpeicher;
    ZwischenSpeicher = neuezahl;
    rechenZeichen2 = rechenZeichen;
    eingabe = false;
  }
  setrechenoperator(root);
}

void MainWindow::on_pbProzent_clicked() { setrechenoperator(percent); }

void MainWindow::on_pbGleich_clicked() {
  if (rechenZeichen != none) {
    if (letztezahl.wert() && !neuezahl.wert()) {
      neuezahl = letztezahl;
    }
    Rechnen();
    letztezahl = neuezahl;
    neuezahl.Clearnumber();
  }
}

void MainWindow::on_pbInvertieren_clicked() { Invertieren(); }

void MainWindow::on_pbBackSpace_clicked() {
  ui->leAnzeige->backspace();
  neuezahl.letztezahlentfernen();
  Anzeigeaktualisieren(neuezahl);
}

void MainWindow::on_pbClear_clicked() {
  neuezahl.Clearnumber();
  Anzeigeaktualisieren(neuezahl);
}

void MainWindow::on_pbAllClear_clicked() {
  neuezahl.Clearnumber();
  ZwischenSpeicher.Clearnumber();
  Ergebnis.Clearnumber();
  Anzeigeaktualisieren(neuezahl);
  rechenZeichen = none;
  eingabe = none;
}

void MainWindow::on_pbBase16_clicked() { BaseUmwandeln(16); }

void MainWindow::on_pbBase10_clicked() {
  if (eingabe) {
    Anzeigeaktualisieren(neuezahl);
  } else {
    Anzeigeaktualisieren(Ergebnis);
  }
}

void MainWindow::on_pbBase2_clicked() { BaseUmwandeln(2); }

void MainWindow::on_pbBaseX_clicked() { BaseUmwandeln(ui->sbBaseX->value()); }
