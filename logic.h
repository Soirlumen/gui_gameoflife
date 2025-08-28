#ifndef LOGIC_H
#define LOGIC_H
#include "helper.h"

class Gra_życia
{
private:
    CMatrix cell_gameboard;
    int width;
    int height;

public:
    Gra_życia(CMatrix _k);
    CMatrix help_gameboard() const;
    Cell get(int x, int y) const;
    int getW() const;
    int getH() const;
    CMatrix get_cell_gameboard() const;
    void set(int x, int y, Cell _c);
    int counting_neighbours(int x, int y) const;
    Cell new_state(int x, int y) const;
};

class Game
{
private:
    Gra_życia first;
    Gra_życia second;

public:
    Game(Gra_życia _p);
    CMatrix get_actual_board() const;
    void setGame(CMatrix g);
    CMatrix new_generation();
    void life(int czas);
    ~Game();
};

#endif // LOGIC_H
