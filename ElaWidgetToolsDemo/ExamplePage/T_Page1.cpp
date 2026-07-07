#include "T_Page1.h"

#include <QVBoxLayout>

#include "ElaCheckBox.h"
#include "ElaComboBox.h"
#include "ElaLineEdit.h"
#include "ElaProgressBar.h"
#include "ElaPushButton.h"
#include "ElaSlider.h"
#include "ElaText.h"
#include "ElaToggleButton.h"
#include "ElaToggleSwitch.h"

T_Page1::T_Page1(QWidget* parent)
    : ElaScrollPage(parent)
{
    setWindowTitle("基础组件");

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("基础组件");
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->setSpacing(15);
    layout->setContentsMargins(30, 20, 30, 20);

    // 标题
    ElaText* titleText = new ElaText("基础组件示例", this);
    titleText->setTextPixelSize(24);
    layout->addWidget(titleText);

    // 按钮区域
    ElaText* buttonText = new ElaText("ElaPushButton", this);
    buttonText->setTextPixelSize(16);
    layout->addWidget(buttonText);

    ElaPushButton* button1 = new ElaPushButton("默认按钮", this);
    button1->setFixedWidth(200);
    layout->addWidget(button1);

    ElaPushButton* button2 = new ElaPushButton("禁用按钮", this);
    button2->setFixedWidth(200);
    button2->setEnabled(false);
    layout->addWidget(button2);

    // 切换按钮与开关
    ElaText* toggleText = new ElaText("ElaToggleButton / ElaToggleSwitch", this);
    toggleText->setTextPixelSize(16);
    layout->addWidget(toggleText);

    QHBoxLayout* toggleLayout = new QHBoxLayout();
    ElaToggleButton* toggleButton = new ElaToggleButton("切换按钮", this);
    toggleLayout->addWidget(toggleButton);
    ElaToggleSwitch* toggleSwitch = new ElaToggleSwitch(this);
    toggleLayout->addWidget(toggleSwitch);
    toggleLayout->addStretch();
    layout->addLayout(toggleLayout);

    // 输入框
    ElaText* inputText = new ElaText("ElaLineEdit", this);
    inputText->setTextPixelSize(16);
    layout->addWidget(inputText);

    ElaLineEdit* lineEdit = new ElaLineEdit(this);
    lineEdit->setPlaceholderText("请输入内容...");
    lineEdit->setFixedWidth(300);
    layout->addWidget(lineEdit);

    // 复选框
    ElaText* checkText = new ElaText("ElaCheckBox", this);
    checkText->setTextPixelSize(16);
    layout->addWidget(checkText);

    ElaCheckBox* checkBox1 = new ElaCheckBox("选项一", this);
    layout->addWidget(checkBox1);
    ElaCheckBox* checkBox2 = new ElaCheckBox("选项二", this);
    checkBox2->setChecked(true);
    layout->addWidget(checkBox2);

    // 下拉框
    ElaText* comboText = new ElaText("ElaComboBox", this);
    comboText->setTextPixelSize(16);
    layout->addWidget(comboText);

    ElaComboBox* comboBox = new ElaComboBox(this);
    comboBox->addItems({"选项 A", "选项 B", "选项 C"});
    comboBox->setFixedWidth(200);
    layout->addWidget(comboBox);

    // 滑块
    ElaText* sliderText = new ElaText("ElaSlider", this);
    sliderText->setTextPixelSize(16);
    layout->addWidget(sliderText);

    ElaSlider* slider = new ElaSlider(Qt::Horizontal, this);
    slider->setFixedWidth(300);
    slider->setRange(0, 100);
    slider->setValue(50);
    layout->addWidget(slider);

    // 进度条
    ElaText* progressText = new ElaText("ElaProgressBar", this);
    progressText->setTextPixelSize(16);
    layout->addWidget(progressText);

    ElaProgressBar* progressBar = new ElaProgressBar(this);
    progressBar->setFixedWidth(300);
    progressBar->setRange(0, 100);
    progressBar->setValue(60);
    layout->addWidget(progressBar);

    layout->addStretch();
    addCentralWidget(centralWidget);
}

T_Page1::~T_Page1()
{
}
