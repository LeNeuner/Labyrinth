#include "settingswindow.h"
#include "ui_settingswindow.h"

#include <QDebug>

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

void SettingsWindow::on_bAccept_clicked()
{
    // запись новых параметров в модель

    // создание поля
}

void SettingsWindow::on_bCancel_clicked()
{
    this->close();
}
