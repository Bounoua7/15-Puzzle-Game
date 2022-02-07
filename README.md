


<h1 style="color:#0B615E;  text-align:center; vertical-align: middle; padding:40px 0; margin-top:30px " > Fifteen Puzzle Game Project </h1>
             </br>
<h4 style="background-color:#F6CEF5" > <a id="up-id" >Realized by: BOUNOUA Oum Koulthoume,      EL IDRISSI Rkia   </a> </h4>

<h2 style="color:#0B615E;">
<li> <a href="#Todo-id">15 Puzzle game</a></li>   
  

</h2>
<h4 style="color:#088A85;">
  


<ul>
<h3 style="color:#58ACFA";>
 <h4> <a href="#Preface-id">Preface</a></h4>
 <h4> <a href="#classes-id">Creating classes</a></h4>
 <h4> <a href="#Interface-id">Interface</a> </h4> 
 <h4> <a href="#result-id">The result </a></h4>
  <h4> <a href="#conclusion-id"> Conclusion  </a></h4>


</h3>
</ul>
      
------------
   <h3 style="color:#088A85" id="Preface-id" >Preface </h3>
   The aim of this project is to create an application in c++ using Qt.
Our group consists of two people.
We chose to create a "puzzle game" and we have as a constraint a deadline of 4 weeks. 
</h4>
</br>
<strong>Fifteen puzzle Game</strong>  is a sliding puzzle having 15 square tiles numbered from 1 to 15 in a frame that is 4 tiles high and 4 tiles wide, leaving one unoccupied tile position.</br>
Tiles in the same row or column of the open position can be moved by sliding them horizontally or vertically, respectively. The goal of the puzzle is to place the tiles in numerical order.

<strong>The goal</strong> of our project is to create the puzzle game. It has all the features of main application . The game contains a level range for complexity of resolution from 1 to 5, buttons for restartnig, the guide that explain how to play, one to return back..


------------


   <h3 style="color:#088A85" id="classes-id" >Creating Classes </h3>
   <p>
We add three classes to the mainwindow class :

<li>A board Model contains functions ressponsible of squares move, direction and permutations.</li>

<li>A board View is for the creation of the board and the fifteen pushbuttons .</li>
<li>A fifteenpushbutton class contains functions responsible of changing the displayed numbers on the buttons, such as  int get_num(),set_num(int num) ,get_idx(), set_idx()..</li>
   </p>

  <h3 style="color:#088A85" id="Interface-id" >Interface</h3>
   <p>
<li>
 In QT designer we created two interfaces using <strong>stacked widget</strong>  that contains two pages, the first displays the home game with three pushButtons:  how te play the game(about the puzzle game) , Start the game (play) , Exit(to quit the app).
 The second page displays the board of the 15 squares  with the pushButtons: scramble( squares permutation) , back (back to the previous move),Restart the game.</li>

   </p>
Our GUI looks like this: 

page1

