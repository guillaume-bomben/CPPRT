#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <QTcpSocket>
#include <QThread>

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QWidget {
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

private slots:
    void connectToServer();
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void sendMessage();
    void sendWizz();
    void onSocketError(QAbstractSocket::SocketError error);

private:
    Ui::ClientWindow *ui;
    QTcpSocket *socket;

    void vibrateWindow(); // Méthode pour faire vibrer la fenêtre
};

#endif // CLIENTWINDOW_H
