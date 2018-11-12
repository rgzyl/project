#ifndef WYPOZYCZENIA_H
#define WYPOZYCZENIA_H

#include <QDialog>
#include "login.h"

namespace Ui {
class Wypozyczenia;
}

class Wypozyczenia : public QDialog
{
    Q_OBJECT

public:
    explicit Wypozyczenia(QWidget *parent = nullptr);
    ~Wypozyczenia();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::Wypozyczenia *ui;
};

#endif // WYPOZYCZENIA_H
