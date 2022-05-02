#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setFlat(true);
    reset();
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::turnToggle()
{
    draw();
    if(isBot){
        checkWon();
        turns++;
        if(turns == 1){
            if(ui->row0col0->text() == "X" || ui->row0col2->text() == "X" || ui->row2col0->text() == "X" || ui->row2col2->text() == "X"){
                ui->row1col1->setText("O");
                matrix[1][1] = 2;
            }else if(ui->row1col1->text() == "X"){
                ui->row0col0->setText("O");
                matrix[0][0] = 2;
            }else{
                ui->row1col1->setText("O");
                matrix[1][1] = 2;
            }
        }else{
            //Check possible win
            int zeroCount = 0;
            int twoCount = 0;
            //Horizontal
            for(int row = 0; row < 3; row++){
                zeroCount = 0;
                twoCount = 0;
                for(int col = 0; col < 3; col++){
                    if(matrix[row][col] == 0){
                        zeroCount++;
                    }else if(matrix[row][col] == 2){
                        twoCount++;
                    }

                    if(zeroCount == 1 && twoCount == 2){
                        for(int i = 0; i < 3; i++){
                            if(matrix[row][i] == 0){
                                matrix[row][i] = 2;
                                setO(row, i);
                                std::cout << "Won1: " << row << " | " << i << std::endl;
                                goto exit;
                            }
                        }
                    }
                }
            }
            //Vertical
            for(int col = 0; col < 3; col++){
                zeroCount = 0;
                twoCount = 0;
                for(int row = 0; row < 3; row++){
                    if(matrix[row][col] == 0){
                        zeroCount++;
                    }else if(matrix[row][col] == 2){
                        twoCount++;
                    }
                    if(zeroCount == 1 && twoCount == 2){
                        std::cout << "?" << std::endl;
                        for(int i = 0; i < 3; i++){
                            std::cout << i << " : " << col << std::endl;
                            if(matrix[i][col] == 0){
                                matrix[i][col] = 2;
                                setO(i, col);
                                std::cout << "Won2: " << i << " | " << col << std::endl;
                                goto exit;
                            }
                        }
                    }
                }
            }
            //Diagonal 1
            zeroCount = 0;
            twoCount = 0;
            for(int row = 0; row < 3; row++){

                if(matrix[row][row] == 0){
                    zeroCount++;
                }else if(matrix[row][row] == 2){
                    twoCount++;
                }
                if(zeroCount == 1 && twoCount == 2){

                    for(int i = 0; i < 3; i++){
                        if(matrix[i][i] == 0){
                            setO(i, i);
                            std::cout << "Won3: " << i << " | " << i << std::endl;
                            goto exit;
                        }
                    }
                }
            }
            //Diagonal 2
            zeroCount = 0;
            twoCount = 0;
            for(int row = 0; row < 3; row++){
                if(matrix[row][2-row] == 0){
                    zeroCount++;
                }else if(matrix[row][2-row] == 2){
                    twoCount++;
                }
                if(zeroCount == 1 && twoCount == 2){

                    for(int i = 0; i < 3; i++){
                        if(matrix[i][2-i] == 0){
                            setO(i, 2-i);
                            std::cout << "Won3: " << i << " | " << 2-i << std::endl;
                            goto exit;
                        }
                    }
                }
            }

            //std::cout << "CheckLose " << std::endl;
            //Check possible lose
            int oneCount;
            //Horizontal
            for(int row = 0; row < 3; row++){
                zeroCount = 0;
                oneCount = 0;
                for(int col = 0; col < 3; col++){
                    if(matrix[row][col] == 0){
                        zeroCount++;
                    }else if(matrix[row][col] == 1){
                        oneCount++;
                    }

                    if(zeroCount == 1 && oneCount == 2){
                        for(int i = 0; i < 3; i++){
                            if(matrix[row][i] == 0){
                                matrix[row][i] = 2;
                                setO(row, i);
                                std::cout << "Lose1: " << row << " | " << i << std::endl;
                                goto exit;
                            }
                        }
                    }
                }
            }
            //Vertical
            for(int col = 0; col < 3; col++){
                zeroCount = 0;
                oneCount = 0;
                //std::cout << "------" << std::endl;
                for(int row = 0; row < 3; row++){
                    //std::cout << "" << row << " " << col << std::endl;
                    if(matrix[row][col] == 0){
                        zeroCount++;
                    }else if(matrix[row][col] == 1){
                        oneCount++;
                    }
                    //std::cout << "-> " << zeroCount << ", " << oneCount << std::endl;
                    if(zeroCount == 1 && oneCount == 2){
                        std::cout << "?" << std::endl;
                        for(int i = 0; i < 3; i++){
                            std::cout << i << " : " << col << std::endl;
                            if(matrix[i][col] == 0){
                                matrix[i][col] = 2;
                                setO(i, col);
                                std::cout << "Lose2: " << i << " | " << col << std::endl;
                                goto exit;
                            }
                        }
                    }
                }
            }
            //Diagonal 1
            zeroCount = 0;
            oneCount = 0;
            for(int row = 0; row < 3; row++){

                if(matrix[row][row] == 0){
                    zeroCount++;
                }else if(matrix[row][row] == 1){
                    oneCount++;
                }
                if(zeroCount == 1 && oneCount == 2){

                    for(int i = 0; i < 3; i++){
                        if(matrix[i][i] == 0){
                            matrix[i][i] = 2;
                            setO(i, i);
                            std::cout << "Lose3: " << i << " | " << i << std::endl;
                            goto exit;
                        }
                    }
                }

            }
            //Diagonal 2 /
            zeroCount = 0;
            oneCount = 0;
            for(int row = 0; row < 3; row++){

                if(matrix[row][2-row] == 0){
                    zeroCount++;
                }else if(matrix[row][2-row] == 1){
                    oneCount++;
                }
                if(zeroCount == 1 && oneCount == 2){

                    for(int i = 0; i < 3; i++){
                        if(matrix[i][2-i] == 0){
                            matrix[i][2-i] = 2;
                            setO(i, 2-i);
                            std::cout << "Lose4: " << i << " | " << 2-i << std::endl;
                            goto exit;
                        }
                    }
                }

            }
            zeroCount = 0;
            twoCount = 0;
            //Horizontal
            for(int row = 0; row < 3; row++){
                zeroCount = 0;
                twoCount = 0;
                for(int col = 0; col < 3; col++){
                    if(matrix[row][col] == 0){
                        zeroCount++;
                    }else if(matrix[row][col] == 2){
                        twoCount++;
                    }

                    if(zeroCount == 2 && twoCount == 1){
                        for(int i = 0; i < 3; i++){
                            if(matrix[row][i] == 0){
                                matrix[row][i] = 2;
                                setO(row, i);
                                std::cout << "set1: " << row << " | " << i << std::endl;
                                goto exit;
                            }
                        }
                    }
                }
            }
            //Vertical
            for(int col = 0; col < 3; col++){
                zeroCount = 0;
                twoCount = 0;
                for(int row = 0; row < 3; row++){
                    if(matrix[row][col] == 0){
                        zeroCount++;
                    }else if(matrix[row][col] == 2){
                        twoCount++;
                    }
                    if(zeroCount == 2 && twoCount == 1){
                        std::cout << "?" << std::endl;
                        for(int i = 0; i < 3; i++){
                            std::cout << i << " : " << col << std::endl;
                            if(matrix[i][col] == 0){
                                matrix[i][col] = 2;
                                setO(i, col);
                                std::cout << "set2: " << i << " | " << col << std::endl;
                                goto exit;
                            }
                        }
                    }
                }
            }
            //Diagonal 1
            zeroCount = 0;
            twoCount = 0;
            for(int row = 0; row < 3; row++){

                if(matrix[row][row] == 0){
                    zeroCount++;
                }else if(matrix[row][row] == 2){
                    twoCount++;
                }
                if(zeroCount == 2 && twoCount == 1){

                    for(int i = 0; i < 3; i++){
                        if(matrix[i][i] == 0){
                            setO(i, i);
                            matrix[i][i] = 2;
                            std::cout << "set3: " << i << " | " << i << std::endl;
                            goto exit;
                        }
                    }
                }
            }
            //Diagonal 2
            zeroCount = 0;
            twoCount = 0;
            for(int row = 0; row < 3; row++){
                if(matrix[row][2-row] == 0){
                    zeroCount++;
                }else if(matrix[row][2-row] == 2){
                    twoCount++;
                }
                if(zeroCount == 2 && twoCount == 1){

                    for(int i = 0; i < 3; i++){
                        if(matrix[i][2-i] == 0){
                            setO(i, 2-i);
                            matrix[i][2-i] = 2;
                            std::cout << "set4: " << i << " | " << 2-i << std::endl;
                            goto exit;
                        }
                    }
                }
            }

            for(int r = 0; r < 3; r++){
                for(int c = 0; c < 3; c++){
                    //std::cout << "ao" << std::endl;
                    if(matrix[r][c] == 0){
                        matrix[r][c] = 2;
                        setO(r, c);
                        std::cout << "Set to: " << r << " | " << c << std::endl;
                        goto exit;
                    }
                }
            }


            exit:

            //std::cout << "Exited" << std::endl;
            turns++;
            draw();
            checkWon();
            if(won || isDraw){
                ui->pushButton->setText("Play again");
                ui->pushButton->setFlat(false);
            }else{
                ui->pushButton->setFlat(true);
            }
            loadMatrix();
        }
    }else{
        turns++;
        if(player1Turn == true){
            player1Turn = false;
        }else if(player1Turn != true){
            player1Turn = true;
        }
        checkWon();
        if(won || isDraw){
            ui->pushButton->setText("Play again");
            ui->pushButton->setFlat(false);
        }else{
            ui->pushButton->setFlat(true);
        }
    }
}

