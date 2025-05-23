#include "ClientGenerator.h"
#include <QDebug>

ClientGenerator::ClientGenerator(QObject* parent)
    : QObject(parent), m_timer(new QTimer(this))
{
    connect(m_timer, &QTimer::timeout, this, &ClientGenerator::generateClient);
}

void ClientGenerator::start()
{
    if (!m_running) {
        m_running = true;
        m_timer->start(10000);
        qDebug() << "[ClientGenerator] Started";
    }
}

void ClientGenerator::stop()
{
    if (m_running) {
        m_timer->stop();
        m_running = false;
        qDebug() << "[ClientGenerator] Stopped";
    }
}

void ClientGenerator::generateClient()
{
    Client c;
    c.name = "something new";
    c.email = "same new things";
    c.save();

    qDebug() << "[ClientGenerator] Client created:" << QString::fromStdString(c.data());
}
