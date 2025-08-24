

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

CMatrix convert_S_toC(SMatrix s,char ch)
{

    int pom1 = s.size();
    CMatrix result; //(pom1,std::vector<Cell>(pom2,DEAD));
    for (int i=0; i < pom1; i++)
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
    if(file.open(QFile::ReadOnly | QFile::Text))
    {
        while(!file.atEnd())
        {
            vec.push_back(file.readLine());
        }
    }
    return vec;

}

CMatrix convert_SQ_toC(const SQMatrix s, char ch)
{
    CMatrix result;
    for (int i=0; i < s.size(); i++)
    {
        std::vector<Cell> pom;
        for(QString::const_iterator it = s[i].begin(); it != s[i].end(); it++)
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


//kontroluje, jestli je vektor stringů konzistentní (všechny řádky stejně dlouhé) anebo prázdná, prázdná matice - false počkeeeeeeeeeeeeeJ VŠAK TO MOHU KONTROLOVAT JEN JAKO cmATRIX IDIOTE BLBEČKU:(
bool test_matrix_consistency(SQMatrix s)
{
    if (s.empty())
    {
        qDebug()<<"it's all empty man";
        return false;
    }
    int first_wymiar = s[0].size();
    for (std::vector<QString>::const_iterator it = s.begin(); it != s.end(); it++)
    {
        if (it->size() != first_wymiar)
        {
            qDebug()<<"man its not a rectangle, its someting cringe idk";
            return false;
        }
    }
    qDebug() << "man its ok\n";
    return true;
}

bool test_matrix_consistency(CMatrix c)
{
    if(c.size()<3){
        qDebug()<<"it's too small man, make bigger field pls";
        return false;
    }
    //prvni radek bere nějak jinak ja to nechapu
    if(c[0].size()+1!=c[1].size()){
        qDebug()<<"iterace: "<<0;
        qDebug()<<"man it's not a rectangle, its something cringe lol";
        return false;
    }

    int first_wymiar=c[1].size();
    qDebug()<<first_wymiar<<"delka 2. radku";
    qDebug()<<c.size()<<" pocet iteraci";
    for(int i=1;i<c.size();i++){
        //qDebug()<<"velikost: "<<c[i].size();
        if(c[i].size()!=first_wymiar){
            qDebug()<<"ktery radek je blbe: "<<i;
            qDebug()<<"man it's not a rectangle, its something cringe lol";
            return false;
        }
    }
    qDebug()<<"ey it's a rectangle boy";
    return true;
}

