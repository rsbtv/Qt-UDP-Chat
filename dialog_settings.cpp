#include "dialog_settings.h"
#include "ui_dialog_settings.h"

Dialog_settings::Dialog_settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_settings) // конструктор
{
    ui->setupUi(this);

    // Контроль ввода IP-адреса
    QString ipRange = "(([ 0]+)|([ 0]*[0-9] *)|([0-9][0-9] )|([ 0][0-9][0-9])|(1[0-9][0-9])|([2][0-4][0-9])|(25[0-5]))";
    QRegExp new_ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");
    ipValidator = new QRegExpValidator(new_ipRegex, this);
    ui->lineEdit_Adress->setValidator(ipValidator);
//    ui->lineEdit_Adress->setInputMask("000.000.000.000");
    ui->lineEdit_Adress->setCursorPosition(0);

    // Контроль ввода портов
    portValidator = new QIntValidator(1, 65536, this);
    ui->lineEdit_Port->setValidator(portValidator);
    ui->lineEdit_Our_Port->setValidator(portValidator);

    // Выставляем наш IP
//    ui->label_myAdress->setText(getAdress());

    getAdress();

    setIpRegex(new_ipRegex);

    setWindowTitle("Настройки");

    connected = false;
}

Dialog_settings::~Dialog_settings() // деструктор
{
    delete ui;

    delete ipValidator;

    delete portValidator;
}

void Dialog_settings::setIpRegex(QRegExp new_ipRegex) // сеттер шаблона для валидатора
{
    ipRegex = new_ipRegex;
}

QRegExp Dialog_settings::getIpRegex() // геттер шаблона для валидатора
{
    return ipRegex;
}

void Dialog_settings::printNick(QString print_nick) // записать наш ник при повторном посещении окна
{
    ui->lineEdit_Nick->setText(print_nick);
}

void Dialog_settings::printPort(int print_port) // записать порт при повторном посещении окна
{
    ui->lineEdit_Port->setText(QString::number(print_port));
}

void Dialog_settings::printAdress(QString print_adress) // записать адрес при повторном посещении окна
{
    ui->lineEdit_Adress->setText(print_adress);
}

void Dialog_settings::printOurPort(int print_our_port) // записать наш порт при повторном посещении окна
{
    ui->lineEdit_Our_Port->setText(QString::number(print_our_port));
}

QString Dialog_settings::getIP() // геттер адреса
{
    return adress;
}

void Dialog_settings::setIP(QString new_adress_string) // сеттер адреса
{
    adress = new_adress_string;
}

int Dialog_settings::getPort() // геттер порта
{
    return port;
}

void Dialog_settings::setPort(int new_port) // сеттер порта
{
    port = new_port;
}

int Dialog_settings::getOurPort() // геттер нашего порта
{
    return our_port;
}

void Dialog_settings::setOurPort(int new_our_port) // сеттер нашего порта
{
    our_port = new_our_port;
}

bool Dialog_settings::checkAdress() // проверка IP адреса
{
//    if (ui->lineEdit_Adress->text().length() > 6 and ui->lineEdit_Adress->text().length() < 16)
//        return true;
//    else
//        return false;
    if (getIpRegex().exactMatch(ui->lineEdit_Adress->text()))
        return true;
    else
        return false;
}

QString Dialog_settings::getNick() // геттер никнейма
{
    return nick;
}

void Dialog_settings::setNick(QString new_nick) // сеттер никнейма
{
    nick = new_nick;
}

bool Dialog_settings::checkPorts() // проверка портов
{
    int port = ui->lineEdit_Port->text().toInt();
    int our_port = ui->lineEdit_Our_Port->text().toInt();

    if (port > 0 and our_port > 0)
        return true;
    else
        return false;
}

bool Dialog_settings::checkNickname() // проверка никнейма
{
    if (ui->lineEdit_Nick->text().isEmpty())
        return false;
    else
        return true;
}

void Dialog_settings::getAdress() // Функция для получения нашего IP
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();

    for(int i = 0; i < list.count(); i++)
    {
        if(!list[i].isLoopback())
            if (list[i].protocol() == QAbstractSocket::IPv4Protocol )
                ui->comboBox->addItem(list[i].toString());
    }
}

void Dialog_settings::on_pushButton_Create_clicked() // нажата кнопка создать
{
    if (checkPorts() and checkAdress() and checkNickname())
    {
        setIP(ui->lineEdit_Adress->text());
        setPort(ui->lineEdit_Port->text().toInt());
        setOurPort(ui->lineEdit_Our_Port->text().toInt());
        setNick(ui->lineEdit_Nick->text());

        ui->lineEdit_Nick->setEnabled(false);
        ui->lineEdit_Port->setEnabled(false);
        ui->lineEdit_Adress->setEnabled(false);
        ui->lineEdit_Our_Port->setEnabled(false);
        ui->pushButton_Create->setEnabled(false);

        connected = true;

        Dialog_settings::close();
    }
    else
        QMessageBox::information(this, "Ошибка", "Неверно введены данные", QMessageBox::Ok);
}
