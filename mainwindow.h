#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QUdpSocket> // Библиотека для работы с UDP
#include <QNetworkInterface> // Библиотека для вывода локального IP
#include <dialog_emoji.h>
#include <dialog_settings.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setSettings();

public slots:
//    printEmojis(QString new_emoji);

private slots:
    void read_data(void); // слот для обработки поступивших данных

    void on_pushButton_Send_Mes_clicked();

    void on_pushButton_Settings_clicked();

    void on_pushButton_Emoji_clicked();

    void printEmojis(QString new_emoji);

private:
    Ui::MainWindow *ui;
    QUdpSocket * udpsocket; // сам UDP сокет (указатель на него)
    QHostAddress * adress; // для адреса
    int port, our_port; // порты для связи
    QString string_adress, nick;
    bool first;

};
#endif // MAINWINDOW_H
