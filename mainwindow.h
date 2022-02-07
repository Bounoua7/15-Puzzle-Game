#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_new_game_btn_clicked();

    void on_start_again_btn_clicked();

    void on_back_move_btn_clicked();

    void _on_moved();



    void on_pushButton_clicked();

    void on_pushButton_2_clicked();



    void on_pushButton_3_clicked();





    void on_pushButton_4_clicked();




private:
    void _check_back_move_btns(const bool manual_mode = false, const bool value = true);

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
