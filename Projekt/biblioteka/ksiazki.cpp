#include "ksiazki.h"
#include "ui_ksiazki.h"

Ksiazki::Ksiazki(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ksiazki)
{
    ui->setupUi(this);
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
