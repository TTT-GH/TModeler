#ifndef CLIENTGENERATOR_H
#define CLIENTGENERATOR_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include "models.h"

class ClientGenerator : public QObject
{
    Q_OBJECT

public:
    explicit ClientGenerator(QObject* parent = nullptr);

public slots:
    void start();
    void stop();

private slots:
    void generateClient();

private:
    QTimer* m_timer = nullptr;
    bool m_running = false;
};

#endif // CLIENTGENERATOR_H
