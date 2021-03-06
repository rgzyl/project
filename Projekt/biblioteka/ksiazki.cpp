#include "ksiazki.h"
#include "ui_ksiazki.h"
#include "QMessageBox"

Ksiazki::Ksiazki(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ksiazki)
{
    ui->setupUi(this);

    /*Połączenie z bazą danych i wyświetlanie informacji czy jest połaczona*/
    Login connect;

    if(!connect.connectOpen())
        ui->label_second->setText("Wstąpił nieoczekiwany problem z odtworzeniem bazy danych");
    else
        ui->label_second->setText("Wykryto aktywną bazę danych");
}

Ksiazki::~Ksiazki()
{
    delete ui;
}

/*Funkcja przycisku do zapisywania rekordu*/
void Ksiazki::on_pushButton_clicked()
{
    Login connect;
    QString id,title,author,release_date,book_genre;
    id=ui->lineEdit_ID->text();
    title=ui->lineEdit_title->text();
    author=ui->lineEdit_author->text();
    release_date=ui->lineEdit_release_date->text();
    book_genre=ui->lineEdit_book_genre->text();

    if(!connect.connectOpen())
    {
        qDebug()<<"Wstąpił nieoczekiwany problem z odtworzeniem bazy danych";
        return;
    }

    connect.connectOpen();
    QSqlQuery start;
    start.prepare("insert into Ksiazki (Id,Tytul,Autor,RokWydania,Gatunek) values ('"+id+"','"+title+"','"+author+"','"+release_date+"','"+book_genre+"')");

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
void Ksiazki::on_pushButton_2_clicked()
{
    Login connect;
    QString id,title,author,release_date,book_genre;
    id=ui->lineEdit_ID->text();
    title=ui->lineEdit_title->text();
    author=ui->lineEdit_author->text();
    release_date=ui->lineEdit_release_date->text();
    book_genre=ui->lineEdit_book_genre->text();

    if(!connect.connectOpen())
    {
        qDebug()<<"Wstąpił nieoczekiwany problem z odtworzeniem bazy danych";
        return;
    }

    connect.connectOpen();
    QSqlQuery start;
    start.prepare("update Ksiazki set ID='"+id+"', Tytul='"+title+"',Autor='"+author+"',RokWydania='"+release_date+"',Gatunek='"+book_genre+"' where ID='"+id+"'" );

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
void Ksiazki::on_pushButton_3_clicked()
{
    Login connect;
    QString id,title,author,release_date,book_genre;
    id=ui->lineEdit_ID->text();
    title=ui->lineEdit_title->text();
    author=ui->lineEdit_author->text();
    release_date=ui->lineEdit_release_date->text();
    book_genre=ui->lineEdit_book_genre->text();

    if(!connect.connectOpen())
    {
        qDebug()<<"Wstąpił nieoczekiwany problem z odtworzeniem bazy danych";
        return;
    }

    connect.connectOpen();
    QSqlQuery start;
    start.prepare("delete from Ksiazki where ID='"+id+"'");

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
void Ksiazki::on_pushButton_4_clicked()
{
    Login connect;
    QSqlQueryModel * model=new QSqlQueryModel();

    connect.connectOpen();
    QSqlQuery* start=new QSqlQuery(connect.kedar);

    start->prepare("select * from Ksiazki");

    start->exec();
    model->setQuery(*start);
    ui->tableView->setModel(model);

    connect.connectClose();
    qDebug()<<(model->rowCount());
}

/*Przypisywanie odpowiednim pól wartości z TableView*/
void Ksiazki::on_tableView_activated(const QModelIndex &index)
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
    start.prepare("select * from Ksiazki where ID='"+val+"' or Tytul='"+val+"' or Autor='"+val+"' or RokWydania='"+val+"' or Gatunek='"+val+"'");

    if(start.exec())
    {
        while (start.next())
        {
            ui->lineEdit_ID->setText(start.value(0).toString());
            ui->lineEdit_title->setText(start.value(1).toString());
            ui->lineEdit_author->setText(start.value(2).toString());
            ui->lineEdit_release_date->setText(start.value(3).toString());
            ui->lineEdit_book_genre->setText(start.value(4).toString());
        }
        connect.connectClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),start.lastError().text());
    }
}
