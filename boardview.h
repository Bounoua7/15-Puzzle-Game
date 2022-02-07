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