![page1](https://user-images.githubusercontent.com/86807424/152706194-0a5cd791-6669-4bea-9eaf-cce02408e8f5.png)


page2

![page2](https://user-images.githubusercontent.com/86807424/152706660-08766c78-eb73-436c-89b3-d8ecb09f9e63.png)


</p>


------------
   <h3 style="color:#088A85" id="Todo-id" >15 puzzle game Code</h3>


<h5 style="color:#FF8000"> The main class code</h5>

```c++

#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile style(":/style.qss");
    style.open(QFile::ReadOnly);
    const QString style_sheet = style.readAll();
    style.close();

    MainWindow w;
    w.setStyleSheet(style_sheet);
    w.show();

    return a.exec();
}



```
<h5 style="color:#FF8000">mainwindow.h file:</h5>


```c++
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



```
<h5 style="color:#FF8000">mainwindow.cpp file:</h5>

```c++
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







 ```











   <h3 style="color:#088A85;" id="spreadsheet-id" > Board Model class  </h3>






<h5 style="color:#FF8000"> Boardmodel.h file:</h5>

```c++

#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QVector>
#include <QVariant>
#include <QPair>
#include <QStack>

// modèle de jeu
class BoardModel {
public:
    // The size of the game box side
    static constexpr int GAME_SHAPE = 4;

    // board size
    static constexpr int GAME_SIZE = GAME_SHAPE * GAME_SHAPE;

    // empty element
    static constexpr int EMPTY_ELEMENT = 0;

    BoardModel();

    // is_rnd -  to create a random arrangement or not
    // complexity  - complexity of the generated arrangement
    BoardModel(const bool is_rnd, const int complexity);

    // check if the task is solved
    // if yes then return the number of permutations
    QPair<bool, QVariant> is_solved() const noexcept;

    // get board
    const QVector<int>& get_board() const noexcept;

    // check whether it is possible
    // start a new game or take a step back
    bool check_back_moves_available() const noexcept;

    // back to the original arrangement
    void set_start_board() noexcept;

    // set a new layout
    void set_new_board(const bool is_rnd, const int complexity);

    // make a permutation
  //  if the permutation is made to return
    // index of the empty cell that was rearranged
    // idx - index of the item to be rearranged
    QPair<bool, QVariant> move(const int idx);

    // go back a step back
    // if successful, return the indexes of the items
    // which swapped places
    QPair<bool, QPair<QVariant, QVariant>> back_move() noexcept;

private:
    enum class DIRECTION {
        UP = 1,
        DOWN,
        LEFT,
        RIGHT
    };

    // complexity coefficient
    static constexpr int _COMPLEXITY_COEF = 10;

    // coefficient of the number of steps to solve the problem
    static constexpr int _SHIFTS_PER_STEP_COEF = 100;

    // count the number of permutations
    // by relative complexity
    static int _compute_actual_complexity(const int complexity);

    // get a random direction
    static DIRECTION _gen_direction() noexcept;

    // check whether it is possible to rearrange in this direction
    static bool _check_direction(const int nul_idx, const DIRECTION direction) noexcept;

    // check whether the item is by index rhs
    // neighbor of the element by index lhs in that direction
    static bool _check_is_neighbour(const int lhs, const int rhs, const DIRECTION direction) noexcept;

    // make a permutation if possible
    static bool _make_move(QVector<int>& board, int& nul_idx, const DIRECTION direction) noexcept;

    // get the solved permutation
    static QVector<int> _get_solved_board();

    // check if the arrangement is resolved
    // board - arrangement for verification
    static bool _check_solved(const QVector<int>& board) noexcept;

    // generate an arrangement
    // complexity - complexity of the generated arrangement
    static QPair<QVector<int>, int> _gen_board(const int num_shifts);

    // auxiliary function for
    // random arrangement initialization
    void init_random(const int complexity);

    QVector<int>              _board;             // arrangement
    int                       _nul_index;         // index of an empty item
    bool                      _is_solved;         // has the arrangement been resolved

    QVector<int>              _start_board;       // Initial placement
    int                       _start_nul_index;   // initial index of an empty item
    bool                      _start_is_solved;   // whether the initial arrangement has been resolved

    int                       _num_shifts;        // Number of permutations made
    QStack<QPair<int, int>>   _states;            // history of permutations
};

#endif // BOARDMODEL_H


```

<h5 style="color:#FF8000">boardmodel.cpp file:</h5> 


```c++
#include <QRandomGenerator>
#include <QtMath>

#include "boardmodel.h"

BoardModel::BoardModel()
    : _board(_get_solved_board()),
      _nul_index(GAME_SIZE - 1),
      _is_solved(true),
      _start_board(_board),
      _start_nul_index(_nul_index),
      _start_is_solved(_is_solved),
      _num_shifts(0),
      _states{} {}

BoardModel::BoardModel(const bool is_rnd, const int complexity)
    : BoardModel() {
    if (is_rnd) {
        init_random(complexity);
    }
}

QPair<bool, QVariant> BoardModel::is_solved() const noexcept {
    if (_is_solved) {
        return {true, QVariant(_num_shifts)};
    } else {
        return {false, QVariant()};
    }
}

const QVector<int>& BoardModel::get_board() const noexcept {
    return _board;
}

void BoardModel::set_start_board() noexcept{
    if (_num_shifts != 0) {
        _board      = _start_board;
        _nul_index  = _start_nul_index;
        _is_solved  = _start_is_solved;
        _num_shifts = 0;
        _states.clear();
    }
}

void BoardModel::set_new_board(const bool is_rnd, const int complexity) {
    if (is_rnd) {
        init_random(complexity);
    } else {
        _board           = _get_solved_board();
        _nul_index       = GAME_SIZE - 1;
        _is_solved       = true;

        _start_board     = _board;
        _start_nul_index = _nul_index;
        _start_is_solved = _is_solved;

        _num_shifts      = 0;
        _states.clear();
    }
}

void BoardModel::init_random(const int complexity) {
    const int actual_complexity = _compute_actual_complexity(complexity);
    const int predicted_max_num_shifts = actual_complexity * _SHIFTS_PER_STEP_COEF;

    if (_states.capacity() < predicted_max_num_shifts) {
        _states.reserve(predicted_max_num_shifts);
    }

    bool continue_generating = true;
    while (continue_generating) {
        const auto rnd_result = _gen_board(actual_complexity);
        const auto board      = rnd_result.first;
        const auto nul_index  = rnd_result.second;

        const auto is_solved  = _check_solved(board);
        continue_generating   = is_solved;

        if (!is_solved) {
            _board            = board;
            _nul_index        = nul_index;
            _is_solved        = is_solved;

            _start_board      = _board;
            _start_nul_index  = _nul_index;
            _start_is_solved  = _is_solved;
        }
    }
}

QPair<bool, QVariant> BoardModel::move(const int idx) {
    bool result = false;
    const int swap_idx = _nul_index;

    if (_check_is_neighbour(_nul_index, idx, DIRECTION::UP)) {
        result = _make_move(_board, _nul_index, DIRECTION::UP);
    } else if (_check_is_neighbour(_nul_index, idx, DIRECTION::DOWN)) {
        result = _make_move(_board, _nul_index, DIRECTION::DOWN);
    } else if (_check_is_neighbour(_nul_index, idx, DIRECTION::LEFT)) {
        result = _make_move(_board, _nul_index, DIRECTION::LEFT);
    } else if (_check_is_neighbour(_nul_index, idx, DIRECTION::RIGHT)) {
        result = _make_move(_board, _nul_index, DIRECTION::RIGHT);
    }

    if (result) {
        _is_solved = _check_solved(_board);
        _num_shifts++;
        _states.push({idx, swap_idx});

        return {true, QVariant(swap_idx)};
    } else {
        return {false, QVariant()};
    }
}

QPair<bool, QPair<QVariant, QVariant> > BoardModel::back_move() noexcept {
    if (!_states.empty()) {
        const auto prev = _states.pop();
        qSwap(_board[prev.first], _board[prev.second]);
        _nul_index = prev.second;
        _num_shifts--;
        _is_solved = _check_solved(_board);

        return {true, {QVariant(prev.first), QVariant(prev.second)}};
    } else {
        return {false, {QVariant(), QVariant()}};
    }
}

int BoardModel::_compute_actual_complexity(const int complexity) {
    const int complexity_num = complexity * _COMPLEXITY_COEF;
    return qFloor(complexity_num * qLn(complexity_num));
}

QPair<QVector<int>, int> BoardModel::_gen_board(const int num_shifts) {
    auto final_state = _get_solved_board();
    int nul_index = GAME_SIZE - 1;

    for (int i = 0; i < num_shifts; i++) {
        _make_move(final_state, nul_index, _gen_direction());
    }

    return {final_state, nul_index};
}

bool BoardModel::_check_direction(const int nul_idx, const DIRECTION direction) noexcept {
    if (direction == DIRECTION::UP) {
        return nul_idx > GAME_SHAPE - 1;
    } else if (direction == DIRECTION::DOWN) {
        return nul_idx < GAME_SIZE - GAME_SHAPE;
    } else if (direction == DIRECTION::LEFT) {
        return  nul_idx % GAME_SHAPE != 0;
    } else if (direction == DIRECTION::RIGHT) {
        return nul_idx % GAME_SHAPE != GAME_SHAPE - 1;
    }

    return false;
}

bool BoardModel::_check_is_neighbour(const int lhs, const int rhs, const DIRECTION direction) noexcept {
    switch (direction) {
        case DIRECTION::UP:
             return lhs - GAME_SHAPE == rhs;
        case DIRECTION::DOWN:
            return  lhs + GAME_SHAPE == rhs;
        case DIRECTION::LEFT:
            return lhs - 1 == rhs;
        case DIRECTION::RIGHT:
            return lhs + 1 == rhs;
        default:
            return false;
    }
}

bool BoardModel::_make_move(QVector<int>& board, int& nul_idx, const DIRECTION direction) noexcept {
    if (_check_direction(nul_idx, direction)) {
        if (direction == DIRECTION::UP) {
            qSwap(board[nul_idx], board[nul_idx - GAME_SHAPE]);
            nul_idx -= GAME_SHAPE;
        } else if (direction == DIRECTION::DOWN) {
            qSwap(board[nul_idx], board[nul_idx + GAME_SHAPE]);
            nul_idx += GAME_SHAPE;
        } else if (direction == DIRECTION::LEFT) {
            qSwap(board[nul_idx], board[nul_idx - 1]);
            nul_idx--;
        } else if (direction == DIRECTION::RIGHT) {
            qSwap(board[nul_idx], board[nul_idx + 1]);
            nul_idx++;
        }

        return true;
    } else {
        return false;
    }
}

BoardModel::DIRECTION BoardModel::_gen_direction() noexcept {
    auto gen = QRandomGenerator::global();
    switch (gen->bounded(1, 5)) {
        case 1:
            return DIRECTION::UP;
        case 2:
            return DIRECTION::DOWN;
        case 3:
            return DIRECTION::LEFT;
        case 4:
            return DIRECTION::RIGHT;
    }
}

QVector<int> BoardModel::_get_solved_board() {
    QVector<int> final_state(GAME_SIZE);
    for (int i = 0; i < GAME_SIZE; i++) {
        final_state[i] = i + 1;
    }
    final_state[GAME_SIZE - 1] = EMPTY_ELEMENT;

    return final_state;
}

bool BoardModel::_check_solved(const QVector<int>& board) noexcept {
    int num_invs = 0;

    for (int i = 0; i < GAME_SIZE; i++) {
        if (board[i] != (i + 1) % GAME_SIZE) {
            num_invs++;
        }
    }

    return num_invs == 0;
}

bool BoardModel::check_back_moves_available() const noexcept {
    return _num_shifts != 0;
}


```

   <h3 style="color:#088A85;" id="spreadsheet-id" > Board View class  </h3>


<h5 style="color:#FF8000"> BoardView.h file:</h5>

```C++
#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include "boardmodel.h"
#include "fifteenpushbutton.h"

// game view
class BoardView : public QWidget
{
    Q_OBJECT
public:
    explicit BoardView(QWidget *parent = nullptr);
    ~BoardView();

    // set a new layout
    // is_rnd - create a random arrangement or not
    // complexity - complexity of the generated arrangement
    void set_new_model(bool is_rnd, int complexity);

    // set the initial arrangement
    void set_start_board();

    // take a step back
    void back_move();

    // check whether it is possible
    // start a new game or take a step back
    bool check_back_moves_available();

signals:
    void moved();

private:

    // check if the arrangement is resolved
    // if yes to output the result
    void check_game_end();

    QGridLayout*                grid;    // layout for buttons - game elements
    BoardModel*                 model;   // game model
    QVector<FifteenPushButton*> buttons; // buttons - game elements

private slots:

    // game button pressed
    // if it is possible to make a permutation
    // idx - button index
    void move(int idx);
};

#endif // BOARDVIEW_H


```

<h5 style="color:#FF8000"> BoardView.cpp file:</h5>


```c++

#include <QString>
#include <QMessageBox>

#include "boardview.h"

BoardView::BoardView(QWidget *parent)
    : QWidget(parent),
      grid(nullptr),
      model(nullptr),
      buttons(BoardModel::GAME_SIZE, nullptr) {}

BoardView::~BoardView() {
    delete model;
}

void BoardView::set_new_model(bool is_rnd, int complexity) {
    if (model == nullptr) {
        model = new BoardModel(is_rnd, complexity);
    } else {
        model->set_new_board(is_rnd, complexity);
    }

    if (grid == nullptr) {
        grid = new QGridLayout(this);

        for (int i = 0; i < BoardModel::GAME_SIZE; i++) {
            auto new_btn = new FifteenPushButton(this);
            new_btn->set_idx(i);
            grid->addWidget(new_btn, i / BoardModel::GAME_SHAPE, i % BoardModel::GAME_SHAPE);
            connect(new_btn, &FifteenPushButton::fifteen_btn_clicked, this, &BoardView::move);
            buttons[i] = new_btn;
        }

        setLayout(grid);
    }

    const auto board = model->get_board();

    for (int i = 0; i < BoardModel::GAME_SIZE; i++) {
        buttons[i]->set_num(board[i]);
    }
}

void BoardView::set_start_board() {
    model->set_start_board();
    const auto board = model->get_board();

    for (int i = 0; i < BoardModel::GAME_SIZE; i++) {
        buttons[i]->set_num(board[i]);
    }
}

void BoardView::move(int idx) {
    const auto result = model->move(idx);
    const auto is_moved = result.first;

    if (is_moved) {
        const int nul_idx = result.second.toInt();
        FifteenPushButton::swap_nums(buttons[idx], buttons[nul_idx]);

        emit moved();
        check_game_end();
    }
}

void BoardView::back_move() {
    const auto result = model->back_move();
    const auto is_moved = result.first;

    if (is_moved) {
        const int lhs_idx = result.second.first.toInt();
        const int rhs_idx = result.second.second.toInt();
        auto lhs = buttons[lhs_idx];
        auto rhs = buttons[rhs_idx];

        FifteenPushButton::swap_nums(lhs, rhs);

        check_game_end();
    }
}

void BoardView::check_game_end() {
    const auto is_solved_result = model->is_solved();
    const auto is_solved = is_solved_result.first;

    if (is_solved) {
        const int num_shifts = is_solved_result.second.toInt();
        const auto msg = tr("Problem solved." "\n" "%1 permutations used.").arg(num_shifts);
        QMessageBox::information(this, tr("Game over"), msg);

    }
}


bool BoardView::check_back_moves_available() {
    return model->check_back_moves_available();
}


```

   <h3 style="color:#088A85;" id="spreadsheet-id" > Fifteen pushButton class  </h3>
<h5 style="color:#FF8000"> fifteenpushButton.h file:</h5>

```C++
#ifndef FIFTEENPUSHBUTTON_H
#define FIFTEENPUSHBUTTON_H

#include <QObject>
#include <QPushButton>

// game element
class FifteenPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit FifteenPushButton(QWidget *parent = nullptr);

    // change the displayed numbers on the buttons
    static void swap_nums(FifteenPushButton* lhs, FifteenPushButton* rhs) noexcept;

    int get_num() const noexcept;
    void set_num(int num) noexcept;

    int get_idx() const noexcept;
    void set_idx(const int idx) noexcept;

signals:
    void fifteen_btn_clicked(int idx);

private:
    int _num; // refluxed number
    int _idx; // element index - corresponds to the index in the model

    virtual void mousePressEvent(QMouseEvent *e) override;
};

#endif // FIFTEENPUSHBUTTON_H

```

<h5 style="color:#FF8000"> fifteenpushButton.cpp file:</h5>


```c++
#include <QString>
#include "fifteenpushbutton.h"
#include "boardmodel.h"

FifteenPushButton::FifteenPushButton(QWidget *parent)
    : QPushButton(parent) {}

void FifteenPushButton::swap_nums(FifteenPushButton *lhs, FifteenPushButton *rhs) noexcept {
    const int tmp_num = lhs->_num;
    lhs->set_num(rhs->_num);
    rhs->set_num(tmp_num);
}

int FifteenPushButton::get_num() const noexcept {
    return _num;
}

void FifteenPushButton::set_num(int num) noexcept {
    _num = num;
    if (_num != BoardModel::EMPTY_ELEMENT) {
        setText(QString::number(_num));
        if (!isEnabled()) {
            setEnabled(true);
        }
    } else {
        setText("");
        setEnabled(false);
    }

}

int FifteenPushButton::get_idx() const noexcept {
    return _idx;
}

void FifteenPushButton::set_idx(const int idx) noexcept {
    _idx = idx;
}

void FifteenPushButton::mousePressEvent(QMouseEvent *e) {
    if (_num != BoardModel::EMPTY_ELEMENT) {
        emit fifteen_btn_clicked(_idx);
    }
}


```

------------


   <h3 style="color:#088A85" id="result-id" >The code Result</h3>



https://user-images.githubusercontent.com/86807424/152706152-a305aeeb-6983-4b12-a9f9-a2f0c76828aa.mp4










------------
   <h3 style="color:#088A85" id="conclusion-id" >Conclusion </h3>


<p> This project allowed us to learn several things about building game applications using Qt designer, we are proud of the results obtained.  </p>









------------
<h4> <a href="#up-id">Up</a></h4>
  
  </div>
