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

private:
    Ui::Ksiazki *ui;
};

#endif // KSIAZKI_H
