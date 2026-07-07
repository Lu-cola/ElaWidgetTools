#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ElaWindow.h"

class T_Page1;
class T_Page2;

class MainWindow : public ElaWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

    void initWindow();
    void initContent();

private:
    T_Page1* _page1{nullptr};
    T_Page2* _page2{nullptr};
    QString _page1Key{""};
    QString _page2Key{""};
};

#endif // MAINWINDOW_H
