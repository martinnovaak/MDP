#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
class QLabel;
class QSpinBox;
class QPushButton;
class QDoubleSpinBox;

class Dialog : public QDialog
{
    Q_OBJECT
private:
    unsigned int R, S;
    double krok, faktor;
    QLabel * labelR;
    QLabel * labelS;
    QLabel * labelKrok;
    QLabel * labelFaktor;
    QSpinBox * spinboxR;
    QSpinBox * spinboxS;
    QDoubleSpinBox * spinboxKrok;
    QDoubleSpinBox * spinboxFaktor;
    QPushButton * konec;
public:
    explicit Dialog(unsigned int R, unsigned int S, double krok, double faktor);
    void setRS(int a, int b){this->R = a; this->S = b;};
    void setKF(double k, double f){krok = k; faktor = f;};
    unsigned int getR(){return R;};
    unsigned int getS(){return S;};
    double getKrok(){return krok;};
    double getFaktor(){return faktor;};
private slots:
    void stisknuto();
};

#endif // DIALOG_H
