#include <QStringList>
#include <QByteArray>
#include <QDebug>
#include <string>
#include <QThread>
#include <QTcpServer>
#include <QHostAddress>
#include <QSystemSemaphore>
#include <QSettings>
#include <QVariant>
#include <QGuiApplication>
#include <QDir>
#include <cstdlib>
#include <iostream>
#include <QFileInfo>

#include "dnai/processmanager.h"

ProcessManager::ProcessManager(QString const &file)
    : QObject(nullptr),
      m_file(file),
      m_server(),
      m_core(),
      m_updaterApp(),
      m_port(0)
{
}

ProcessManager::~ProcessManager() {
    closeAll();
}

void ProcessManager::closeAll() {
    qDebug() << "close server process and core process !";
    m_server.close();
    m_core.close();
}


void ProcessManager::launchUpdater(QString const &actualVer, QString const &newVersion) {
    if (m_updaterApp.size() != 0) {
    QProcess proc;
    QStringList args;

#if defined(Q_OS_MAC)
    QString path = QGuiApplication::applicationDirPath();
    int len = sizeof("/DNAI.app/Contents/MacOS");
    int idx = path.length() - (len - 1);
    path.remove(idx, len);

    QFile moveUpdater;
    QString applicationUpdater = QDir::tempPath() + "/DNAI_UPDATER.app";
    QFileInfo updaterFile(applicationUpdater);

    if (updaterFile.exists()) {
        QDir dir(applicationUpdater);
        dir.removeRecursively();
    }

    moveUpdater.rename(m_updaterApp, applicationUpdater);

    QString app = "\"" + applicationUpdater + "/Contents/MacOS/DNAI Updater\" " +  actualVer + " " + newVersion + " \"" + path + "\" " + "DNAI";
    qDebug() << app;
    proc.startDetached(app);
#else
    args.push_back(actualVer);
    args.push_back(newVersion);

 /*   QString appDirPath = QGuiApplication::applicationDirPath();
    while (appDirPath.size() >= 0 && appDirPath.back() != '/') {
        appDirPath.remove(appDirPath.size() - 1, 1);
    }
    appDirPath.remove(appDirPath.size() - 1, 1);
    args.push_back(appDirPath);
    qDebug() << appDirPath;*/
    args.push_back(QGuiApplication::applicationDirPath());

    args.push_back("DNAI");
    qDebug() << "applicationDirPath: " << QGuiApplication::applicationDirPath();
    QString updaterDir = m_updaterApp;
    m_updaterApp = "\"" + m_updaterApp + "\" ";// +  actualVer + " " + newVersion + " \"" + QGuiApplication::applicationDirPath() + "\" " + "DNAI";
    qDebug() << "M_UPDATERAPP: " << m_updaterApp;

    int idx = m_updaterApp.size();
    while (updaterDir.size() >= 0 && updaterDir.back() != '/') {
        updaterDir.remove(updaterDir.size() - 1, 1);
    }
    updaterDir.remove(updaterDir.size() - 1, 1);
    qDebug() << "UPDATERDIR: " << updaterDir;

    /*QDir dirRemove(QDir::tempPath() + "/DNAI_UPDATER");

    dirRemove.removeRecursively();*/

    QDir dir;

    bool returnRename = dir.rename(updaterDir, QDir::tempPath() + "/DNAI_UPDATER");
    qDebug() << returnRename;
    proc.startDetached(QDir::tempPath() + "/DNAI_UPDATER/DNAI Updater.exe", args);

#endif
    } else {
        qDebug() << "[WARNING] can't launch DNAI Updater";
    }
}

quint16 ProcessManager::findUnusedPort() const {
     QTcpServer serverTmp;
     quint16 port = 0;

     if (serverTmp.listen(QHostAddress::LocalHost, 0) == false) {
         return port;
     }
     port = serverTmp.serverPort();
     serverTmp.close();

     return port;
}

void ProcessManager::launch() {
    QSettings settingsBin(m_file, QSettings::IniFormat);

    m_updaterApp = settingsBin.value("BINARIES/updater", "").toString();
    m_updaterApp.replace("{OUT_DIR}", QGuiApplication::applicationDirPath());

    QStringList argumentsServer;
    QSystemSemaphore sem("SERVER_CORE_DNAI", 0, QSystemSemaphore::Create);

    m_port = findUnusedPort();
    if (m_port <= 0) {
        qDebug() << "no port disponible" << m_port;
        return;
    }

    QString serverPath = settingsBin.value("BINARIES/server", "").toString();
    if (serverPath.size() == 0) {
        qDebug() << "failed to launch server from file " << m_file;
        qDebug() << "DO BINARIES/server=\"./PATH/Server\" ";
        return;
    }

    serverPath.replace("{OUT_DIR}", QGuiApplication::applicationDirPath());

    argumentsServer << "-p";
    QString portStr;
    portStr.setNum(m_port);
    argumentsServer << portStr;
    argumentsServer << "-S";
    argumentsServer << sem.key();

    m_server.start(serverPath, argumentsServer);
    if (m_server.waitForStarted() == false) {
        qDebug() << "[FAILED] LAUNCH Server has failed";
        qDebug() << "[FAILED]" << serverPath;
        return;
    }

    qDebug() << "Server started on port: " << portStr;

    sem.acquire();

    QString corePath = settingsBin.value("BINARIES/core", "").toString();
    if (corePath.size() == 0) {
        qDebug() << "failed to launch core from file " << m_file;
        qDebug() << "DO BINARIES/core=\"[mono] ./PATH/CoreDaemon.exe\" ";
        return;
    }

    corePath.replace("{OUT_DIR}", QGuiApplication::applicationDirPath());

    corePath.append(" -p ");
    corePath.append(portStr);

    m_core.start(corePath);
    if (m_core.waitForStarted() == false) {
        qDebug() << "[FAILED] LAUNCH Core has failed";
        qDebug() << "[FAILED]" << corePath;
        return;
    }

    qDebug() << "PROCESSES OK !";
  //  QThread::sleep(10);
}

qint16 ProcessManager::getServerPort() {
    return m_port;
}
