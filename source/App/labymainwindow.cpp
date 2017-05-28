#include "labymainwindow.h"
#include "ui_labymainwindow.h"

#include <iostream>
#include <QDebug>

#include "aboutwindow.h"

LabyMainWindow::LabyMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LabyMainWindow),
    glModel(new GlobalModel(this)),
    settWind(new SettingsWindow(this)),
    graphManager(new GraphicsManager(this))
{
    ui->setupUi(this);

    // установка глобальной модели настроек
    setGlobalParamModel();

    // установка виджетов основного меню
    setMainMenu();

    // графическое построение поля игрока
    ui->gvLaby->setScene(graphManager->createPlayerGraphicsScene());

    // графическое построение поля
    ui->gvSecond->setScene(graphManager->createGraphicsScene());
}

LabyMainWindow::~LabyMainWindow()
{
    delete ui;
    delete glModel;
    delete settWind;
    delete graphManager;
}

//--------------------------------------------------
// добавление основного меню
//--------------------------------------------------
void LabyMainWindow::setMainMenu()
{
    //--------------------------------------------------
    // 1. MenuBar
    //--------------------------------------------------
    // создание новой игры
    QAction* actNewGame = new QAction("start new game", 0);
    actNewGame->setText("Новая игра");
    actNewGame->setShortcut(QKeySequence("CTRL+N"));
    actNewGame->setToolTip("Начать новую игру");
    actNewGame->setStatusTip("Начать новую игру");
    actNewGame->setWhatsThis("Начать новую игру");
    actNewGame->setIcon(QPixmap(":AppIcon"));
    connect(actNewGame, SIGNAL(triggered()), SLOT(createNewGame()));

    // настройки
    QAction* actSettings = new QAction("open settings window", 0);
    actSettings->setText("Параметры");
    actSettings->setShortcut(QKeySequence("CTRL+P"));
    actSettings->setToolTip("Открыть окно настройки параметров");
    actSettings->setStatusTip("Открыть окно настройки параметров");
    actSettings->setWhatsThis("Открыть окно настройки параметров");
    actSettings->setIcon(QPixmap(":SettingsIcon"));
    connect(actSettings, SIGNAL(triggered()), SLOT(settingsWindowOpen()));

    // Выход
    QAction* actExit = new QAction("app exit", 0);
    actExit->setText("&Выход");
    actExit->setShortcut(QKeySequence("ALT+F4"));
    actExit->setToolTip("Выход из приложения");
    actExit->setStatusTip("Выход из приложения");
    actExit->setWhatsThis("Выход из приложения");
    actExit->setIcon(QPixmap(":ExitIcon"));
    connect(actExit, SIGNAL(triggered()), this, SLOT(close()));

    // Составление меню #Игра
    QMenu* menuGame = new QMenu("Игра");
    menuGame->addAction(actNewGame);
    menuGame->addAction(actSettings);
    menuGame->addSeparator();
    menuGame->addAction(actExit);
    this->menuBar()->addMenu(menuGame);


    // Справка
    QAction* actReference = new QAction("open Reference", 0);
    actReference->setText("Справка");
    actReference->setShortcut(QKeySequence("F1"));
    actReference->setToolTip("Информация о программе");
    actReference->setStatusTip("Информация о программе");
    actReference->setWhatsThis("Информация о программе");
    connect(actReference, SIGNAL(triggered()), SLOT(aboutWindowOpen()));
    this->menuBar()->addAction(actReference);

    // Дополнительная кнопка выхода
    QAction* actAddExit = new QAction("exit", 0);
    actAddExit->setStatusTip("Выход из приложения");
    actAddExit->setWhatsThis("Выход из приложения");
    actAddExit->setIcon(QPixmap(":ExitIcon"));
    connect(actAddExit, SIGNAL(triggered()), this, SLOT(close()));
    this->menuBar()->addSeparator();
    this->menuBar()->addAction(actAddExit);
    //--------------------------------------------------
}


//--------------------------------------------------
// установка глобальной модели нстроек
//--------------------------------------------------
void LabyMainWindow::setGlobalParamModel()
{
    // модель по умолчанию
    glModel->setDefaults();
    settWind->setGlobalModel(glModel);
    graphManager->setGlobalModel(glModel);

    // модель из файла
//    QString folder = QCoreApplication::applicationDirPath();
//    bool successSettLoad = settManager->loadSettings(folder + "\\settings\\lastSettings.jSon");

//    if (!successSettLoad)
//        glModel->setDefaults();

//    commandListChanged();
}
//--------------------------------------------------


//--------------------------------------------------
// слоты
//--------------------------------------------------
void LabyMainWindow::settingsWindowOpen()
{
    settWind->setWindowIcon(QPixmap(":SettingsIcon"));

    // открыть окно основных настроек
    int winResult;
    winResult = settWind->exec();

    // выход, если добавление отменено (несохранено)
    if (winResult == QDialog::Rejected)
        return;

    // создание нового игрового поля
    createNewGame();
}
void LabyMainWindow::aboutWindowOpen()
{
    AboutWindow aboutWind;
    aboutWind.exec();
}

void LabyMainWindow::createNewGame()
{
    glModel->fieldModel->createField(glModel->gameSettModel);
    glModel->playerFieldModel->createPlayerField(glModel->gameSettModel);

    ui->gvSecond->setScene(graphManager->updateGraphicsScene());
    ui->gvSecond->update();

    ui->gvLaby->setScene(graphManager->updatePlayerGraphicsScene());
    ui->gvLaby->update();
}
//--------------------------------------------------


//--------------------------------------------------
// служебные слоты
//--------------------------------------------------
// слот заглушка
void LabyMainWindow::slotNoImp()
{
    QMessageBox::information(0, "Message", "Not implemented");
}

// сообщение миганием о запуске приложения
void LabyMainWindow::testAlert()
{
    QApplication::alert(this, 10000);
}

// key test
void LabyMainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "key pressed: " << event->key();
    qDebug() << QString("You typed %1").arg(event->key());
}

//--------------------------------------------------




// временная генерация (убрать)
void LabyMainWindow::on_bGenerate_clicked()
{
    createNewGame();
//    glModel->fieldModel->createField(glModel->gameSettModel);

//    ui->gvLaby->setScene(graphManager->updateGraphicsScene());
//    ui->gvLaby->update();
}
