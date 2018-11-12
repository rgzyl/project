#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    /*Połączenie z bazą danych i wyświetlanie informacji czy jest połaczona*/
    if(!connectOpen())
        ui->label->setText("Wstąpił nieoczekiwany problem z odtworzeniem bazy danych");
    else
        ui->label->setText("Wykryto aktywną bazę danych");
}

Login::~Login()
{
    delete ui;
}

/*Funkcja logująca nas do widoku "menu"*/
void Login::on_pushButton_clicked()
{
    QString username,password; /*deklarowanie zmiennych*/
    username=ui->lineEdit_username->text(); /*przypisywanie zmiennych do opowiednich pól w ui*/
    password=ui->lineEdit_password->text(); /*przypisywanie zmiennych do opowiednich pól w ui*/

    /*warunek sprawdzający połączenie z bazą danych*/
    if(!connectOpen())
    {
        qDebug()<<"Wstąpił nieoczekiwany problem z odtworzeniem bazy danych";
        return;
    }

    connectOpen();

    /*deklaracja zmiennej i wypakowanie danych z tabeli SQLite i przypisanie odpowiednich pół do zmiennych*/
    QSqlQuery start;
    start.prepare("select * from Loguj where Login='"+username +"' and Haslo='"+password+ "'" );

    /*pętla while, polegająca na sprawdzaniu rekurencyjnym czy wprowadzone przez nas dane są prawidłowe*/
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
            this->hide(); /*chowanie powyższej liniki tekstu*/
            Menu menu; /*otworzenie klasy i obiektu*/
            menu.setModal(true); /*metoda wykonywana alternatywnie przez funckją exec()*/
            menu.exec(); /*przejście do nowego widoku*/
        }
        if(count<1)
            ui->label->setText("Login albo hasło jest nie prawidłowe");
    }
}
