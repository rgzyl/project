#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    if(!connectOpen())
        ui->label->setText("Wstąpił nieoczekiwany problem z odtworzeniem bazy danych");
    else
        ui->label->setText("Wykryto aktywną bazę danych");
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    QString username,password;
    username=ui->lineEdit_username->text();
    password=ui->lineEdit_password->text();

    if(!connectOpen())
    {
        qDebug()<<"Wstąpił nieoczekiwany problem z odtworzeniem bazy danych";
        return;
    }

    connectOpen();
    QSqlQuery start;
    start.prepare("select * from Loguj where Login='"+username +"' and Haslo='"+password+ "'" );

    if(start.exec())
    {
        int count=0;
        while(start.next())
        {
            count++;
        }
        if(count==1)
        {
            ui->label->setText("Login i hasło jest prawidłowe");
            this->hide();
            Ksiazki ksiazki;
            ksiazki.setModal(true);
            ksiazki.exec();
        }
        if(count<1)
            ui->label->setText("Login albo hasło jest nie prawidłowe");
    }
}
