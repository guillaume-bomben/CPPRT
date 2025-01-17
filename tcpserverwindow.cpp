#include "tcpserverwindow.h"

TcpServerWindow::TcpServerWindow(QWidget *parent)
    : QWidget(parent), server(new QTcpServer(this)) {
    // Configuration de l'interface graphique
    QVBoxLayout *layout = new QVBoxLayout(this);

    statusLabel = new QLabel("Serveur arrêté", this);
    logTextEdit = new QTextEdit(this);
    logTextEdit->setReadOnly(true);
    startButton = new QPushButton("Démarrer le serveur", this);

    layout->addWidget(statusLabel);
    layout->addWidget(logTextEdit);
    layout->addWidget(startButton);

    setLayout(layout);
    setWindowTitle("Serveur TCP");

    // Connecter le bouton de démarrage
    connect(startButton, &QPushButton::clicked, this, &TcpServerWindow::startServer);

    // Connecter les signaux du serveur
    connect(server, &QTcpServer::newConnection, this, &TcpServerWindow::onNewConnection);
}

void TcpServerWindow::startServer() {
    if (server->listen(QHostAddress::Any, 12345)) {
        logMessage("Serveur démarré sur le port 12345.");
        statusLabel->setText("Serveur en cours d'exécution...");
        startButton->setEnabled(false);
    } else {
        logMessage("Erreur : Impossible de démarrer le serveur.");
    }
}

void TcpServerWindow::onNewConnection() {
    QTcpSocket *clientSocket = server->nextPendingConnection();
    clients.append(clientSocket);

    logMessage("Nouvelle connexion de : " + clientSocket->peerAddress().toString());

    // Connecter les signaux du client
    connect(clientSocket, &QTcpSocket::readyRead, this, &TcpServerWindow::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &TcpServerWindow::onClientDisconnected);
}

void TcpServerWindow::onClientDisconnected() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (clientSocket) {
        logMessage("Client déconnecté : " + clientSocket->peerAddress().toString());
        clients.removeAll(clientSocket);
        clientUsernames.remove(clientSocket);
        clientSocket->deleteLater();
    }
}

void TcpServerWindow::onReadyRead() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (clientSocket) {
        QByteArray data = clientSocket->readAll();
        QString message = QString(data).trimmed();

        // Enregistrement du nom d'utilisateur si absent
        if (!clientUsernames.contains(clientSocket)) {
            clientUsernames[clientSocket] = message; // Premier message envoyé = nom d'utilisateur
            logMessage("Nom d'utilisateur enregistré : " + message);
            clientSocket->write("Nom d'utilisateur enregistré.\n");
            return;
        }

        QString username = clientUsernames[clientSocket];

        // Gestion des messages
        if (message == "WIZZ") {
            logMessage("WIZZ reçu de : " + username);

            // Diffuse le Wizz à tous les autres clients
            for (QTcpSocket *client : clients) {
                if (client != clientSocket) {
                    client->write("WIZZ\n");
                }
            }
        } else {
            logMessage(username + " : " + message);

            // Diffuse le message aux autres clients
            for (QTcpSocket *client : clients) {
                if (client != clientSocket) {
                    client->write(username.toUtf8() + " : " + message.toUtf8() + "\n");
                }
            }
        }
    }
}

void TcpServerWindow::logMessage(const QString &message) {
    logTextEdit->append(message);
}
