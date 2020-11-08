#include "atmmainwindow.h"
#include "ui_atmmainwindow.h"

ATMMainWindow::ATMMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ATMMainWindow)
{
    ui->setupUi(this);
}

ATMMainWindow::~ATMMainWindow()
{
    delete ui;
}

