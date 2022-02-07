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
