#include "spielfeld.h"
#include "spieler.h"

#include <QVector>

spielfeld::spielfeld() {}

int spielfeld::getrunde() { return Runde; }

bool spielfeld::setfeld(int i, int j, spieler::Players player) {
  if (feld[i][j] == spieler::none) {
    feld[i][j] = player;
    return true;
  }
  return false;
}

bool spielfeld::setfeld(spielfeldcoord v, spieler::Players player) {
  int i = v.x();
  int j = v.y();
  if (player == spieler::none) {
    feld[i][j] = player;
    return true;
  }
  if (feld[i][j] == spieler::none) {
    feld[i][j] = player;
    return true;
  }
  return false;
}

spieler::Players spielfeld::getfeld(spielfeldcoord v) {
  return feld[v.x()][v.y()];
}

spieler::Players spielfeld::getfeld(int i, int j) { return feld[i][j]; }

bool spielfeld::checkwin(int i, int j, spieler::Players player) {
  if (checkrow(i, player)) {
    return true;
  }
  if (checkcol(j, player)) {
    return true;
  }
  if (checkdiag(i, j, player)) {
    return true;
  }
  return false;
}
spielfeld::gamemode spielfeld::getgamemode() { return spielmodus; }
void spielfeld::setspielmodus(gamemode sm) { spielmodus = sm; }

void spielfeld::incrunde() { Runde++; }

void spielfeld::reset() {
  for (int i = 0; i <= 2; i++) {
    for (int j = 0; j <= 2; j++) {
      feld[i][j] = spieler::Players::none;
    }
  }
  Runde = 1;
}

QVector<spielfeldcoord> spielfeld::getleerefelder() const {
  QVector<spielfeldcoord> v;
  for (int i = 0; i <= 2; i++) {
    for (int j = 0; j <= 2; j++) {
      if (feld[i][j] == spieler::Players::none) {
        v.append(spielfeldcoord{i, j});
      }
    }
  }
  return v;
}

bool spielfeld::leeresfeldexists() {
  if (getleerefelder().isEmpty()) {
    return false;
  } else {
    return true;
  }
}

bool spielfeld::checkrow(int i, spieler::Players player) {
  for (int z = 0; z <= 2; z++) {
    if (feld[i][z] != player) {
      return false;
    }
  }
  return true;
}

bool spielfeld::checkcol(int i, spieler::Players player) {
  for (int z = 0; z <= 2; z++) {
    if (feld[z][i] != player) {
      return false;
    }
  }
  return true;
}

bool spielfeld::checkdiag(int i, int j, spieler::Players player) {
  if ((i == 0 && j == 0) || (i == 2 && j == 2) || (i == 1 && j == 1)) {
    for (int z = 0; z <= 2; z++) {
      if (feld[z][z] != player) {
        return false;
      }
    }
    return true;
  }

  else if (i == 0 && j == 2) {
    for (int z = 0; z <= 2; z++) {
      if (feld[i + z][j - z] != player) {
        return false;
      }
    }
    return true;
  }

  else if (i == 2 && j == 0) {
    for (int z = 0; z <= 2; z++) {
      if (feld[i - z][j + z] != player) {
        return false;
      }
    }
    return true;
  }
  return false;
}
