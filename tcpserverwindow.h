#ifndef TCPSERVERWINDOW_H
#define TCPSERVERWINDOW_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QHash>

class TcpServerWindow : public QWidget {
    Q_OBJECT

public:
    explicit TcpServerWindow(QWidget *parent = nullptr);

private slots:
    void startServer();
    void onNewConnection();
    void onReadyRead();
    void onClientDisconnected();

private:
    void logMessage(const QString &message);

    QTcpServer *server;
    QLabel *statusLabel;
    QTextEdit *logTextEdit;
    QPushButton *startButton;

    QList<QTcpSocket *> clients;
    QHash<QTcpSocket*, QString> clientUsernames; // Stockage des noms d'utilisateur
};

#endif // TCPSERVERWINDOW_H
