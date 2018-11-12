#ifndef CZYTELNICY_H
#define CZYTELNICY_H

#include <QDialog>
#include "login.h"

namespace Ui {
class Czytelnicy;
}

class Czytelnicy : public QDialog
{
    Q_OBJECT

public:
    explicit Czytelnicy(QWidget *parent = nullptr);
    ~Czytelnicy();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::Czytelnicy *ui;
};

#endif // CZYTELNICY_H
