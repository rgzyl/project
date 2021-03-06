#ifndef KSIAZKI_H
#define KSIAZKI_H

#include <QDialog>
#include "login.h"

namespace Ui {
class Ksiazki;
}

class Ksiazki : public QDialog
{
    Q_OBJECT

public:
    explicit Ksiazki(QWidget *parent = nullptr);
    ~Ksiazki();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::Ksiazki *ui;
};

#endif // KSIAZKI_H
