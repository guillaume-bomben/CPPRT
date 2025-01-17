#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <QMessageBox>
#include <QThread> // Pour gérer les pauses courtes

ClientWindow::ClientWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::ClientWindow), socket(new QTcpSocket(this)) {
    // Configure l'interface utilisateur
    ui->setupUi(this);

    // Initialisation de l'état de la connexion
    ui->statusLabel->setText("Déconnecté");

    // Connexion des boutons
    connect(ui->connectButton, &QPushButton::clicked, this, &ClientWindow::connectToServer);
    connect(ui->sendButton, &QPushButton::clicked, this, &ClientWindow::sendMessage);
    connect(ui->wizzButton, &QPushButton::clicked, this, &ClientWindow::sendWizz);

    // Connexion des signaux du socket
    connect(socket, &QTcpSocket::connected, this, &ClientWindow::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &ClientWindow::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &ClientWindow::onReadyRead);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, &ClientWindow::onSocketError);
}

ClientWindow::~ClientWindow() {
    delete ui;
}

void ClientWindow::connectToServer() {
    QString host = ui->hostLineEdit->text();
    quint16 port = ui->portLineEdit->text().toUShort();

    if (host.isEmpty() || port == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une adresse IP et un port valides.");
        return;
    }

    ui->statusLabel->setText("Connexion en cours...");
    socket->connectToHost(host, port);
}

void ClientWindow::onConnected() {
    ui->statusLabel->setText("Connecté");
    ui->chatTextEdit->append("Connecté au serveur.");

    // Envoyer le nom d'utilisateur au serveur
    QString username = ui->usernameLineEdit->text().trimmed();
    if (!username.isEmpty()) {
        socket->write(username.toUtf8() + "\n");
    } else {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un nom d'utilisateur.");
    }
}

void ClientWindow::onDisconnected() {
    ui->statusLabel->setText("Déconnecté");
    ui->chatTextEdit->append("Déconnecté du serveur.");
}

void ClientWindow::onReadyRead() {
    QByteArray data = socket->readAll();
    QString message = QString(data).trimmed();

    if (message == "WIZZ") {
        vibrateWindow();
    } else {
        ui->chatTextEdit->append(message);
    }
}

void ClientWindow::onSocketError(QAbstractSocket::SocketError error) {
    Q_UNUSED(error);
    QMessageBox::critical(this, "Erreur", socket->errorString());
    ui->statusLabel->setText("Déconnecté");
}

void ClientWindow::sendMessage() {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        QString message = ui->messageLineEdit->text().trimmed();
        if (!message.isEmpty()) {
            socket->write(message.toUtf8() + "\n");
            ui->chatTextEdit->append("Moi : " + message);
            ui->messageLineEdit->clear();
        }
    } else {
        QMessageBox::warning(this, "Erreur", "Vous n'êtes pas connecté au serveur.");
    }
}

void ClientWindow::sendWizz() {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write("WIZZ\n");
    } else {
        QMessageBox::warning(this, "Erreur", "Vous n'êtes pas connecté au serveur.");
    }
}

void ClientWindow::vibrateWindow() {
    // Faire vibrer la fenêtre en déplaçant légèrement sa position
    QPoint originalPos = this->pos();

    for (int i = 0; i < 10; ++i) {
        int offset = (i % 2 == 0) ? 10 : -10;
        this->move(originalPos.x() + offset, originalPos.y());
        QThread::msleep(30); // Pause pour donner l'effet de vibration
    }

    // Revenir à la position d'origine
    this->move(originalPos);
}
