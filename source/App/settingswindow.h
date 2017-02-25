#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include "globalmodel.h"
#include <QDialog>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = 0);
    ~SettingsWindow();

    // установка модели настроек
    void setGlobalModel(GlobalModel* model){
        glModel = model;
    }

private slots:
    void on_bAccept_clicked();
    void on_bCancel_clicked();

private:
    Ui::SettingsWindow  *ui;
    GlobalModel         *glModel = nullptr;
};

#endif // SETTINGSWINDOW_H
