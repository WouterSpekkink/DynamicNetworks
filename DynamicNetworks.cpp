#include <QApplication>
#include "MainDialog.h"


int main(int argc, char *argv[]) 
{
    // Setting up the app
    QApplication DynamicNetworks(argc, argv);

    MainDialog *dialog =  new MainDialog;
    dialog->show();
    return DynamicNetworks.exec();
}

