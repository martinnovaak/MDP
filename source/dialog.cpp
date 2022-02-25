#include "dialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

Dialog::Dialog(QWidget *parent)  : QDialog(parent)
{
    QVBoxLayout * layout = new QVBoxLayout();
    QHBoxLayout * prvniradka = new QHBoxLayout();
    labelR = new QLabel("Počet řádek");
    spinboxR = new QSpinBox();
    spinboxR->setMinimum(3);
    spinboxR->setValue(5);
    prvniradka->addWidget(labelR);
    prvniradka->addWidget(spinboxR);
    layout->addLayout(prvniradka);
    QHBoxLayout * druharadka = new QHBoxLayout();
    labelS = new QLabel("Počet sloupců");
    spinboxS = new QSpinBox();
    spinboxS->setMinimum(3);
    spinboxS->setValue(5);
    druharadka->addWidget(labelS);
    druharadka->addWidget(spinboxS);
    layout->addLayout(druharadka);
    konec = new QPushButton("Vrať se zpět");
    layout->addWidget(konec);
    this->setLayout(layout);
    connect(konec, &QPushButton::clicked, this, &Dialog::stisknuto);
}

void Dialog::stisknuto()
{
    setRS(spinboxR->value(), spinboxS->value());
    accept();
}
