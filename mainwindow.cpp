#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "boardview.h"
#include <QMessageBox>
#include <QPixmap>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->board_view, &BoardView::moved, this, &MainWindow::_on_moved);

    ui->complexity_num_sldr->setRange(1, 5);
    ui->complexity_num_sldr->setValue(1);
    ui->complexity_num_sldr->setSingleStep(1);




    _check_back_move_btns(true, false);

    ui->board_view->set_new_model(true, ui->complexity_num_sldr->value());


   // set the icon of mainWindow
    QPixmap pixmap(":/images/icons8-puzzle-pieces-64.png");
    QIcon Icon(pixmap);
   this->setWindowIcon(Icon);
    //set the title of miWindow
    this->setWindowTitle("15 puzzle game");


}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_new_game_btn_clicked() {
    ui->board_view->set_new_model(true, ui->complexity_num_sldr->value());
    _check_back_move_btns(true, false);
   //add con to the button
    QPixmap pixmap(":/images/icons8-new-64.png");
    QIcon ButtonIcon(pixmap);
    ui->new_game_btn->setIcon(ButtonIcon);
}

void MainWindow::on_start_again_btn_clicked() {
    ui->board_view->set_start_board();

        //add icon
    QPixmap pixmap(":/images/icons8-restart-96.png");
    QIcon ButtonIcon(pixmap);

    ui->start_again_btn->setIcon(ButtonIcon);
    _check_back_move_btns();
   }

void MainWindow::on_back_move_btn_clicked() {
    ui->board_view->back_move();
  // add icon
    QPixmap pixmap(":/images/icons8-backward-64.png");
    QIcon ButtonIcon(pixmap);

    ui->back_move_btn->setIcon(ButtonIcon);
    _check_back_move_btns();
}

void MainWindow::_on_moved() {
    _check_back_move_btns();
}

void MainWindow::_check_back_move_btns(const bool manual_mode, const bool value) {
    if (manual_mode) {
        ui->start_again_btn->setEnabled(value);
        ui->back_move_btn->setEnabled(value);
    } else {
        const bool is_back_move_buttons_enabled = ui->board_view->check_back_moves_available();
        ui->start_again_btn->setEnabled(is_back_move_buttons_enabled);
        ui->back_move_btn->setEnabled(is_back_move_buttons_enabled);
    }
}




void MainWindow::on_pushButton_clicked()
{
    int index = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(index+1);







}

void MainWindow::on_pushButton_2_clicked()
{
    auto msgBox= new QMessageBox;
    msgBox->setWindowIcon(QIcon(":/Images/Icon.png"));
        msgBox->setWindowTitle("15 Puzzle");
        msgBox->setText("Are you sure you want to exit?");
        msgBox->setStandardButtons(QMessageBox::Yes);
        msgBox->addButton(QMessageBox::No);
        msgBox->setDefaultButton(QMessageBox::No);

        if(msgBox->exec() == QMessageBox::Yes)
        {
            QApplication::exit();
        }
}





void MainWindow::on_pushButton_3_clicked()
{
    QMessageBox *tutorial = new QMessageBox;


    tutorial->setWindowTitle("How to play");
    tutorial -> setText("The goal of Fifteen Puzzle is to arrange the tiles from 1 to 15 by sliding them one by one into the empty space on the board. The puzzle is considered solved when tile 1 is in the top left corner, tile 2 is to the right of it, and so on, with the empty space on the bottom right.");
    tutorial -> show();
}






void MainWindow::on_pushButton_4_clicked()
{
    int index = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(index-1);
}




