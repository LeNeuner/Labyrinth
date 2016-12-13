#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);

    // снимаем флаг WindowContextHelpButtonHint
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::MSWindowsFixedSizeDialogHint |
                         Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}
