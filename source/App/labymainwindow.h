/*!
\file
\brief Заголовочный файл, содержащий класс LabyMainWindow -
класс главного окна приложения
*/
#ifndef LABYMAINWINDOW_H
#define LABYMAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTextEdit>
#include <QPushButton>

#include "globalmodel.h"
#include "settingswindow.h"
#include "graphicsmanager.h"
#include "enginemanager.h"


namespace Ui {
class LabyMainWindow;
}

class LabyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LabyMainWindow(QWidget *parent = nullptr);
    ~LabyMainWindow();

private slots:

    // открыть окно настроек
    void settingsWindowOpen();
    // открыть окно "О программе"
    void aboutWindowOpen();
    // создать новую игру
    void createNewGame();

    // слот заглушка
    void slotNoImp();
    // оповещение о включении приложения
    void testAlert();

    // временная кнопка удобной генерации поля
    void on_bGenerate_clicked();

    //+
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::LabyMainWindow  *ui;
    GlobalModel         *glModel;           // глобальная модель параметров
    SettingsWindow      *settWind;          // окно управления настройками
    GraphicsManager     *graphManager;      // класс управления графикой
    EngineManager       *engineManager;     // класс движка (управления игрой)

    // установить основное меню приложения
    void setMainMenu();
    // установить основное меню приложения
    void setGlobalParamModel();
};

#endif // LABYMAINWINDOW_H
