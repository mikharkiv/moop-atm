#ifndef ATMMAINWINDOW_H
#define ATMMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ATMMainWindow; }
QT_END_NAMESPACE

class ATMMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ATMMainWindow(QWidget *parent = nullptr);
    ~ATMMainWindow();

private:
    Ui::ATMMainWindow *ui;
};
#endif // ATMMAINWINDOW_H
