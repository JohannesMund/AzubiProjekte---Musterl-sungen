#include "ki.h"
#include <QVector>

ki::ki() {}

spielfeldcoord ki::randomMove(QVector<spielfeldcoord> l) {
  std::random_shuffle(l.begin(), l.end());
  return l.first();
}

spielfeldcoord ki::nonlosingMove(QVector<spielfeldcoord> l, spielfeld &sf) {
  QVector<spielfeldcoord> v;
  for (int i = 0; i < l.count(); i++) {
    sf.setfeld(l.value(i), spieler::X);
    if (sf.checkwin(l.value(i).x(), l.value(i).y(), spieler::X)) {
      sf.setfeld(l.value(i), spieler::none);
      v.append(l.value(i));
    }
    sf.setfeld(l.value(i), spieler::none);
  }
  if (v.isEmpty()) {
    return randomMove(l);
  } else
    return randomMove(v);
}

spielfeldcoord ki::winningMove(QVector<spielfeldcoord> l, spielfeld &sf) {

  for (int i = 0; i < l.count(); i++) {
    sf.setfeld(l.value(i), spieler::O);
    if (sf.checkwin(l.value(i).x(), l.value(i).y(), spieler::O)) {
      sf.setfeld(l.value(i), spieler::none);
      return (l.value(i));
    }
    sf.setfeld(l.value(i), spieler::none);
  }
  return nonlosingMove(l, sf);
}

spielfeldcoord ki::optimierterMove(QVector<spielfeldcoord> l, spielfeld &sf,
                                   spieler &sp) {
  QVector<spielfeldcoord> m;
  if (sf.getrunde() == 1) {
    if (sp.getstarter() == sp.O) {
      m.append(l.value(0));
      m.append(l.value(2));
      m.append(l.value(6));
      m.append(l.value(8));
    } else {
      if ((l.indexOf(spielfeldcoord(0, 0)) == -1) ||
          (l.indexOf(spielfeldcoord(2, 2)) == -1) ||
          (l.indexOf(spielfeldcoord(2, 0)) == -1) ||
          (l.indexOf(spielfeldcoord(0, 2)) == -1)) {
        m.append(spielfeldcoord(1, 1));
      } else if (l.indexOf(spielfeldcoord(1, 1)) == -1) {
        m.append(spielfeldcoord(0, 0));
        m.append(spielfeldcoord(0, 2));
        m.append(spielfeldcoord(2, 0));
        m.append(spielfeldcoord(2, 2));
      } else {
        if (l.indexOf(spielfeldcoord(0, 1)) == -1) {
          m.append(spielfeldcoord(0, 0));
          m.append(spielfeldcoord(0, 2));
        } else if (l.indexOf(spielfeldcoord(1, 0)) == -1) {
          m.append(spielfeldcoord(0, 0));
          m.append(spielfeldcoord(2, 0));
        } else if (l.indexOf(spielfeldcoord(1, 2)) == -1) {
          m.append(spielfeldcoord(0, 2));
          m.append(spielfeldcoord(2, 2));
        } else if (l.indexOf(spielfeldcoord(2, 1)) == -1) {
          m.append(spielfeldcoord(2, 0));
          m.append(spielfeldcoord(2, 2));
        } else {
          m.append(spielfeldcoord(0, 0));
          m.append(spielfeldcoord(0, 2));
          m.append(spielfeldcoord(2, 0));
          m.append(spielfeldcoord(2, 2));
        }
      }
    }
  } else if (sf.getrunde() == 2) {
    if (sp.getstarter() == sp.O) {
      if (sf.getfeld(1, 1) == sp.X) {
        if (sf.getfeld(0, 0) == sp.O) {
          return spielfeldcoord(2, 2);
        } else if (sf.getfeld(2, 2) == sp.O) {
          return spielfeldcoord(0, 0);
        } else if (sf.getfeld(0, 2) == sp.O) {
          return spielfeldcoord(2, 0);
        } else if (sf.getfeld(2, 0) == sp.O) {
          return spielfeldcoord(0, 2);
        }
      } else {
      }
    } else {
      if (sf.getfeld(1, 1) == sp.X) {
        return nonlosingMove(l, sf);
      } else if ((sf.getfeld(0, 0) == sp.X && sf.getfeld(2, 2) == sp.X) ||
                 (sf.getfeld(0, 2) == sp.X && sf.getfeld(2, 0) == sp.X)) {
        m.append(spielfeldcoord(0, 1));
        m.append(spielfeldcoord(2, 1));
        m.append(spielfeldcoord(1, 0));
        m.append(spielfeldcoord(1, 2));
      } else if (sf.getfeld(1, 1) == sp.none) {
        return spielfeldcoord(1, 1);
      }
    }

  } else {
    return winningMove(l, sf);
  }
  std::random_shuffle(m.begin(), m.end());
  return (m.first());
}

void ki::setSchwierigkeit(int i) { Schwierigkeit = Schwierigkeitsgrade(i); }

spielfeldcoord ki::doMove(spielfeld &aktuell, spieler &sp) {
  QVector<spielfeldcoord> v = aktuell.getleerefelder();
  if (Schwierigkeit == Optimiert) {
    return optimierterMove(v, aktuell, sp);
  }
  if (Schwierigkeit == Schwer) {
    return winningMove(v, aktuell);
  }
  if (Schwierigkeit == Mittel) {
    return nonlosingMove(v, aktuell);
  }

  return randomMove(v);
}
