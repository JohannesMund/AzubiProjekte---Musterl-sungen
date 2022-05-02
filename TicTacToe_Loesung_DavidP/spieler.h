#ifndef SPIELER_H
#define SPIELER_H
#include <QString>

class spieler {
public:
  spieler();

  enum Players {
    none,
    X,
    O,
  };

  Players getspieler() const;
  Players getspieler(int i) const;
  void setspieler(Players spieler);
  void togglespieler();
  void setstarter(Players spieler);
  Players getstarter();
  QString getplayercolor();

private:
  Players Spieler;
  Players Starter;
};

#endif // SPIELER_H
