#include "dialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

Dialog::Dialog(unsigned int R, unsigned int S, double krok, double faktor)
    : R(R), S(S), krok(krok), faktor(faktor)
{
    QVBoxLayout * layout = new QVBoxLayout();

    QHBoxLayout * prvniradka = new QHBoxLayout();
    labelR = new QLabel("Počet řádek");
    spinboxR = new QSpinBox();
    spinboxR->setMinimum(3);
    spinboxR->setValue(R);
    prvniradka->addWidget(labelR);
    prvniradka->addWidget(spinboxR);
    layout->addLayout(prvniradka);

    QHBoxLayout * druharadka = new QHBoxLayout();
    labelS = new QLabel("Počet sloupců");
    spinboxS = new QSpinBox();
    spinboxS->setMinimum(3);
    spinboxS->setValue(S);
    druharadka->addWidget(labelS);
    druharadka->addWidget(spinboxS);
    layout->addLayout(druharadka);

    QHBoxLayout * tretiradka = new QHBoxLayout();
    labelKrok = new QLabel("Cena kroku");
    spinboxKrok = new QDoubleSpinBox();
    spinboxKrok->setMinimum(0.0);
    spinboxKrok->setValue(krok);
    spinboxKrok->setSingleStep(0.01);
    tretiradka->addWidget(labelKrok);
    tretiradka->addWidget(spinboxKrok);
    layout->addLayout(tretiradka);

    QHBoxLayout * ctvrtaradka = new QHBoxLayout();
    labelFaktor = new QLabel("Diskontní faktor");
    spinboxFaktor = new QDoubleSpinBox();
    spinboxFaktor->setMinimum(0.0);
    spinboxFaktor->setMaximum(1.0);
    spinboxFaktor->setSingleStep(0.01);
    spinboxFaktor->setValue(faktor);
    ctvrtaradka->addWidget(labelFaktor);
    ctvrtaradka->addWidget(spinboxFaktor);
    layout->addLayout(ctvrtaradka);

    konec = new QPushButton("Vrať se zpět");
    layout->addWidget(konec);
    this->setLayout(layout);
    connect(konec, &QPushButton::clicked, this, &Dialog::stisknuto);
}

void Dialog::stisknuto()
{
    setRS(spinboxR->value(), spinboxS->value());
    setKF(spinboxKrok->value(), spinboxFaktor->value());
    accept();
}
