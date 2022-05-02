#ifndef SPIELFELD_H
#define SPIELFELD_H

#include "spieler.h"
#include "spielfeldcoord.h"

class spielfeld {
public:
  spielfeld();
  int getrunde();
  bool setfeld(int i, int j, spieler::Players player);
  bool setfeld(spielfeldcoord v, spieler::Players player);
  spieler::Players getfeld(spielfeldcoord v);
  spieler::Players getfeld(int i, int j);

  bool checkwin(int i, int j, spieler::Players player);
  enum gamemode {
    pvp,
    pve,
  };
  gamemode getgamemode();
  void setspielmodus(gamemode sm);
  void incrunde();
  void reset();
  QVector<spielfeldcoord> getleerefelder() const;
  bool leeresfeldexists();

private:
  bool checkrow(int i, spieler::Players player);
  bool checkcol(int i, spieler::Players player);
  bool checkdiag(int i, int j, spieler::Players player);
  spieler::Players feld[3][3]{{spieler::none, spieler::none, spieler::none},
                              {spieler::none, spieler::none, spieler::none},
                              {spieler::none, spieler::none, spieler::none}};
  int Runde = 1;
  gamemode spielmodus;
};

#endif // SPIELFELD_H
