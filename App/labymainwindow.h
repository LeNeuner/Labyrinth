#ifndef LABYMAINWINDOW_H
#define LABYMAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTextEdit>
#include <QPushButton>

#include "globalmodel.h"
#include "settingswindow.h"
#include "graphicsmanager.h"


namespace Ui {
class LabyMainWindow;
}

class LabyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LabyMainWindow(QWidget *parent = 0);
    ~LabyMainWindow();

private slots:
    void settingsWindowOpen();
    void aboutWindowOpen();

    void slotNoImp();
    void testAlert();

    void on_bGenerate_clicked();

private:
    Ui::LabyMainWindow  *ui;
    GlobalModel         *glModel;
    SettingsWindow      *settWind;
    GraphicsManager     *graphManager;

    void setMainMenu();
    void setGlobalParamModel();
};

#endif // LABYMAINWINDOW_H
