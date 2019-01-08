#ifndef PLAYERS_H
#define PLAYERS_H

#include <QObject>

#include "globalModel_global.h"
#include "gamesettings.h"
#include "player.h"

class GLOBALMODELSHARED_EXPORT Players : public QObject
{
    Q_OBJECT
public:
    explicit Players(QObject *parent = nullptr);

    void setDefaults();
    void createPlayers(GameSettings *settings);

    std::vector<Player> players;

signals:

public slots:
};

#endif // PLAYERS_H
