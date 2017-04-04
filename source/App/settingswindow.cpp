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

    setChangeMode(false);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

//--------------------------------------------------
// обработка нажатия клавиши подтверждния
void SettingsWindow::on_bAccept_clicked()
{
    // запись новых параметров в модель
    saveParams();

    // создание поля
    glModel->fieldModel->createField(glModel->gameSettModel);
    accept();
}
// обработка нажатия клавиши отмены
void SettingsWindow::on_bCancel_clicked()
{
    this->close();
}
// обработка изменения режима игры
void SettingsWindow::on_cmbGameMode_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "Сложный")
    {
        setParamsToModeValues(15, 15, 4, 1, 2, 3, 2, 10, 5);
        setChangeMode(false);
    }
    else if (arg1 == "Стандартный")
    {
        setParamsToModeValues(10, 10, 4, 1, 1, 2, 2, 10, 5);
        setChangeMode(false);
    }
    else if (arg1 == "Простой")
    {
        setParamsToModeValues(7, 7, 4, 1, 0, 1, 1, 7, 3);
        setChangeMode(false);
    }
    else
        setChangeMode(true);
}
//--------------------------------------------------

// сохранение игровых настроек
void SettingsWindow::saveParams()
{
    // размеры поля
    glModel->gameSettModel->setFieldWidth(ui->sbWidth->value());
    glModel->gameSettModel->setFieldHeight(ui->sbHeight->value());

    // количество игровых объектов
    glModel->gameSettModel->setRealTreasureNum(ui->sbRealTreasure->value());
    glModel->gameSettModel->setFakeTreasureNum(ui->sbFakeTreasure->value());
    glModel->gameSettModel->setArsenalNum(ui->sbArsenal->value());
    glModel->gameSettModel->setHoleTypeNum(ui->sbHole->value());
    glModel->gameSettModel->setFieldExitNum(ui->sbExit->value());

    // инвентарь игрока
    glModel->gameSettModel->setAmmunitionNum(ui->sbAmmunition->value());
    glModel->gameSettModel->setGrenadeNum(ui->sbGrenade->value());
}

// установка параметров в соотвествии с выбранным режимом
void SettingsWindow::setParamsToModeValues(int width, int height, int exit,
                                           int real, int fake, int arsenal,
                                           int hole, int ammo, int grenade)
{
    ui->sbWidth->setValue(width);
    ui->sbHeight->setValue(height);
    ui->sbRealTreasure->setValue(real);
    ui->sbFakeTreasure->setValue(fake);
    ui->sbArsenal->setValue(arsenal);
    ui->sbHole->setValue(hole);
    ui->sbExit->setValue(exit);
    ui->sbAmmunition->setValue(ammo);
    ui->sbGrenade->setValue(grenade);
}
// блокировка/разблокировка внесения изменений в настройки
void SettingsWindow::setChangeMode(bool isCanChange)
{
    ui->sbWidth->setEnabled(isCanChange);
    ui->sbHeight->setEnabled(isCanChange);
    ui->sbRealTreasure->setEnabled(isCanChange);
    ui->sbFakeTreasure->setEnabled(isCanChange);
    ui->sbArsenal->setEnabled(isCanChange);
    ui->sbHole->setEnabled(isCanChange);
    ui->sbExit->setEnabled(isCanChange);
    ui->sbAmmunition->setEnabled(isCanChange);
    ui->sbGrenade->setEnabled(isCanChange);
}


