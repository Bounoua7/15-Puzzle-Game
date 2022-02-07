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
