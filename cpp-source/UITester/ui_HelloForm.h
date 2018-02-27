/********************************************************************************
** Form generated from reading UI file 'HelloForm.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELLOFORM_H
#define UI_HELLOFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_HelloForm
{
public:
    QLabel *label;
    QLineEdit *helloEdit;
    QGroupBox *groupBox;
    QPushButton *pbTopLaneL;
    QPushButton *pbTopLaneM;
    QPushButton *pbTopLaneR;
    QPushButton *pbOutHole;
    QPushButton *pbTilt;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *HelloForm)
    {
        if (HelloForm->objectName().isEmpty())
            HelloForm->setObjectName(QString::fromUtf8("HelloForm"));
        HelloForm->resize(665, 468);
        label = new QLabel(HelloForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 361, 18));
        helloEdit = new QLineEdit(HelloForm);
        helloEdit->setObjectName(QString::fromUtf8("helloEdit"));
        helloEdit->setEnabled(true);
        helloEdit->setGeometry(QRect(20, 80, 361, 31));
        helloEdit->setFrame(false);
        helloEdit->setReadOnly(true);
        groupBox = new QGroupBox(HelloForm);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(40, 130, 481, 141));
        pbTopLaneL = new QPushButton(groupBox);
        pbTopLaneL->setObjectName(QString::fromUtf8("pbTopLaneL"));
        pbTopLaneL->setGeometry(QRect(10, 20, 81, 27));
        pbTopLaneL->setCheckable(false);
        pbTopLaneM = new QPushButton(groupBox);
        pbTopLaneM->setObjectName(QString::fromUtf8("pbTopLaneM"));
        pbTopLaneM->setGeometry(QRect(100, 20, 81, 27));
        pbTopLaneM->setCheckable(false);
        pbTopLaneR = new QPushButton(groupBox);
        pbTopLaneR->setObjectName(QString::fromUtf8("pbTopLaneR"));
        pbTopLaneR->setGeometry(QRect(190, 20, 81, 27));
        pbOutHole = new QPushButton(groupBox);
        pbOutHole->setObjectName(QString::fromUtf8("pbOutHole"));
        pbOutHole->setGeometry(QRect(10, 70, 98, 27));
        pbOutHole->setCheckable(true);
        pbTilt = new QPushButton(groupBox);
        pbTilt->setObjectName(QString::fromUtf8("pbTilt"));
        pbTilt->setGeometry(QRect(110, 70, 98, 27));
        textBrowser = new QTextBrowser(HelloForm);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 270, 651, 192));

        retranslateUi(HelloForm);

        QMetaObject::connectSlotsByName(HelloForm);
    } // setupUi

    void retranslateUi(QDialog *HelloForm)
    {
        HelloForm->setWindowTitle(QApplication::translate("HelloForm", "Hello Qt World", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("HelloForm", "Enter your name below", 0, QApplication::UnicodeUTF8));
        helloEdit->setText(QString());
        groupBox->setTitle(QApplication::translate("HelloForm", "Switches", 0, QApplication::UnicodeUTF8));
        pbTopLaneL->setText(QApplication::translate("HelloForm", "TopLane L", 0, QApplication::UnicodeUTF8));
        pbTopLaneM->setText(QApplication::translate("HelloForm", "TopLane M", 0, QApplication::UnicodeUTF8));
        pbTopLaneR->setText(QApplication::translate("HelloForm", "TopLane R", 0, QApplication::UnicodeUTF8));
        pbOutHole->setText(QApplication::translate("HelloForm", "Outhole", 0, QApplication::UnicodeUTF8));
        pbTilt->setText(QApplication::translate("HelloForm", "Tilt", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class HelloForm: public Ui_HelloForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELLOFORM_H
