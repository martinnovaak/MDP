#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSignalMapper>
#include <QInputDialog>
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    R(5), S(5), krok(0.0), faktor(1.0), rezim(true), velikostPole(50)
{
    setWindowTitle("MDP");
    nastavFormular();
    nastavTlacitka();
}

MainWindow::~MainWindow()
{

}

void MainWindow::nastavFormular()
{
    this->odmena = new QAction("Odměna");
    this->prekazka = new QAction("Překážka");
    this->vycistit = new QAction("Vyčistit");
    this->nastaveni = new QAction("Nastavení");
    this->nacist = new QAction("Načíst");

    menubar = new QMenuBar;
    QMenu * upravy = new QMenu("Úpravy");
    upravy->addAction(odmena);
    upravy->addAction(prekazka);
    upravy->addSeparator();
    upravy->addAction(vycistit);
    menubar->addMenu(upravy);

    QMenu * nastroje = new QMenu("Nástroje");
    nastroje->addAction(nastaveni);
    nastroje->addAction(nacist);
    menubar->addMenu(nastroje);
    setMenuBar(menubar);

    connect(prekazka, &QAction::triggered, this, [this]{rezim = false;});
    connect(odmena, &QAction::triggered, this, [this]{rezim = true;});
    connect(vycistit, &QAction::triggered, this, &MainWindow::vycisti);

    connect(nastaveni, &QAction::triggered, this, &MainWindow::nastav);
    connect(nacist, &QAction::triggered, this, &MainWindow::nacti);
}

void MainWindow::nastavTlacitka()
{
    for(int i = 0; i < tlacitka.size(); i++)
        tlacitka[i]->deleteLater();
    tlacitka.clear();
    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(stisknuto(int)));
    int index = 0;
    for (unsigned int i = 0;i<this->R;i++)
    {
       for (unsigned int j = 0;j<this->S;j++)
       {
           QPushButton *tl = new QPushButton(this);
           tl->setGeometry(j*velikostPole,i*velikostPole+27,velikostPole,velikostPole);
           nastavBarvu(tl, QColor(Qt::white));
           tl->setText("");
           tl->setProperty("typ", 0);
           tl->setProperty("odmena", 0.0);
           tl->setVisible(true);
           signalMapper->setMapping(tl, index);
           connect(tl, SIGNAL(clicked()), signalMapper, SLOT(map()));
           tlacitka.push_back(tl);
           index++;
       }
    }
    this->setFixedSize(S*velikostPole,R*velikostPole+27);
}

void MainWindow::nastavBarvu(QPushButton *tl, QColor barva)
{
    if(barva.isValid())
    {
       QString qss = QString("background-color: %1").arg(barva.name());
       tl->setStyleSheet(qss);
    }
}

void MainWindow::stisknuto(int index)
{
    QPushButton * tl = tlacitka[index];
    if(rezim)
    {
        nastavBarvu(tl, Qt::white);
        tl->setProperty("typ", 2);
        QInputDialog dialog;
        dialog.setDoubleDecimals(3);
        double odmena = dialog.getDouble(0,"Odměna", "Nastav odměnu",0.0, -2147483647, 2147483647, 3);
        tl->setProperty("odmena", odmena);
        tl->setText(QString::number(odmena));
    }
    else
    {
        if(tl->property("typ").toInt() == 1)
        {
            nastavBarvu(tl, Qt::white);
            tl->setProperty("typ", 0);
        }
        else
        {
            nastavBarvu(tl, Qt::black);
            tl->setProperty("typ", 1);
        }
        tl->setText("");
    }
}

void MainWindow::vycisti()
{
    for(int i = 0; i < tlacitka.size(); i++)
    {
        tlacitka[i]->setText("0");
        tlacitka[i]->setProperty("typ", 0);
        nastavBarvu(tlacitka[i], Qt::white);
    }
}

void MainWindow::nastav()
{
    Dialog * dialog = new Dialog(R,S,krok,faktor);
    if(dialog->exec())
    {
        this->R = dialog->getR();
        this->S = dialog->getS();
    }
    nastavTlacitka();
}


void MainWindow::nacti()
{

}

void MainWindow::vypocti()
{

}

