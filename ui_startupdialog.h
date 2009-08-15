/********************************************************************************
** Form generated from reading ui file 'startupdialog.ui'
**
** Created: Sat Aug 15 19:10:28 2009
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
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QToolBox>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartupDialog
{
public:
    QDialogButtonBox *buttonBox;
    QCheckBox *dontshow;
    QToolBox *toolBox;
    QWidget *page;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QComboBox *monitor;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *res;
    QCheckBox *windowed;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QSpinBox *timeout;
    QLabel *label_7;
    QWidget *page_2;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_6;
    QComboBox *mssa;
    QCheckBox *floor;
    QCheckBox *labels;
    QWidget *page_3;
    QListWidget *paths;
    QPushButton *addfolder;
    QPushButton *removefolder;
    QCheckBox *subdirs;
    QToolButton *moveup;
    QToolButton *movedown;

    void setupUi(QDialog *StartupDialog)
    {
        if (StartupDialog->objectName().isEmpty())
            StartupDialog->setObjectName(QString::fromUtf8("StartupDialog"));
        StartupDialog->resize(614, 310);
        buttonBox = new QDialogButtonBox(StartupDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(520, 10, 81, 101));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        dontshow = new QCheckBox(StartupDialog);
        dontshow->setObjectName(QString::fromUtf8("dontshow"));
        dontshow->setGeometry(QRect(430, 280, 171, 23));
        dontshow->setChecked(false);
        toolBox = new QToolBox(StartupDialog);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        toolBox->setGeometry(QRect(10, 10, 501, 271));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 501, 195));
        groupBox = new QGroupBox(page);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 181, 63));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        monitor = new QComboBox(groupBox);
        monitor->setObjectName(QString::fromUtf8("monitor"));

        horizontalLayout->addWidget(monitor);

        groupBox_2 = new QGroupBox(page);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(190, 0, 251, 63));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        res = new QComboBox(groupBox_2);
        res->setObjectName(QString::fromUtf8("res"));
        res->setEnabled(false);

        horizontalLayout_2->addWidget(res);

        windowed = new QCheckBox(groupBox_2);
        windowed->setObjectName(QString::fromUtf8("windowed"));

        horizontalLayout_2->addWidget(windowed);

        groupBox_5 = new QGroupBox(page);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(0, 70, 181, 63));
        horizontalLayout_7 = new QHBoxLayout(groupBox_5);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_6 = new QLabel(groupBox_5);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_7->addWidget(label_6);

        timeout = new QSpinBox(groupBox_5);
        timeout->setObjectName(QString::fromUtf8("timeout"));
        timeout->setMaximum(10000);
        timeout->setValue(3);

        horizontalLayout_7->addWidget(timeout);

        label_7 = new QLabel(groupBox_5);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_7->addWidget(label_7);

        toolBox->addItem(page, QString::fromUtf8("General"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 501, 195));
        groupBox_4 = new QGroupBox(page_2);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(0, 0, 221, 63));
        horizontalLayout_6 = new QHBoxLayout(groupBox_4);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        mssa = new QComboBox(groupBox_4);
        mssa->setObjectName(QString::fromUtf8("mssa"));

        horizontalLayout_6->addWidget(mssa);

        floor = new QCheckBox(page_2);
        floor->setObjectName(QString::fromUtf8("floor"));
        floor->setGeometry(QRect(0, 70, 171, 23));
        labels = new QCheckBox(page_2);
        labels->setObjectName(QString::fromUtf8("labels"));
        labels->setGeometry(QRect(180, 70, 201, 23));
        toolBox->addItem(page_2, QString::fromUtf8("Rendering"));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        page_3->setGeometry(QRect(0, 0, 501, 175));
        paths = new QListWidget(page_3);
        paths->setObjectName(QString::fromUtf8("paths"));
        paths->setGeometry(QRect(0, 0, 401, 141));
        addfolder = new QPushButton(page_3);
        addfolder->setObjectName(QString::fromUtf8("addfolder"));
        addfolder->setGeometry(QRect(410, 0, 90, 27));
        removefolder = new QPushButton(page_3);
        removefolder->setObjectName(QString::fromUtf8("removefolder"));
        removefolder->setGeometry(QRect(410, 30, 90, 27));
        subdirs = new QCheckBox(page_3);
        subdirs->setObjectName(QString::fromUtf8("subdirs"));
        subdirs->setGeometry(QRect(0, 150, 191, 23));
        moveup = new QToolButton(page_3);
        moveup->setObjectName(QString::fromUtf8("moveup"));
        moveup->setGeometry(QRect(410, 70, 24, 23));
        moveup->setArrowType(Qt::UpArrow);
        movedown = new QToolButton(page_3);
        movedown->setObjectName(QString::fromUtf8("movedown"));
        movedown->setGeometry(QRect(410, 100, 24, 23));
        movedown->setArrowType(Qt::DownArrow);
        toolBox->addItem(page_3, QString::fromUtf8("Photos"));

        retranslateUi(StartupDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), StartupDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), StartupDialog, SLOT(reject()));
        QObject::connect(windowed, SIGNAL(toggled(bool)), res, SLOT(setEnabled(bool)));

        toolBox->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(StartupDialog);
    } // setupUi

    void retranslateUi(QDialog *StartupDialog)
    {
        StartupDialog->setWindowTitle(QApplication::translate("StartupDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        dontshow->setText(QApplication::translate("StartupDialog", "Don't show this again", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("StartupDialog", "Monitor", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("StartupDialog", "Window", 0, QApplication::UnicodeUTF8));
        res->clear();
        res->insertItems(0, QStringList()
         << QApplication::translate("StartupDialog", "640x480", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("StartupDialog", "800x600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("StartupDialog", "1024x768", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("StartupDialog", "1024x1024", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("StartupDialog", "1280x720", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("StartupDialog", "1280x800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("StartupDialog", "1440x900", 0, QApplication::UnicodeUTF8)
        );
        windowed->setText(QApplication::translate("StartupDialog", "Windowed", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("StartupDialog", "Slide Show", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("StartupDialog", "Every", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("StartupDialog", "seconds", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("StartupDialog", "General", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("StartupDialog", "Multi-Sampling (Anti-Aliasing)", 0, QApplication::UnicodeUTF8));
        mssa->clear();
        mssa->insertItems(0, QStringList()
         << QApplication::translate("StartupDialog", "(none)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("StartupDialog", "2x", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("StartupDialog", "4x", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("StartupDialog", "8x", 0, QApplication::UnicodeUTF8)
        );
        floor->setText(QApplication::translate("StartupDialog", "Render reflective floor", 0, QApplication::UnicodeUTF8));
        labels->setText(QApplication::translate("StartupDialog", "Render labels (file names)", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("StartupDialog", "Rendering", 0, QApplication::UnicodeUTF8));
        addfolder->setText(QApplication::translate("StartupDialog", "Add Folder", 0, QApplication::UnicodeUTF8));
        removefolder->setText(QApplication::translate("StartupDialog", "Remove", 0, QApplication::UnicodeUTF8));
        subdirs->setText(QApplication::translate("StartupDialog", "Dive into sub-directories", 0, QApplication::UnicodeUTF8));
        moveup->setText(QApplication::translate("StartupDialog", "...", 0, QApplication::UnicodeUTF8));
        movedown->setText(QApplication::translate("StartupDialog", "...", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("StartupDialog", "Photos", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(StartupDialog);
    } // retranslateUi

};

namespace Ui {
    class StartupDialog: public Ui_StartupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTUPDIALOG_H