QString MainWindow::getSign()
{
    if(player1Turn){
        return "X";
    }else{
        return "O";
    }
}

bool MainWindow::draw()
{
    std::cout << turns << std::endl;
    if(turns == 8 || turns == 9){
        std::cout << "Draw " << std::endl;
        isDraw = true;
        ui->pushButton->setText("Play again");
        ui->mainLabel->setText("Draw");
        return true;
    }else{
        return false;
    }
}

void MainWindow::reset()
{
    ui->row0col0->setText("");
    ui->row1col0->setText("");
    ui->row2col0->setText("");
    ui->row0col1->setText("");
    ui->row1col1->setText("");
    ui->row2col1->setText("");
    ui->row0col2->setText("");
    ui->row1col2->setText("");
    ui->row2col2->setText("");
    ui->mainLabel->setText("");
    ui->pushButton->setText("");
    won = false;
    player1Turn = true;
    turns = 0;
    isDraw = false;
    ui->pushButton->setFlat(true);
    for(int i = 0; i < 3; i++){
        for(int r = 0; r < 3; r++){
            matrix[i][r] = 0;
        }
    }

}

void MainWindow::checkWon()
{
    QString sign = "X";
    for(int i = 0; i < 2; i++){
        if(i == 1){
            sign = "O";
        }
        if(ui->row0col0->text() == sign && ui->row0col1->text() == sign && ui->row0col2->text() == sign){//1
            won = true;
            if(i == 0){
                ui->mainLabel->setText("Player one wins the game!");
            }else{
                ui->mainLabel->setText("Player two wins the game!");
            }
        }else if(ui->row1col0->text() == sign && ui->row1col1->text() == sign && ui->row1col2->text() == sign){//2
            won = true;
            if(i == 0){
                ui->mainLabel->setText("Player one wins the game!");
            }else{
                ui->mainLabel->setText("Player two wins the game!");
            }
        }else if(ui->row2col0->text() == sign && ui->row2col1->text() == sign && ui->row2col2->text() == sign){//3
            won = true;
            if(i == 0){
                ui->mainLabel->setText("Player one wins the game!");
            }else{
                ui->mainLabel->setText("Player two wins the game!");
            }
        }else if(ui->row0col0->text() == sign && ui->row1col0->text() == sign && ui->row2col0->text() == sign){//4
            won = true;
            if(i == 0){
                ui->mainLabel->setText("Player one wins the game!");
            }else{
                ui->mainLabel->setText("Player two wins the game!");
            }
        }else if(ui->row0col1->text() == sign && ui->row1col1->text() == sign && ui->row2col1->text() == sign){//5
            won = true;
            if(i == 0){
                ui->mainLabel->setText("Player one wins the game!");
            }else{
                ui->mainLabel->setText("Player two wins the game!");
            }
        }else if(ui->row0col2->text() == sign && ui->row1col2->text() == sign && ui->row2col2->text() == sign){//6
            won = true;
            if(i == 0){
                ui->mainLabel->setText("Player one wins the game!");
            }else{
                ui->mainLabel->setText("Player two wins the game!");
            }
        }else if(ui->row0col0->text() == sign && ui->row1col1->text() == sign && ui->row2col2->text() == sign){//7
            won = true;
            if(i == 0){
                ui->mainLabel->setText("Player one wins the game!");
            }else{
                ui->mainLabel->setText("Player two wins the game!");
            }
        }else if(ui->row2col0->text() == sign && ui->row1col1->text() == sign && ui->row0col2->text() == sign){//8
            won = true;
            if(i == 0){
                ui->mainLabel->setText("Player one wins the game!");
            }else{
                ui->mainLabel->setText("Player two wins the game!");
            }
        }
    }

}

