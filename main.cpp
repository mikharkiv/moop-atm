#include "atmmainwindow.h"

#include <QApplication>
#include "controllers/uicontroller.h"
#include "controllers/sessioncontroller.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ATMMainWindow w;
	w.show();
	UIController c(&w);
	SessionController s(&c);
    return a.exec();
}
