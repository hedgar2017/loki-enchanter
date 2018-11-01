#include <QApplication>
#include <QTime>
#include <iostream>

#include "dialogs/dialog_about.h"
#include "main_window.h"

int main(int argc, char *argv[])
{
    if (argc > 1 && 0 == strcmp(argv[1], "--version")) {
        std::cout << APP_VERSION << std::endl;
        return EXIT_SUCCESS;
    }

    qsrand(QTime::currentTime().msec());

    QApplication qApplication{argc, argv};
    MainWindow mainWindow;
    if (argc > 1 && 0 == strcmp(argv[1], "--about")) {
        AboutDialog dialog{&mainWindow};
        dialog.show();
        return qApplication.exec();
    }
    mainWindow.show();
    return qApplication.exec();
}