void MainWindow::loadMatrix()
{
    std::cout << matrix[0][0] << " | " << matrix[0][1] << " | " <<  matrix[0][2] << std::endl;
    std::cout << matrix[1][0] << " | " << matrix[1][1] << " | " <<  matrix[1][2] << std::endl;
    std::cout << matrix[2][0] << " | " << matrix[2][1] << " | " <<  matrix[2][2] << std::endl;
}

void MainWindow::setO(int row, int col)
{
    if(row == 0){
        if(col == 0){
            ui->row0col0->setText("O");
        }else if(col == 1){
            ui->row0col1->setText("O");
        }else if(col == 2){
            ui->row0col2->setText("O");
        }
    }else if(row == 1){
        if(col == 0){
            ui->row1col0->setText("O");
        }else if(col == 1){
            ui->row1col1->setText("O");
        }else if(col == 2){
            ui->row1col2->setText("O");
        }
    }else if(row == 2){
        if(col == 0){
            ui->row2col0->setText("O");
        }else if(col == 1){
            ui->row2col1->setText("O");
        }else if(col == 2){
            ui->row2col2->setText("O");
        }
    }
}

void MainWindow::on_row0col0_clicked()
{
    if(won || isDraw){
        reset();
    }
    ui->mainLabel->setText("");
    if(ui->row0col0->text() == "X" || ui->row0col0->text() == "O"){
        ui->mainLabel->setText("Please choose a different location");
    }else if(ui->row0col0->text() == ""){
        ui->row0col0->setText(getSign());
        if(getSign() == "X"){
            matrix[0][0] = 1;
        }else{
            matrix[0][0] = 2;
        }
        turnToggle();
    }
}

