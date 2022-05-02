#include "zahl.h"
#include "math.h"

const int Zahl::Precision = 15;

Zahl::Zahl(const Zahl &c) { *this = c; } // copy constructor

void Zahl::zahlhinzufuegen(int i) { // fügt eine Zahl hinten dran
  if (i == '.') {
    kommagedrueckt = true;
    return;
  }
  if (CheckPrecision()) {
    return;
  }
  if (kommagedrueckt) {
    if (i == 0 && floatpart == 0) {
      vorangehendenullen += 1;
    } else {
      floatpart = floatpart * 10 + i;
    }
  } else {
    integerpart = integerpart * 10 + i;
  }
  wertgegeben = true;
}

bool Zahl::CheckPrecision()
    const { // vergleicht Die Anzahl Zeichen mit der maximal erlaubten Precision

  unsigned int i = CountNumber(integerpart);
  unsigned int f = CountNumber(floatpart);
  if (i + f + vorangehendenullen > Precision) {
    return true;
  } else {
    return false;
  }
}

unsigned int Zahl::CountNumber(
    unsigned long long i) const { // zählt die Anzahl Zeichen (Nummern)

  unsigned int count = 1;
  unsigned long long j = i;
  while (j > 1) {
    j = floor(j / 10);
    count++;
  }
  return count;
}

double Zahl::get() const { // gibt die Zahl als double wieder
  double flt = floatpart;
  double i;
  while (flt >= 1) {
    flt /= 10;
  }
  for (int j = vorangehendenullen; j > 0; j--) {
    flt = flt / 10;
  }
  i = integerpart + flt;
  if (invertiert) {
    i = i * -1;
  }
  return (i);
}

void Zahl::set(double d) { // wandelt die Zahl von nem double in eigenes Format

  Clearnumber();
  integerpart = abs(trunc(d));

  if (d < 0) {
    invertiert = true;
    d = d * -1;
  }
  double dd = d;

  dd = dd - integerpart; // 0,xx um zu schauen ob Kommateil vorhanden
  if (dd > 0) {
    int verbleibendezahlen = Precision - CountNumber(integerpart);

    while (verbleibendezahlen) {
      verbleibendezahlen--;
      dd = dd * 10;   // erhöht den kommateil auf eine ganze Zahl
      if (dd < 1.0) { // wenn kommateil immer noch kleiner als 1, Zahl hat
                      // vorrangehende Nullen
        vorangehendenullen++;
      }
    }

    floatpart = trunc(dd);

    while (floatpart % 10 == 0 &&
           floatpart != 0) { // alle nullen hinten abschneiden
      floatpart = floatpart / 10;
    }
  }

  if (floatpart > 0) {
    kommagedrueckt = true;
  }
  if (floatpart == 0 && vorangehendenullen > 0) {
    vorangehendenullen = 0;
  }
  wertgegeben = true;
}

QString Zahl::toString() const { // wandelt die Zahl in einen String um
  QString nummer = "";
  if (invertiert) {
    nummer = "-";
  }
  nummer = nummer + QString::number(integerpart);

  if (kommagedrueckt) {
    nummer = nummer + ".";
    for (int i = vorangehendenullen; i > 0; i--) {
      nummer = nummer + "0";
    }
  }
  if (floatpart > 0) {
    nummer = nummer + QString::number(floatpart);
  }
  return nummer;
}

void Zahl::letztezahlentfernen() { // entfernt die letzte eingegebene Zahl
  if (kommagedrueckt) {
    if (floatpart > 0) {
      floatpart = floor(floatpart / 10);
    } else if (vorangehendenullen > 0) {
      vorangehendenullen -= 1;
    } else {
      kommagedrueckt = false;
    }
  } else {
    if (integerpart > 0) {
      integerpart = floor(integerpart / 10);
    }
  }
}

void Zahl::Clearnumber() { // setzt alles auf null
  integerpart = 0;
  floatpart = 0;
  vorangehendenullen = 0;
  kommagedrueckt = false;
  invertiert = false;
  wertgegeben = false;
}

void Zahl::invertieren() { invertiert = !invertiert; }

