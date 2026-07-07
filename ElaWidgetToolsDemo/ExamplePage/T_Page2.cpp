#include "T_Page2.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "ElaMessageBar.h"
#include "ElaProgressBar.h"
#include "ElaProgressRing.h"
#include "ElaPushButton.h"
#include "ElaReminderCard.h"
#include "ElaText.h"
#include "ElaTheme.h"
#include "ElaToggleSwitch.h"

T_Page2::T_Page2(QWidget* parent)
    : ElaScrollPage(parent)
{
    setWindowTitle("主题与提示");

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("主题与提示");
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->setSpacing(15);
    layout->setContentsMargins(30, 20, 30, 20);

    // 标题
    ElaText* titleText = new ElaText("主题与提示示例", this);
    titleText->setTextPixelSize(24);
    layout->addWidget(titleText);

    // 主题切换
    ElaText* themeText = new ElaText("主题切换", this);
    themeText->setTextPixelSize(16);
    layout->addWidget(themeText);

    QHBoxLayout* themeLayout = new QHBoxLayout();
    ElaText* themeLabel = new ElaText("深色模式", this);
    themeLabel->setTextPixelSize(14);
    themeLayout->addWidget(themeLabel);
    ElaToggleSwitch* themeSwitch = new ElaToggleSwitch(this);
    themeLayout->addWidget(themeSwitch);
    themeLayout->addStretch();
    layout->addLayout(themeLayout);

    connect(themeSwitch, &ElaToggleSwitch::toggled, this, [=](bool isChecked) {
        eTheme->setThemeMode(isChecked ? ElaThemeType::Dark : ElaThemeType::Light);
    });

    // 消息提示
    ElaText* messageText = new ElaText("ElaMessageBar", this);
    messageText->setTextPixelSize(16);
    layout->addWidget(messageText);

    QHBoxLayout* messageLayout = new QHBoxLayout();
    ElaPushButton* successBtn = new ElaPushButton("Success", this);
    successBtn->setFixedWidth(120);
    connect(successBtn, &ElaPushButton::clicked, this, [=]() {
        ElaMessageBar::success(ElaMessageBarType::BottomRight, "Success", "操作成功！", 2000);
    });
    messageLayout->addWidget(successBtn);

    ElaPushButton* warningBtn = new ElaPushButton("Warning", this);
    warningBtn->setFixedWidth(120);
    connect(warningBtn, &ElaPushButton::clicked, this, [=]() {
        ElaMessageBar::warning(ElaMessageBarType::BottomRight, "Warning", "这是一个警告！", 2000);
    });
    messageLayout->addWidget(warningBtn);

    ElaPushButton* errorBtn = new ElaPushButton("Error", this);
    errorBtn->setFixedWidth(120);
    connect(errorBtn, &ElaPushButton::clicked, this, [=]() {
        ElaMessageBar::error(ElaMessageBarType::BottomRight, "Error", "这是一个错误！", 2000);
    });
    messageLayout->addWidget(errorBtn);

    ElaPushButton* infoBtn = new ElaPushButton("Info", this);
    infoBtn->setFixedWidth(120);
    connect(infoBtn, &ElaPushButton::clicked, this, [=]() {
        ElaMessageBar::information(ElaMessageBarType::BottomRight, "Info", "这是一条信息", 2000);
    });
    messageLayout->addWidget(infoBtn);
    messageLayout->addStretch();
    layout->addLayout(messageLayout);

    // 进度条
    ElaText* progressText = new ElaText("ElaProgressBar / ElaProgressRing", this);
    progressText->setTextPixelSize(16);
    layout->addWidget(progressText);

    QHBoxLayout* progressLayout = new QHBoxLayout();
    ElaProgressBar* progressBar = new ElaProgressBar(this);
    progressBar->setFixedWidth(250);
    progressBar->setRange(0, 100);
    progressBar->setValue(60);
    progressLayout->addWidget(progressBar);

    ElaProgressRing* progressRing = new ElaProgressRing(this);
    progressRing->setFixedSize(50, 50);
    progressRing->setRange(0, 100);
    progressRing->setValue(75);
    progressLayout->addWidget(progressRing);
    progressLayout->addStretch();
    layout->addLayout(progressLayout);

    // 提醒卡片
    ElaText* cardText = new ElaText("ElaReminderCard", this);
    cardText->setTextPixelSize(16);
    layout->addWidget(cardText);

    ElaReminderCard* reminderCard = new ElaReminderCard(this);
    reminderCard->setCardPixmap(QPixmap());
    reminderCard->setTitle("提醒卡片");
    reminderCard->setSubTitle("这是一个示例提醒卡片，用于展示重要信息。");
    reminderCard->setFixedWidth(350);
    layout->addWidget(reminderCard);

    layout->addStretch();
    addCentralWidget(centralWidget);
}

T_Page2::~T_Page2()
{
}