void MainWindow::on_row0col1_clicked()
{
    if(won){
        reset();
    }
    ui->mainLabel->setText("");
    if(ui->row0col1->text() == "X" || ui->row0col1->text() == "O"){
        ui->mainLabel->setText("Please choose a different location");
    }else if(ui->row0col1->text() == ""){
        ui->row0col1->setText(getSign());
        if(getSign() == "X"){
            matrix[0][1] = 1;
        }else{
            matrix[0][1] = 2;
        }
        turnToggle();
    }
}

void MainWindow::on_row0col2_clicked()
{
    if(won){
        reset();
    }

    ui->mainLabel->setText("");
    if(ui->row0col2->text() == "X" || ui->row0col2->text() == "O"){
        ui->mainLabel->setText("Please choose a different location");
    }else if(ui->row0col2->text() == ""){
        ui->row0col2->setText(getSign());
        if(getSign() == "X"){
            matrix[0][2] = 1;
        }else{
            matrix[0][2] = 2;
        }
        turnToggle();
    }
}

void MainWindow::on_row1col0_clicked()
{
    if(won){
        reset();
    }
    ui->mainLabel->setText("");
    if(ui->row1col0->text() == "X" || ui->row1col0->text() == "O"){
        ui->mainLabel->setText("Please choose a different location");
    }else if(ui->row1col0->text() == ""){
        ui->row1col0->setText(getSign());
        if(getSign() == "X"){
            matrix[1][0] = 1;
        }else{
            matrix[1][0] = 2;
        }
        turnToggle();
    }
}

