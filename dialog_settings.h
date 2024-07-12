#ifndef DIALOG_SETTINGS_H
#define DIALOG_SETTINGS_H

#include <QDialog>
#include <QtNetwork/QUdpSocket> // Библиотека для работы с UDP
#include <QRegExp> // Библиотеки для проверки IP
#include <QRegExpValidator>
#include <QIntValidator> // Библиотека для проверки порта
#include <QNetworkInterface> // Библиотека для вывода локального IP
#include <QMessageBox>
#include <QVector>

namespace Ui {
class Dialog_settings;
}

class Dialog_settings : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_settings(QWidget *parent = nullptr);
    ~Dialog_settings();

    int port, our_port;

    QString adress, nick;

    bool connected;

    QString getIP();

    QString getNick();

    int getPort();

    int getOurPort();

    void setIP(QString new_adress_string);

    void setNick(QString new_nick);

    void setPort(int new_port);

    void setOurPort(int new_our_port);

public slots:

    void getAdress();

    bool checkAdress();

    bool checkPorts();

    bool checkNickname();

    void printAdress(QString print_adress);

    void printPort(int print_port);

    void printOurPort(int print_our_port);

    void printNick(QString print_nick);

    void setIpRegex(QRegExp new_ipRegex);

    QRegExp getIpRegex();

private slots:
    void on_pushButton_Create_clicked();

private:
    Ui::Dialog_settings *ui;

    QRegExpValidator *ipValidator;

    QValidator *portValidator;

    QRegExp ipRegex;

};

#endif // DIALOG_SETTINGS_H
