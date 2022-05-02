#include "spieler.h"

spieler::spieler() {}

spieler::Players spieler::getspieler() const { return Spieler; }

spieler::Players spieler::getspieler(int i) const { return Players(i); }

void spieler::setspieler(Players spieler) { Spieler = spieler; }

void spieler::togglespieler() {
  if (Spieler == X) {
    setspieler(O);
  } else {
    setspieler(X);
  }
}

void spieler::setstarter(Players spieler) { Starter = spieler; }

spieler::Players spieler::getstarter() { return Starter; }

QString spieler::getplayercolor() {
  if (Spieler == X) {
    return "blue";
  } else {
    return "red";
  }
}
