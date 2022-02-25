#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
class QLabel;
class QSpinBox;
class QPushButton;

class Dialog : public QDialog
{
    Q_OBJECT
private:
    unsigned int R, S;
    QLabel * labelR;
    QLabel * labelS;
    QSpinBox * spinboxR;
    QSpinBox * spinboxS;
    QPushButton * konec;
public:
    explicit Dialog(QWidget*parent = nullptr);
    void setRS(int a, int b){this->R = a; this->S = b;};
    unsigned int getR(){return R;};
    unsigned int getS(){return S;};
private slots:
    void stisknuto();
};

#endif // DIALOG_H
