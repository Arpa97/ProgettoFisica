#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <vector>
#include <iostream>
#include <ctime>

void stress_test()
{
    //double(*composizione)[2] = new double[3][2]{ {1, .5}, {13, .2}, {7, .3} };
    std::vector<std::vector<double>> composizione;
    int step = GRID_SIDE / CELL_SIDE;
    Environment* Foresta;
    time_t start = time(0);

    for (int i = 0; i != step; i++)
    {
        for (int j = 0; j != step; j++)
        {
            for (int U = 0; U < 3; U++)
            {
                for (double theta = -3; theta < 4; theta++)
                {
                    Foresta = new Environment(composizione, DEFAULT_MOISTURE);
                    Foresta->setU(U);
                    Foresta->setTheta(theta);
                    Foresta->addFire((i + 1) * CELL_SIDE / 2, (j + 1) * CELL_SIDE / 2);
                    while (!Foresta->timeHeap.empty())
                    {
                        Foresta->advance(1);
                    }
                    std::cerr << i << ' ' << j << ' ' << U << ' ' << theta << ' ' << difftime(time(0), start) << '\n';
                    //delete[] Foresta;     //TBD dctor Environment
                }
            }
        }
    }
 


}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    //stress_test();
}
