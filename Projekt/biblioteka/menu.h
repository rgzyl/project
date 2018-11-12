#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <ksiazki.h>
#include <wypozyczenia.h>
#include <czytelnicy.h>
#include <login.h>

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