QString Zahl::toBase(int i) {
  QString Ergebnis = "0";
  unsigned long intpart = integerpart;

  double d = floatpart;
  int zs = 0;
  int count = 0;

  if (intpart > 0) { // andere Behandlung für erste Zahl [nur visuell kein
                     // doppelpunkt und kein if in einer while])
    if (i <= 36) {
      Ergebnis = QString::number(intpart % i, i);
    } else {
      Ergebnis = QString::number(intpart % i);
    }
    intpart = intpart / i;
    count++;
  }
  while (intpart > 0) {
    if (i <= 36) {
      Ergebnis =
          QString::number(intpart % i, i) +
          Ergebnis; // Rest wird vornedrangehängt da normal rückwärtsgelesen
    } else {
      Ergebnis = QString::number(intpart % i) + ":" + Ergebnis;
    }
    intpart =
        intpart /
        i; // zahl wird durch i geteilt,ab komma ignoriert (ganzzahldivision)
    count++;
    if (count > 30) {
      return Ergebnis;
    }
  }
  if (d > 0) { // wenn floatpart (d) größer als null n Punkt dranhängen
    Ergebnis = Ergebnis + ".";
    while (d > 1) { // solange größer als 1 durch 10 teilen das man eine 0.xx
                    // zahl erhält
      d = d / 10;
    }
    for (int z = vorangehendenullen; z > 0; z--) { // vorangehendenullen
                                                   // beachten
      d = d / 10;
    }
    d = d * i; // 0.xx wird mal i genommen
    zs = trunc(d);
    if (i <= 36) {
      Ergebnis = Ergebnis + QString::number(zs, i);
      // Zahl vor dem komma wird hinten dran angehängt
    } else {
      Ergebnis = Ergebnis + QString::number(zs);
    }
    d = d - zs; // ganze Zahl wird mit sich selbst abgezogen um 0.xx wieder zu
    // erhalten
    count++;

    while (d > 0) {
      d = d * i;
      zs = trunc(d);
      if (i <= 36) {
        Ergebnis = Ergebnis + QString::number(zs, i);
      } else {
        Ergebnis = Ergebnis + ":" + QString::number(zs);
      }
      d = d - (zs % i);
      count++;
      if (count > 30) {
        return Ergebnis;
      }
    }
  }

  return Ergebnis;
}

void Zahl::operator=(const Zahl &ZW1) {
  vorangehendenullen = ZW1.vorangehendenullen;
  kommagedrueckt = ZW1.kommagedrueckt;
  integerpart = ZW1.integerpart;
  invertiert = ZW1.invertiert;
  floatpart = ZW1.floatpart;
  wertgegeben = true;
}

double Zahl::exponent(const int &ZW1, const int &ZW2) { return pow(ZW1, ZW2); }

void Zahl::operator=(const double ZW1) { set(ZW1); }
double operator+(const Zahl ZW1, const Zahl ZW2) {
  return (ZW1.get() + ZW2.get());
}
double operator+(const double ZW1, const Zahl ZW2) { return (ZW1 + ZW2.get()); }
double operator+(const Zahl ZW1, const double ZW2) { return (ZW1.get() + ZW2); }
double operator-(const Zahl ZW1, const Zahl ZW2) {
  return (ZW1.get() - ZW2.get());
}
double operator/(const Zahl ZW1, const Zahl ZW2) {
  return (ZW1.get() / ZW2.get());
}
double operator/(const Zahl ZW1, const double ZW2) { return (ZW1.get() / ZW2); }
double operator/(const double ZW1, const Zahl ZW2) { return (ZW1 / ZW2.get()); }

double operator*(const Zahl ZW1, const Zahl ZW2) {
  return (ZW1.get() * ZW2.get());
}
double operator*(const Zahl ZW1, const double ZW2) { return (ZW1.get() * ZW2); }
double operator*(const double ZW1, const Zahl ZW2) { return (ZW1 * ZW2.get()); }

double Zahl::exponent(const Zahl &ZW1, const Zahl &ZW2) {
  return (pow(ZW1.get(), ZW2.get()));
}
double Zahl::wurzel(const Zahl ZW1, const Zahl ZW2) {
  return (pow(ZW1.get(), 1 / ZW2.get()));
}

double Zahl::exponent(const Zahl ZW1, const int ZW2) {
  return (pow(
      ZW1.get(),
      ZW2)); // exponentfunktion existiert schon in math.h (sonst for schleife);
}

double Zahl::wurzel(const Zahl ZW1, const int ZW2) {
  return (pow(ZW1.get(), 1 / ZW2)); // wurzel y_/x is gleich x ^ 1/y
}

bool Zahl::wert() { return (wertgegeben); }
