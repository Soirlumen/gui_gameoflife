#include "logic.h"

Gra_życia::Gra_życia(CMatrix _k) : cell_gameboard(_k)
{
    width = cell_gameboard.size();
    height = cell_gameboard[0].size();
}
CMatrix Gra_życia::help_gameboard() const
{
    CMatrix result;
    result.push_back(std::vector<Cell>(height + 2, SCHRÖDINGER));
    for (int i = 0; i < width; i++)
    {
        std::vector<Cell> pom;
        pom.push_back(SCHRÖDINGER);
        for (int j = 1; j < height + 1; j++)
        {

            pom.push_back(cell_gameboard[i][j - 1]);
        }
        pom.push_back(SCHRÖDINGER);
        result.push_back(pom);
    }
    result.push_back(std::vector<Cell>(height + 2, SCHRÖDINGER));
    return result;
}

Cell Gra_życia::get(int x, int y) const
{
    return cell_gameboard[x][y];
}
void Gra_życia::set(int x, int y, Cell _c)
{
    cell_gameboard[x].at(y) = _c;
}

int Gra_życia::counting_neighbours(int x, int y) const
{
    CMatrix tymczasowy = help_gameboard();
    int numer = 0;

    for (int i = x; i < x + 3; i++)
    {

        for (int j = y; j < y + 3; j++)
        {

            if (tymczasowy[i][j] == ALIVE)
            {

                numer++;
            }
        }
    }
    if (tymczasowy[x + 1][y + 1] == ALIVE)
    {
        numer--;
    }
    return numer;
}

Cell Gra_życia::new_state(int x, int y) const
{
    int pepschmi = counting_neighbours(x, y);

    if (get(x, y) == ALIVE)
    {
        if ((pepschmi < 2) || (pepschmi > 3))
        {

            return DEAD;
        }
        return ALIVE;
    }
    if (pepschmi == 3)
    {
        return ALIVE;
    }
    return DEAD;
}
int Gra_życia::getW() const
{
    return width;
}
int Gra_życia::getH() const
{
    return height;
}
CMatrix Gra_życia::get_cell_gameboard() const
{
    return cell_gameboard;
}

CMatrix Game::get_actual_board() const
{
    return first.get_cell_gameboard();
}

void Game::setGame(CMatrix g)
{
    Gra_życia pom(g);
    first = pom;
    second = pom;
}

Game::Game(Gra_życia _p) : first(_p), second(_p) {}
CMatrix Game::new_generation()
{

    for (int i = 0; i < first.getW(); i++)
    {
        for (int j = 0; j < first.getH(); j++)
        {
            second.set(i, j, first.new_state(i, j));
        }
    }
    std::swap(first, second);
    return first.get_cell_gameboard();
}
void Game::life(int czas)
{
    for (int i = 0; i < czas; i++)
    {
        new_generation();
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        system("cls");
    }
}

Game::~Game()
{
}
