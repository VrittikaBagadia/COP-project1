#ifndef MAIN_CHOICE_H
#define MAIN_CHOICE_H

#include <QDialog>

namespace Ui {
class main_choice;
}

class main_choice : public QDialog
{
    Q_OBJECT

public:

    explicit main_choice(QWidget *parent = 0);
    ~main_choice();


public slots:

    void on_TwoD_to_3D_clicked();

    void on_ThreeD_to_2D_o_clicked();

    void on_ThreeD_to_2D_dr_clicked();

private:
    Ui::main_choice *ui;

};
//int threeDto2D(bool dr, char* filename){}
#endif // MAIN_CHOICE_H
