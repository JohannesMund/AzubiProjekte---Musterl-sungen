#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->cbGameMode->insertItem(0, "Mensch");
  ui->cbGameMode->insertItem(1, "Einfach");
  ui->cbGameMode->insertItem(2, "Mittel");
  ui->cbGameMode->insertItem(3, "Schwer");
  // ui->cbGameMode->insertItem(4, "Optimiert");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::buttonpressed(int i, int j, QPushButton *&Button) {
  if (Feld.setfeld(i, j, Spieler.getspieler())) {
    Button->setStyleSheet("color:" + Spieler.getplayercolor());
    if (Spieler.getspieler() == spieler::X) {
      togglebuttonstatus(Button, "X");
    } else {
      togglebuttonstatus(Button, "O");
    }

    if (Feld.checkwin(i, j, Spieler.getspieler())) {

      ui->lAnzeige->setText("Gewinner Spieler " +
                            QString::number(Spieler.getspieler()));
      // alle Knöpfe deaktivieren
      if (ui->pb1_1->isEnabled()) {
        togglebuttonstatus(ui->pb1_1);
      }
      if (ui->pb1_2->isEnabled()) {
        togglebuttonstatus(ui->pb1_2);
      }
      if (ui->pb1_3->isEnabled()) {
        togglebuttonstatus(ui->pb1_3);
      }
      if (ui->pb2_1->isEnabled()) {
        togglebuttonstatus(ui->pb2_1);
      }
      if (ui->pb2_2->isEnabled()) {
        togglebuttonstatus(ui->pb2_2);
      }
      if (ui->pb2_3->isEnabled()) {
        togglebuttonstatus(ui->pb2_3);
      }
      if (ui->pb3_1->isEnabled()) {
        togglebuttonstatus(ui->pb3_1);
      }
      if (ui->pb3_2->isEnabled()) {
        togglebuttonstatus(ui->pb3_2);
      }
      if (ui->pb3_3->isEnabled()) {
        togglebuttonstatus(ui->pb3_3);
      }
      return;
    }

    if (Spieler.getspieler() == Spieler.getstarter()) {
      Spieler.togglespieler();
      ui->lAnzeige->setText(
          "Runde:" + QString::number(Feld.getrunde()) + "    Spieler " +
          QString::number(Spieler.getspieler()) + " ist am Zug.");
      if (Feld.getrunde() == 5) {
        ui->lAnzeige->setText("Unentschieden");
      }
    } else {
      Spieler.togglespieler();
      Feld.incrunde();
      ui->lAnzeige->setText(
          "Runde:" + QString::number(Feld.getrunde()) + "    Spieler " +
          QString::number(Spieler.getspieler()) + " ist am Zug.");
    }

    if ((Feld.getgamemode() == spielfeld::pve) && (Feld.leeresfeldexists()) &&
        (Spieler.getspieler() == spieler::O)) {
      kimove();
    }
  }
}

void MainWindow::togglebuttonstatus(QPushButton *&Button, QString Text) {
  Button->setFlat(!Button->isFlat());
  Button->setEnabled(!Button->isEnabled());
  Button->setText(Text);
}

void MainWindow::togglebuttonstatus(QPushButton *&Button) {
  Button->setFlat(!Button->isFlat());
  Button->setEnabled(!Button->isEnabled());
}

void MainWindow::togglebuttonstatus(int i, int j) {
  if (i == 0) {
    if (j == 0) {
      buttonpressed(i, j, ui->pb1_1);
    }
    if (j == 1) {
      buttonpressed(i, j, ui->pb1_2);
    }
    if (j == 2) {
      buttonpressed(i, j, ui->pb1_3);
    }
  }
  if (i == 1) {
    if (j == 0) {
      buttonpressed(i, j, ui->pb2_1);
    }
    if (j == 1) {
      buttonpressed(i, j, ui->pb2_2);
    }
    if (j == 2) {
      buttonpressed(i, j, ui->pb2_3);
    }
  }
  if (i == 2) {
    if (j == 0) {
      buttonpressed(i, j, ui->pb3_1);
    }
    if (j == 1) {
      buttonpressed(i, j, ui->pb3_2);
    }
    if (j == 2) {
      buttonpressed(i, j, ui->pb3_3);
    }
  }
}

void MainWindow::kimove() {
  spielfeldcoord coord = Gegner.doMove(Feld, Spieler);
  togglebuttonstatus(coord.x(), coord.y());
}

void MainWindow::on_pb1_1_clicked() { buttonpressed(0, 0, ui->pb1_1); }

void MainWindow::on_pb1_2_clicked() { buttonpressed(0, 1, ui->pb1_2); }

void MainWindow::on_pb1_3_clicked() { buttonpressed(0, 2, ui->pb1_3); }

void MainWindow::on_pb2_1_clicked() { buttonpressed(1, 0, ui->pb2_1); }

void MainWindow::on_pb2_2_clicked() { buttonpressed(1, 1, ui->pb2_2); }

void MainWindow::on_pb2_3_clicked() { buttonpressed(1, 2, ui->pb2_3); }

void MainWindow::on_pb3_1_clicked() { buttonpressed(2, 0, ui->pb3_1); }

void MainWindow::on_pb3_2_clicked() { buttonpressed(2, 1, ui->pb3_2); }

void MainWindow::on_pb3_3_clicked() { buttonpressed(2, 2, ui->pb3_3); }

void MainWindow::on_pbStartGame_clicked() {

  if (!ui->pb1_1->isEnabled()) {
    togglebuttonstatus(ui->pb1_1, "");
  }
  if (!ui->pb1_2->isEnabled()) {
    togglebuttonstatus(ui->pb1_2, "");
  }
  if (!ui->pb1_3->isEnabled()) {
    togglebuttonstatus(ui->pb1_3, "");
  }
  if (!ui->pb2_1->isEnabled()) {
    togglebuttonstatus(ui->pb2_1, "");
  }
  if (!ui->pb2_2->isEnabled()) {
    togglebuttonstatus(ui->pb2_2, "");
  }
  if (!ui->pb2_3->isEnabled()) {
    togglebuttonstatus(ui->pb2_3, "");
  }
  if (!ui->pb3_1->isEnabled()) {
    togglebuttonstatus(ui->pb3_1, "");
  }
  if (!ui->pb3_2->isEnabled()) {
    togglebuttonstatus(ui->pb3_2, "");
  }
  if (!ui->pb3_3->isEnabled()) {
    togglebuttonstatus(ui->pb3_3, "");
  }

  Feld.reset();

  Spieler.setstarter(Spieler.getspieler((std::rand() % 2) + 1));
  Spieler.setspieler(Spieler.getstarter());
  ui->lAnzeige->setText("Runde:" + QString::number(Feld.getrunde()) +
                        "    Spieler " + QString::number(Spieler.getspieler()) +
                        " ist am Zug.");
  if (ui->cbGameMode->currentIndex() == 0) {
    Feld.setspielmodus(spielfeld::pvp);
  } else {
    Feld.setspielmodus(spielfeld::pve);
    Gegner.setSchwierigkeit(ui->cbGameMode->currentIndex() - 1);
    if (Spieler.getstarter() == spieler::O) {
      kimove();
    }
  }
}
