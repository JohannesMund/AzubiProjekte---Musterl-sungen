#ifndef KI_H
#define KI_H
#include "spielfeld.h"
#include "spielfeldcoord.h"
#include "spieler.h"

class ki {
public:
  ki();

private:
  enum Schwierigkeitsgrade {
    Einfach,
    Mittel,
    Schwer,
    Optimiert,
  };
  Schwierigkeitsgrade Schwierigkeit = Einfach;
  spielfeldcoord randomMove(QVector<spielfeldcoord> l);
  spielfeldcoord nonlosingMove(QVector<spielfeldcoord> l, spielfeld &sf);
  spielfeldcoord winningMove(QVector<spielfeldcoord> l, spielfeld &sf);
  spielfeldcoord optimierterMove(QVector<spielfeldcoord> l, spielfeld &sf,
                                 spieler &sp);

public:
  int getSchwierigkeit();
  void setSchwierigkeit(int i);
  spielfeldcoord doMove(spielfeld &aktuell, spieler &sp);
};

#endif // KI_H
