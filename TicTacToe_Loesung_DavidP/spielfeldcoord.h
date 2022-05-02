#ifndef SPIELFELDCOORD_H
#define SPIELFELDCOORD_H
#include "qpair.h"

struct spielfeldcoord : public QPair<int, int> {
public:
  spielfeldcoord();
  spielfeldcoord(int x, int y);
  int x();
  int y();
};

#endif // SPIELFELDCOORD_H
