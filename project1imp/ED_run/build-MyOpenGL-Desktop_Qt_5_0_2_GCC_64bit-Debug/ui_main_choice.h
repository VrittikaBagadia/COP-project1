/********************************************************************************
** Form generated from reading UI file 'main_choice.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_CHOICE_H
#define UI_MAIN_CHOICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_main_choice
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QRadioButton *ThreeD_to_2D_o;
    QRadioButton *ThreeD_to_2D_dr;
    QRadioButton *TwoD_to_3D;

    void setupUi(QDialog *main_choice)
    {
        if (main_choice->objectName().isEmpty())
            main_choice->setObjectName(QStringLiteral("main_choice"));
        main_choice->resize(400, 300);
        widget = new QWidget(main_choice);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(120, 70, 196, 83));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ThreeD_to_2D_o = new QRadioButton(widget);
        ThreeD_to_2D_o->setObjectName(QStringLiteral("ThreeD_to_2D_o"));

        verticalLayout->addWidget(ThreeD_to_2D_o);

        ThreeD_to_2D_dr = new QRadioButton(widget);
        ThreeD_to_2D_dr->setObjectName(QStringLiteral("ThreeD_to_2D_dr"));

        verticalLayout->addWidget(ThreeD_to_2D_dr);

        TwoD_to_3D = new QRadioButton(widget);
        TwoD_to_3D->setObjectName(QStringLiteral("TwoD_to_3D"));

        verticalLayout->addWidget(TwoD_to_3D);


        retranslateUi(main_choice);

        QMetaObject::connectSlotsByName(main_choice);
    } // setupUi

    void retranslateUi(QDialog *main_choice)
    {
        main_choice->setWindowTitle(QApplication::translate("main_choice", "Dialog", 0));
        ThreeD_to_2D_o->setText(QApplication::translate("main_choice", "3D to 2D orthographic", 0));
        ThreeD_to_2D_dr->setText(QApplication::translate("main_choice", "3D to 2D Direction ratios", 0));
        TwoD_to_3D->setText(QApplication::translate("main_choice", "2D to 3D", 0));
    } // retranslateUi

};

namespace Ui {
    class main_choice: public Ui_main_choice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_CHOICE_H
