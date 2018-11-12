#include "czytelnicy.h"
#include "ui_czytelnicy.h"
#include "QMessageBox"

Czytelnicy::Czytelnicy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Czytelnicy)
{
    ui->setupUi(this);

    /*Połączenie z bazą danych i wyświetlanie informacji czy jest połaczona*/
    Login connect;

    if(!connect.connectOpen())
        ui->label_third->setText("Wstąpił nieoczekiwany problem z odtworzeniem bazy danych");
    else
        ui->label_third->setText("Wykryto aktywną bazę danych");
}

Czytelnicy::~Czytelnicy()
{
    delete ui;
}

/*Funkcja przycisku do zapisywania rekordu*/
void Czytelnicy::on_pushButton_clicked()
{
    Login connect;
    QString id,name,phone,mail,post_code,city,street;
    id=ui->lineEdit_ID->text();
    name=ui->lineEdit_name->text();
    phone=ui->lineEdit_phone->text();
    mail=ui->lineEdit_mail->text();
    post_code=ui->lineEdit_post_code->text();
    city=ui->lineEdit_city->text();
    street=ui->lineEdit_street->text();

    if(!connect.connectOpen())
    {
        qDebug()<<"Wstąpił nieoczekiwany problem z odtworzeniem bazy danych";
        return;
    }

    connect.connectOpen();
    QSqlQuery start;
    start.prepare("insert into Czytelnik (ID,Personalia,Telefon,Email,KodPocztowy,Miejscowosc,Adres) values ('"+id+"','"+name+"','"+phone+"','"+mail+"','"+post_code+"','"+city+"','"+street+"')");

    if(start.exec())
    {
        QMessageBox::information(this,tr("Zapisane"),tr("Zapisane"));
        connect.connectClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),start.lastError().text());
    }
}

/*Funkcja przycisku do edytowania rekordu*/
void Czytelnicy::on_pushButton_2_clicked()
{
    Login connect;
    QString id,name,phone,mail,post_code,city,street;
    id=ui->lineEdit_ID->text();
    name=ui->lineEdit_name->text();
    phone=ui->lineEdit_phone->text();
    mail=ui->lineEdit_mail->text();
    post_code=ui->lineEdit_post_code->text();
    city=ui->lineEdit_city->text();
    street=ui->lineEdit_street->text();

    if(!connect.connectOpen())
    {
        qDebug()<<"Wstąpił nieoczekiwany problem z odtworzeniem bazy danych";
        return;
    }

    connect.connectOpen();
    QSqlQuery start;
    start.prepare("update Czytelnik set ID='"+id+"', Personalia='"+name+"',Telefon='"+phone+"',Email='"+mail+"',KodPocztowy='"+post_code+"',Miejscowosc='"+city+"',Adres='"+street+"' where ID='"+id+"'" );

    if(start.exec())
    {
        QMessageBox::information(this,tr("Edytuj"),tr("Zaktualizowane"));
        connect.connectClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),start.lastError().text());
    }
}

/*Funckja przycisku do usuwanania rekordu*/
void Czytelnicy::on_pushButton_3_clicked()
{
    Login connect;
    QString id,name,phone,mail,post_code,city,street;
    id=ui->lineEdit_ID->text();
    name=ui->lineEdit_name->text();
    phone=ui->lineEdit_phone->text();
    mail=ui->lineEdit_mail->text();
    post_code=ui->lineEdit_post_code->text();
    city=ui->lineEdit_city->text();
    street=ui->lineEdit_street->text();

    if(!connect.connectOpen())
    {
        qDebug()<<"Wstąpił nieoczekiwany problem z odtworzeniem bazy danych";
        return;
    }

    connect.connectOpen();
    QSqlQuery start;
    start.prepare("delete from Czytelnik where ID='"+id+"'");

    if(start.exec())
    {
        QMessageBox::information(this,tr("Usuń"),tr("Usunięte"));
        connect.connectClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),start.lastError().text());
    }
}

/*Przycisk służący do załadowania tabeli do tableView*/
void Czytelnicy::on_pushButton_4_clicked()
{
    Login connect;
    QSqlQueryModel * model=new QSqlQueryModel();

    connect.connectOpen();
    QSqlQuery* start=new QSqlQuery(connect.kedar);

    start->prepare("select * from Czytelnik");

    start->exec();
    model->setQuery(*start);
    ui->tableView->setModel(model);

    connect.connectClose();
    qDebug()<<(model->rowCount());

}

/*Przypisywanie odpowiednim pól wartości z TableView*/
void Czytelnicy::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();

    Login connect;
    if(!connect.connectOpen())
    {
        qDebug()<<"Wstąpił nieoczekiwany problem z odtworzeniem bazy danych";
        return;
    }

    connect.connectOpen();
    QSqlQuery start;
    start.prepare("select * from Czytelnik where ID='"+val+"' or Personalia='"+val+"' or Telefon='"+val+"' or Email='"+val+"' or KodPocztowy='"+val+"' or Miejscowosc='"+val+"' or Adres='"+val+"'");

    if(start.exec())
    {
        while (start.next())
        {
            ui->lineEdit_ID->setText(start.value(0).toString());
            ui->lineEdit_name->setText(start.value(1).toString());
            ui->lineEdit_phone->setText(start.value(2).toString());
            ui->lineEdit_mail->setText(start.value(3).toString());
            ui->lineEdit_post_code->setText(start.value(4).toString());
            ui->lineEdit_city->setText(start.value(5).toString());
            ui->lineEdit_street->setText(start.value(6).toString());
        }
        connect.connectClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),start.lastError().text());
    }
}
