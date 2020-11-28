#include "atmmainwindow.h"

#include <QApplication>
#include "controllers/uicontroller.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ATMMainWindow w;
	w.show();
	UIController c(&w);
    return a.exec();
}
