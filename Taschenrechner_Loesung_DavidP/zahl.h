#ifndef ZAHL_H
#define ZAHL_H

#include <QString>
#include <QObject>

class Zahl {

public:
  Zahl(){};
  Zahl(const Zahl &c);

  static const int Precision;
  void zahlhinzufuegen(int i);
  bool CheckPrecision() const;
  unsigned int CountNumber(unsigned long long i) const;
  double get() const;
  void set(double d);
  QString toString() const;
  void letztezahlentfernen();
  void Clearnumber();
  void invertieren();
  QString toBase(int i);

  void operator=(const Zahl &ZW1);
  void operator=(const double ZW1);

  double exponent(const Zahl &ZW1, const Zahl &ZW2);
  double exponent(const Zahl ZW1, const int ZW2);
  double exponent(const int &ZW1, const int &ZW2);

  double wurzel(const Zahl ZW1, const Zahl ZW2);
  double wurzel(const Zahl ZW1, const int ZW2);
  bool wert();

private:
  unsigned long long integerpart = 0;
  unsigned long long floatpart = 0;
  int vorangehendenullen = 0;
  bool kommagedrueckt = false;
  bool invertiert = false;
  bool wertgegeben = false;
};

// Overloads
void zahlhinzufuegen(char i);

double operator+(const Zahl ZW1, const Zahl ZW2);
double operator+(const double ZW1, const Zahl ZW2);
double operator+(const Zahl ZW1, const double ZW2);
double operator-(const Zahl ZW1, const Zahl ZW2);
double operator*(const Zahl ZW1, const Zahl ZW2);
double operator*(const Zahl ZW1, const double ZW2);
double operator*(const double ZW1, const Zahl ZW2);
double operator/(const Zahl ZW1, const Zahl ZW2);
double operator/(const Zahl ZW1, const double ZW2);
double operator/(const double ZW1, const Zahl ZW2);

#endif // ZAHL_H
