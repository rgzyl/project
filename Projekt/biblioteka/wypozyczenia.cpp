#include "wypozyczenia.h"
#include "ui_wypozyczenia.h"
#include "QMessageBox"

Wypozyczenia::Wypozyczenia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Wypozyczenia)
{
    ui->setupUi(this);

    /*Połączenie z bazą danych i wyświetlanie informacji czy jest połaczona*/
    Login connect;

    /*Ustawianie aktualnej daty*/
    ui->dateEdit->setDate(QDate::currentDate());

    /*Pola do listy rozwijanej "status"*/
    ui->comboBox_3->addItem("Oddane");
    ui->comboBox_3->addItem("Wypożyczone");

    if(!connect.connectOpen())
        ui->label_first->setText("Wstąpił nieoczekiwany problem z odtworzeniem bazy danych");
    else
        ui->label_first->setText("Wykryto aktywną bazę danych");
}

Wypozyczenia::~Wypozyczenia()
{
    delete ui;
}

/*Funkcja przycisku do zapisywania rekordu*/
void Wypozyczenia::on_pushButton_clicked()
{
    Login connect;
    QString id,name,title,status,date,comment;
    id=ui->lineEdit_ID->text();
    title=ui->comboBox->currentText();
    name=ui->comboBox_2->currentText();
    comment=ui->lineEdit_comment->text();
    status=ui->comboBox_3->currentText();
    date=ui->dateEdit->text();

    if(!connect.connectOpen())
    {
        qDebug()<<"Wstąpił nieoczekiwany problem z odtworzeniem bazy danych";
        return;
    }

    connect.connectOpen();
    QSqlQuery start;
    start.prepare("insert into Wypozyczenia (ID,Personalia,Tytul,Status,Data,Komentarz) values ('"+id+"','"+name+"','"+title+"','"+status+"','"+date+"','"+comment+"')");

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
void Wypozyczenia::on_pushButton_2_clicked()
{
    Login connect;
    QString id,name,title,status,date,comment;
    id=ui->lineEdit_ID->text();
    status=ui->comboBox_3->currentText();
    date=ui->dateEdit->text();
    title=ui->comboBox->currentText();
    name=ui->comboBox_2->currentText();
    comment=ui->lineEdit_comment->text();


    if(!connect.connectOpen())
    {
        qDebug()<<"Wstąpił nieoczekiwany problem z odtworzeniem bazy danych";
        return;
    }

    connect.connectOpen();
    QSqlQuery start;
    start.prepare("update Wypozyczenia set ID='"+id+"',Personalia='"+name+"',Tytul='"+title+"', Status='"+status+"',Data='"+date+"',Komentarz='"+comment+"' where ID='"+id+"'" );

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
void Wypozyczenia::on_pushButton_3_clicked()
{
    Login connect;
    QString id,name,title,status,date,comment;
    id=ui->lineEdit_ID->text();
    title=ui->comboBox->currentText();
    name=ui->comboBox_2->currentText();
    comment=ui->lineEdit_comment->text();
    status=ui->comboBox_3->currentText();
    date=ui->dateEdit->text();

    if(!connect.connectOpen())
    {
        qDebug()<<"Wstąpił nieoczekiwany problem z odtworzeniem bazy danych";
        return;
    }

    connect.connectOpen();
    QSqlQuery start;
    start.prepare("delete from Wypozyczenia where ID='"+id+"'");

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

/*Przycisk służący do załadowania tabeli do tableView, wyświetlenia pola comboBox dla personali i tytułów*/
void Wypozyczenia::on_pushButton_4_clicked()
{
    Login connect;
    QSqlQueryModel * model=new QSqlQueryModel();

    connect.connectOpen();
    QSqlQuery* start=new QSqlQuery(connect.kedar);

    start->prepare("select * from Wypozyczenia");

    start->exec();
    model->setQuery(*start);
    ui->tableView->setModel(model);

    connect.connectClose();
    qDebug()<<(model->rowCount());

    QSqlQueryModel * model1=new QSqlQueryModel();

    connect.connectOpen();
    QSqlQuery* start1=new QSqlQuery(connect.kedar);

    start1->prepare("select Tytul from Ksiazki");

    start1->exec();
    model1->setQuery(*start1);
    ui->comboBox->setModel(model1);

    connect.connectClose();
    qDebug()<<(model1->rowCount());

    QSqlQueryModel * model2=new QSqlQueryModel();

    connect.connectOpen();
    QSqlQuery* start2=new QSqlQuery(connect.kedar);

    start2->prepare("select Personalia from Czytelnik");

    start2->exec();
    model2->setQuery(*start2);
    ui->comboBox_2->setModel(model2);

    connect.connectClose();
    qDebug()<<(model2->rowCount());
}

/*Przypisywanie odpowiednim pól wartości z TableView*/
void Wypozyczenia::on_tableView_activated(const QModelIndex &index)
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
    start.prepare("select * from Wypozyczenia where ID='"+val+"' or Personalia='"+val+"' or Tytul='"+val+"' or Status='"+val+"' or Data='"+val+"' or Komentarz='"+val+"'");

    if(start.exec())
    {
        while (start.next())
        {
            ui->lineEdit_ID->setText(start.value(0).toString());
            ui->comboBox_2->setCurrentText(start.value(1).toString());
            ui->comboBox->setCurrentText(start.value(2).toString());
            ui->comboBox_3->setCurrentText(start.value(3).toString());
            ui->dateEdit->setDate(start.value(4).toDate());
            ui->lineEdit_comment->setText(start.value(5).toString());
        }
        connect.connectClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),start.lastError().text());
    }
}
