#include "spielfeldcoord.h"

spielfeldcoord::spielfeldcoord() {}

spielfeldcoord::spielfeldcoord(int x, int y) : QPair<int, int>(x, y) {}

int spielfeldcoord::x() { return first; }
int spielfeldcoord::y() { return second; }