void MainWindow::on_row1col1_clicked()
{
    if(won){
        reset();
    }
    ui->mainLabel->setText("");
    if(ui->row1col1->text() == "X" || ui->row1col1->text() == "O"){
        ui->mainLabel->setText("Please choose a different location");
    }else if(ui->row1col1->text() == ""){
        ui->row1col1->setText(getSign());
        if(getSign() == "X"){
            matrix[1][1] = 1;
        }else{
            matrix[1][1] = 2;
        }
        turnToggle();
    }
}

void MainWindow::on_row1col2_clicked()
{
    if(won){
        reset();
    }
    ui->mainLabel->setText("");
    if(ui->row1col2->text() == "X" || ui->row1col2->text() == "O"){
        ui->mainLabel->setText("Please choose a different location");
    }else if(ui->row1col2->text() == ""){
        ui->row1col2->setText(getSign());
        if(getSign() == "X"){
            matrix[1][2] = 1;
        }else{
            matrix[1][2] = 2;
        }
        turnToggle();
    }
}

void MainWindow::on_row2col0_clicked()
{
    if(won){
        reset();
    }
    ui->mainLabel->setText("");
    if(ui->row2col0->text() == "X" || ui->row2col0->text() == "O"){
        ui->mainLabel->setText("Please choose a different location");
    }else if(ui->row2col0->text() == ""){
        ui->row2col0->setText(getSign());
        if(getSign() == "X"){
            matrix[2][0] = 1;
        }else{
            matrix[2][0] = 2;
        }
        turnToggle();
    }
}

void MainWindow::on_row2col1_clicked()
{
    if(won){
        reset();
    }
    ui->mainLabel->setText("");
    if(ui->row2col1->text() == "X" || ui->row2col1->text() == "O"){
        ui->mainLabel->setText("Please choose a different location");
    }else if(ui->row2col1->text() == ""){
        ui->row2col1->setText(getSign());
        if(getSign() == "X"){
            matrix[2][1] = 1;
        }else{
            matrix[2][1] = 2;
        }
        turnToggle();
    }
}

void MainWindow::on_row2col2_clicked()
{
    if(won){
        reset();
    }
    ui->mainLabel->setText("");
    if(draw()){
        ui->mainLabel->setText("Draw");
    }else if(ui->row2col2->text() == "X" || ui->row2col2->text() == "O"){
        ui->mainLabel->setText("Please choose a different location");
    }else if(ui->row2col2->text() == ""){
        ui->row2col2->setText(getSign());
        if(getSign() == "X"){
            matrix[2][2] = 1;
        }else{
            matrix[2][2] = 2;
        }
        turnToggle();
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(won || isDraw){
        reset();
    }
}
