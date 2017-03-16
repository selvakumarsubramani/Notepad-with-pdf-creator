/**
  * @file main.cpp - contains main function of the mynotepad project
  */

#include <QApplication>

#include "mynotepad.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyNotePad w;
    w.show();

    return a.exec();
}
