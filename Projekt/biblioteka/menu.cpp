#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    Login connect;

    if(!connect.connectOpen())
        ui->label_fourth->setText("Wstąpił nieoczekiwany problem z odtworzeniem bazy danych");
    else
        ui->label_fourth->setText("Wykryto aktywną bazę danych");
}

Menu::~Menu()
{
    delete ui;
}

/*przycisk polegający na przejściu do widoku książki*/
void Menu::on_pushButton_clicked()
{
    Ksiazki ksiazki; /*otworzenie klasy i obiektu*/
    ksiazki.setModal(true); /*metoda wykonywana alternatywnie przez funckją exec()*/
    ksiazki.exec(); /*przejście do nowego widoku*/
}

/*przycisk polegający na przejściu do widoku czytelnicy*/
void Menu::on_pushButton_2_clicked()
{
    Czytelnicy czytelnicy; /*otworzenie klasy i obiektu*/
    czytelnicy.setModal(true); /*metoda wykonywana alternatywnie przez funckją exec()*/
    czytelnicy.exec(); /*przejście do nowego widoku*/
}

/*przycisk polegający na przejściu do widoku wypożyczenia*/
void Menu::on_pushButton_3_clicked()
{
    Wypozyczenia wypozyczenia; /*otworzenie klasy i obiektu*/
    wypozyczenia.setModal(true); /*metoda wykonywana alternatywnie przez funckją exec()*/
    wypozyczenia.exec(); /*przejście do nowego widoku*/
}
