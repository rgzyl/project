#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <menu.h>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase kedar;

    void connectClose()
    {
        kedar.close();
        kedar.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connectOpen()
    {
        kedar=QSqlDatabase::addDatabase("QSQLITE");
        kedar.setDatabaseName("C:/Users/Admin/Desktop/projekt/kedar.db");

        if(!kedar.open())
        {
            qDebug()<<("Wstąpił nieoczekiwany problem z odtworzeniem bazy danych");
            return false;
        }
        else
        {
            qDebug()<<("Wykryto aktywną bazę danych");
            return true;
        }
    }

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
