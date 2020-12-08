#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <vector>
#include <iostream>
using std::cout;

void print(std::vector<int> vect)
{
    for (int i = 0; i != vect.size(); i++)
    {
        cout << vect[i] << ' ';
    }
    cout << '\n';
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
