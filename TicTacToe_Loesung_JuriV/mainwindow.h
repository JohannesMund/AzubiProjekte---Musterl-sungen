#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool player1Turn = true;
    void turnToggle();
    int turns = 0;
    QString getSign();
    bool draw();
    void reset();
    void checkWon();
    void loadMatrix();
    int matrix[3][3];
    void setO(int, int);



private slots:
    void on_row0col0_clicked();

    void on_row0col1_clicked();

    void on_row0col2_clicked();

    void on_row1col0_clicked();

    void on_row1col1_clicked();

    void on_row1col2_clicked();

    void on_row2col0_clicked();

    void on_row2col1_clicked();

    void on_row2col2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    bool won = false;
    bool isDraw = false;
    bool isBot = true;
};
#endif // MAINWINDOW_H
