#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "ElaText.h"
#include "ElaTheme.h"
#include "ExamplePage/T_Page1.h"
#include "ExamplePage/T_Page2.h"

MainWindow::MainWindow(QWidget* parent)
    : ElaWindow(parent)
{
    initWindow();
    initContent();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initWindow()
{
    setFocusPolicy(Qt::StrongFocus);
    resize(1000, 650);
    setWindowTitle("ElaWidgetTools Demo");
    setUserInfoCardTitle("Demo App");
    setUserInfoCardSubTitle("ElaWidgetTools Demo");

    // 中心堆栈占位页面
    ElaText* centralText = new ElaText("欢迎使用 ElaWidgetTools Demo", this);
    centralText->setTextPixelSize(28);
    centralText->setAlignment(Qt::AlignCenter);
    addCentralWidget(centralText);
}

void MainWindow::initContent()
{
    _page1 = new T_Page1(this);
    _page2 = new T_Page2(this);

    addPageNode("示例页面1", _page1, ElaIconType::House);
    addPageNode("示例页面2", _page2, ElaIconType::GearComplex);
}
