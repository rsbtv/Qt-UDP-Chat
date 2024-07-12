#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) // конструктор
{
    ui->setupUi(this);

    ui->pushButton_Send_Mes->setVisible(false);
    ui->textEdit_Input->setReadOnly(true);

    first = true;
    setWindowTitle("UDP Чат");
}

MainWindow::~MainWindow() // деструктор
{
    delete ui;
    delete udpsocket;
    delete adress;
}

void MainWindow::read_data() // обработка поступивших данных
{
    char * data;
    int size;
    size = int(udpsocket->pendingDatagramSize()); // уточняем объем данных в очереди
    if (size > 0)
    {
        data = new char [size+1];
        udpsocket->readDatagram(data, size); // читаем данные
        data[size] = 0; // завершающий 0 - признак конца строки ( так как передаем строки). Можно терминировать нулем при передаче (даже правильнее)
        QString stroka;
        stroka = QString::fromUtf8(data, size);
        ui->textEdit_Input->append(stroka);
        delete [] data;
    }
}

void MainWindow::on_pushButton_Send_Mes_clicked() // отправка сообщения
{
    //    char * data;
    QString message = ui->lineEdit_Send_Mes->text().toUtf8();
    QByteArray ba;
    ba.append(nick + ": ");
    ba.append(message);
    int size = ba.size();
    int nick_size = nick.size() + 2;
    if (size > nick_size)
    {
        udpsocket->writeDatagram(ba, size, *adress, quint16(port)); // отправка сообщения узлу с указанным адресом на указанный порт
        ui->textEdit_Input->append(nick + ": "  + ui->lineEdit_Send_Mes->text());
    }
}

void MainWindow::on_pushButton_Settings_clicked() // нажата кнопка настроек
{
    Dialog_settings dialog;
    if (!first)
    {
        dialog.printNick(nick);
        dialog.printPort(port);
        dialog.printAdress(string_adress);
        dialog.printOurPort(our_port);
    }
    dialog.exec();

    if (dialog.connected)
    {
        ui->pushButton_Send_Mes->setVisible(true);
        // получаем настройки
        string_adress = dialog.getIP();
        port = dialog.getPort();
        our_port = dialog.getOurPort();
        nick = dialog.getNick();
        first = false;

        udpsocket = new QUdpSocket(this);
        udpsocket->abort();
        udpsocket->bind(QHostAddress::Any, quint16(our_port)); // включаем привязку сокета к порту our_port и принимаем сообщения с любых адресов
        connect(udpsocket, &QUdpSocket::readyRead, this, &MainWindow::read_data); // соединяем сигнал готовности данных с нашим слотом обработки

        adress = new QHostAddress();
        adress->setAddress(string_adress);
    }

}

void MainWindow::printEmojis(QString new_emoji) // вывод эмоджи в лайн эдит
{
    ui->lineEdit_Send_Mes->setText(ui->lineEdit_Send_Mes->text() + new_emoji);
}

void MainWindow::on_pushButton_Emoji_clicked() // нажата кнопка выбора эмоджи
{
    Dialog_emoji dialog;
    connect(&dialog, SIGNAL(newEmoji(QString)), this, SLOT(printEmojis(QString)));
    dialog.exec();
}
