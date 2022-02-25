#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    unsigned int R, S;
    double krok, faktor;

    QVector <QPushButton *> tlacitka;

    QMenuBar * menubar;
    QAction * odmena;
    QAction * prekazka;
    QAction * vycistit;
    QAction * nastaveni;
    QAction * nacist;
    QAction * vyres;

    bool rezim; // odmena = true, prekazka = false
    unsigned int velikostPole;

    void nastavFormular();
    void nastavTlacitka();

    void nastavBarvu(QPushButton * tl, QColor barva);

private slots:
    void stisknuto(int index);
    void vycisti();
    void nastav();
    void nacti();
    void vypocti();
};
#endif // MAINWINDOW_H
