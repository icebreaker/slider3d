/********************************************************************************
** Form generated from reading ui file 'startupdialog.ui'
**
** Created: Sat Aug 8 13:30:54 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_STARTUPDIALOG_H
#define UI_STARTUPDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_StartupDialog
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QComboBox *comboBox;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_7;
    QLineEdit *lineEdit;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_2;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_4;

    void setupUi(QDialog *StartupDialog)
    {
        if (StartupDialog->objectName().isEmpty())
            StartupDialog->setObjectName(QString::fromUtf8("StartupDialog"));
        StartupDialog->resize(426, 391);
        buttonBox = new QDialogButtonBox(StartupDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(340, 10, 81, 101));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(StartupDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 151, 63));
        groupBox->setFlat(false);
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout_3->addWidget(comboBox);

        groupBox_2 = new QGroupBox(StartupDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 70, 311, 121));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout->addWidget(checkBox);

        checkBox_7 = new QCheckBox(groupBox_2);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));

        verticalLayout->addWidget(checkBox_7);

        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setEnabled(false);

        verticalLayout->addWidget(lineEdit);

        groupBox_3 = new QGroupBox(StartupDialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 190, 242, 181));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox_2 = new QComboBox(groupBox_3);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        horizontalLayout->addWidget(comboBox_2);


        verticalLayout_2->addLayout(horizontalLayout);

        checkBox_2 = new QCheckBox(groupBox_3);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        verticalLayout_2->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(groupBox_3);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        verticalLayout_2->addWidget(checkBox_3);

        checkBox_5 = new QCheckBox(groupBox_3);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));

        verticalLayout_2->addWidget(checkBox_5);

        checkBox_6 = new QCheckBox(groupBox_3);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));

        verticalLayout_2->addWidget(checkBox_6);

        checkBox_4 = new QCheckBox(StartupDialog);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(250, 360, 171, 23));
        checkBox_4->setChecked(true);

        retranslateUi(StartupDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), StartupDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), StartupDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(StartupDialog);
    } // setupUi

    void retranslateUi(QDialog *StartupDialog)
    {
        StartupDialog->setWindowTitle(QApplication::translate("StartupDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setStyleSheet(QString());
        groupBox->setTitle(QApplication::translate("StartupDialog", "Monitor", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("StartupDialog", "(Default)", 0, QApplication::UnicodeUTF8)
        );
        groupBox_2->setTitle(QApplication::translate("StartupDialog", "Photo Management", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("StartupDialog", "Scan sub-directories (may be slow)", 0, QApplication::UnicodeUTF8));
        checkBox_7->setText(QApplication::translate("StartupDialog", "Exlude which contains (RegExp):", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("StartupDialog", "Rendering", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("StartupDialog", "Anti-Aliasing", 0, QApplication::UnicodeUTF8));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("StartupDialog", "(None)", 0, QApplication::UnicodeUTF8)
        );
        checkBox_2->setText(QApplication::translate("StartupDialog", "Reflective ground", 0, QApplication::UnicodeUTF8));
        checkBox_3->setText(QApplication::translate("StartupDialog", "Animations", 0, QApplication::UnicodeUTF8));
        checkBox_5->setText(QApplication::translate("StartupDialog", "Polaroid frames (a la Picasa)", 0, QApplication::UnicodeUTF8));
        checkBox_6->setText(QApplication::translate("StartupDialog", "Show file names", 0, QApplication::UnicodeUTF8));
        checkBox_4->setText(QApplication::translate("StartupDialog", "Don't show this again", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(StartupDialog);
    } // retranslateUi

};

namespace Ui {
    class StartupDialog: public Ui_StartupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTUPDIALOG_H
