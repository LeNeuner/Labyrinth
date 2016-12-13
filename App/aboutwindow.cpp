#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);

    // снимаем флаг WindowContextHelpButtonHint
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::MSWindowsFixedSizeDialogHint |
                         Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::on_bOK_clicked()
{
    this->close();
}
