#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <QString>
#include <QFile>
#include <QDebug>

enum Cell
{
    DEAD = 0,
    ALIVE = 1,
    SCHRÖDINGER = 5
};
using String = std::string;
using SMatrix = std::vector<String>;
using CMatrix = std::vector<std::vector<Cell>>;
using SQMatrix = std::vector<QString>;

SMatrix read_file(String filename);
SQMatrix read_file2(QString filename);
void read_smatrix(SMatrix &board);
void read_Cmatrix(CMatrix board);
bool test_matrix_consistency(SMatrix s);
bool test_matrix_consistency(SQMatrix s);
bool test_matrix_consistency(CMatrix c);
CMatrix convert_S_toC(SMatrix s,char ch);
CMatrix convert_SQ_toC(SQMatrix s,char ch);
CMatrix cut(const CMatrix& c);

/*
template <typename T>
void wypisywanie(T t)
{
    std::cout << t << " ";
}

template<typename T, typename... Args>
void wypisywanie(T t, Args... args)
{
    std::cout << t <<" ";

    wypisywanie(args...) ;
}*/
#endif // HELPER_H
