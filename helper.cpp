

#include "helper.h"

SMatrix read_file(String filename)
{
    // otevreme soubor pro cteni
    std::ifstream file(filename);

    SMatrix result;
    // kontrola chyb pomoci file.good()
    while (file.good())
    {
        // cteni obsahu pomoci funkce getline()
        std::string line;
        std::getline(file, line);
        result.push_back(line);
    }

    if (!file.eof())
    {
        file.close();
        return result = {"neni konec souboru!"};
    }
    // vratit vysledek
    file.close();
    return result;
}

void read_smatrix(SMatrix &board)
{
    // tady bude třeba kontrola vstupu, nebo to bude samostatná fce
    for (int i = 0; i < board.size(); i++)
    {
        for (const char &j : board[i])
        {
            std::cout << j;
        }
        std::cout << std::endl;
    }
}
void read_Cmatrix(CMatrix board)
{
    // tady bude třeba kontrola vstupu, nebo to bude samostatná fce
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            std::cout << board[i][j];
        }
        std::cout << std::endl;
    }
}
bool test_matrix_consistency(SMatrix s)
{
    if (s.empty())
    {
        std::cout << "its not ok\n";
        return false;
    }
    int first_sz = s[0].size();
    for (auto linia : s)
    {
        if (linia.size() != first_sz)
        {
            std::cout << "its not ok\n";
            return false;
        }
    }
    std::cout << "its ok\n";
    return true;
}

CMatrix convert_S_toC(SMatrix s, char ch)
{

    int pom1 = s.size();
    CMatrix result; //(pom1,std::vector<Cell>(pom2,DEAD));
    for (int i = 0; i < pom1; i++)
    {
        std::vector<Cell> pom;
        for (char &c : s[i])
        {
            if (c == ch)
            {
                pom.push_back(ALIVE);
            }
            else
            {
                pom.push_back(DEAD);
            }
        }
        result.push_back(pom);
    }
    return result;
}

SQMatrix read_file2(QString filename)
{
    QFile file(filename);
    SQMatrix vec;
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        while (!file.atEnd())
        {
            QString line = file.readLine();
            line.chop(1); // odstraní \n nebo \r
            vec.push_back(line);
        }
    }
    return vec;
}

CMatrix convert_SQ_toC(const SQMatrix s, char ch)
{
    CMatrix result;
    for (int i = 0; i < s.size(); i++)
    {
        std::vector<Cell> pom;
        for (QString::const_iterator it = s[i].begin(); it != s[i].end(); it++)
        {
            if (*it == ch)
            {
                pom.push_back(ALIVE);
            }
            else
            {
                pom.push_back(DEAD);
            }
        }
        result.push_back(pom);
    }
    return result;
}

// kontroluje, jestli je vektor stringů konzistentní (všechny řádky stejně dlouhé) anebo prázdná, prázdná matice - false počkeeeeeeeeeeeeeJ VŠAK TO MOHU KONTROLOVAT JEN JAKO cmATRIX IDIOTE BLBEČKU:(
bool test_matrix_consistency(SQMatrix s)
{
    if (s.empty())
    {
        qDebug() << "it's all empty man";
        return false;
    }
    int first_wymiar = s[0].size();
    for (std::vector<QString>::const_iterator it = s.begin(); it != s.end(); it++)
    {
        if (it->size() != first_wymiar)
        {
            qDebug() << "man its not a rectangle, its someting cringe idk";
            return false;
        }
    }
    qDebug() << "man its ok\n";
    return true;
}

bool test_matrix_consistency(CMatrix c)
{
    if (c.size() < 3)
    {
        qDebug() << "it's too small man, make bigger field pls";
        return false;
    }

    int first_wymiar = c[0].size();
    for (int i = 1; i < c.size(); i++)
    {
        if (c[i].size() != first_wymiar)
        {
            qDebug() << "Row " << i << " has different size";
            return false;
        }
    }
    qDebug() << "ey it's a rectangle boy";
    return true;
}

CMatrix cut(const CMatrix &c)
{
    int rows = c.size();
    if (rows == 0)
        return CMatrix();

    int cols = c[0].size();
    if (cols == 0)
        return CMatrix();

    int min_x = rows, max_x = -1;
    int min_y = cols, max_y = -1;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (c[i][j] == ALIVE)
            {
                if (i < min_x)
                    min_x = i;
                if (i > max_x)
                    max_x = i;
                if (j < min_y)
                    min_y = j;
                if (j > max_y)
                    max_y = j;
            }
        }
    }

    if (max_x < min_x || max_y < min_y)
    {
        return CMatrix(); // všechno mrtvé
    }

    CMatrix result(max_x - min_x + 1, std::vector<Cell>(max_y - min_y + 1));

    for (int i = min_x; i <= max_x; ++i)
    {
        for (int j = min_y; j <= max_y; ++j)
        {
            result[i - min_x][j - min_y] = c[i][j];
        }
    }

    return result;
}
