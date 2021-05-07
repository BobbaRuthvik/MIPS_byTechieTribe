/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer_3;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QGridLayout *gridLayout_3;
    QTextEdit *textEdit;
    QWidget *tab_5;
    QGridLayout *gridLayout_4;
    QTextEdit *textEdit_3;
    QWidget *tab_4;
    QGridLayout *gridLayout_5;
    QTextEdit *textEdit_4;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_7;
    QLabel *label;
    QCheckBox *checkBox;
    QFrame *frame;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_16;
    QLineEdit *lineEdit_6;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_7;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QVBoxLayout *verticalLayout_12;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_34;
    QLineEdit *lineEdit_35;
    QLineEdit *lineEdit_36;
    QSpacerItem *horizontalSpacer_5;
    QTextBrowser *textBrowser;
    QTextEdit *textEdit_2;
    QLabel *label_3;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1081, 886);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 3, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_2, 4, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer, 1, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 3, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setFamily(QString::fromUtf8("Lucida Handwriting"));
        font.setPointSize(11);
        font.setBold(true);
        label_2->setFont(font);

        gridLayout_2->addWidget(label_2, 0, 0, 1, 2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer_3 = new QSpacerItem(20, 350, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 2, 2, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_4, 6, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 5, 2, 1, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Book Antiqua"));
        font1.setPointSize(12);
        font1.setBold(true);
        tabWidget->setFont(font1);
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_3 = new QGridLayout(tab_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        textEdit = new QTextEdit(tab_3);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setFont(font1);
        textEdit->setFrameShape(QFrame::Box);
        textEdit->setReadOnly(true);

        gridLayout_3->addWidget(textEdit, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        gridLayout_4 = new QGridLayout(tab_5);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        textEdit_3 = new QTextEdit(tab_5);
        textEdit_3->setObjectName(QString::fromUtf8("textEdit_3"));
        textEdit_3->setReadOnly(true);

        gridLayout_4->addWidget(textEdit_3, 0, 0, 1, 1);

        tabWidget->addTab(tab_5, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        gridLayout_5 = new QGridLayout(tab_4);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        textEdit_4 = new QTextEdit(tab_4);
        textEdit_4->setObjectName(QString::fromUtf8("textEdit_4"));
        textEdit_4->setReadOnly(true);

        gridLayout_5->addWidget(textEdit_4, 0, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());

        gridLayout->addWidget(tabWidget, 1, 3, 5, 1);

        horizontalSpacer = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 6, 0, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_7, 3, 1, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font1);

        gridLayout->addWidget(label, 1, 1, 1, 1);

        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setFont(font1);

        gridLayout->addWidget(checkBox, 0, 1, 1, 1);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        layoutWidget = new QWidget(frame);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 0, 151, 101));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(80);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Modern No. 20"));
        font2.setPointSize(12);
        pushButton->setFont(font2);

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(50);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setFont(font2);

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy2);
        pushButton_3->setFont(font2);

        verticalLayout->addWidget(pushButton_3);

        layoutWidget1 = new QWidget(frame);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 140, 222, 32));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_16 = new QLabel(layoutWidget1);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy3);
        QFont font3;
        font3.setFamily(QString::fromUtf8("Comic Sans MS"));
        font3.setPointSize(11);
        label_16->setFont(font3);

        horizontalLayout_5->addWidget(label_16);

        lineEdit_6 = new QLineEdit(layoutWidget1);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lineEdit_6->sizePolicy().hasHeightForWidth());
        lineEdit_6->setSizePolicy(sizePolicy4);
        QFont font4;
        font4.setFamily(QString::fromUtf8("Comic Sans MS"));
        lineEdit_6->setFont(font4);

        horizontalLayout_5->addWidget(lineEdit_6);

        layoutWidget2 = new QWidget(frame);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 214, 222, 327));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font4);

        verticalLayout_6->addWidget(label_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setSizeConstraint(QLayout::SetMaximumSize);
        label_7 = new QLabel(layoutWidget2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font3);

        verticalLayout_9->addWidget(label_7);

        label_8 = new QLabel(layoutWidget2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font3);

        verticalLayout_9->addWidget(label_8);

        label_9 = new QLabel(layoutWidget2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font3);

        verticalLayout_9->addWidget(label_9);

        label_10 = new QLabel(layoutWidget2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font3);

        verticalLayout_9->addWidget(label_10);


        horizontalLayout->addLayout(verticalLayout_9);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        lineEdit = new QLineEdit(layoutWidget2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        sizePolicy4.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy4);
        lineEdit->setFont(font4);

        verticalLayout_2->addWidget(lineEdit);

        lineEdit_9 = new QLineEdit(layoutWidget2);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));
        sizePolicy4.setHeightForWidth(lineEdit_9->sizePolicy().hasHeightForWidth());
        lineEdit_9->setSizePolicy(sizePolicy4);
        lineEdit_9->setFont(font4);

        verticalLayout_2->addWidget(lineEdit_9);

        lineEdit_8 = new QLineEdit(layoutWidget2);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        sizePolicy4.setHeightForWidth(lineEdit_8->sizePolicy().hasHeightForWidth());
        lineEdit_8->setSizePolicy(sizePolicy4);
        lineEdit_8->setFont(font4);

        verticalLayout_2->addWidget(lineEdit_8);

        lineEdit_7 = new QLineEdit(layoutWidget2);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        sizePolicy4.setHeightForWidth(lineEdit_7->sizePolicy().hasHeightForWidth());
        lineEdit_7->setSizePolicy(sizePolicy4);
        lineEdit_7->setFont(font4);

        verticalLayout_2->addWidget(lineEdit_7);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_6->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout_6);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        label_11 = new QLabel(layoutWidget2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font4);

        verticalLayout_10->addWidget(label_11);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_11->setSizeConstraint(QLayout::SetMaximumSize);
        label_12 = new QLabel(layoutWidget2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font3);

        verticalLayout_11->addWidget(label_12);

        label_13 = new QLabel(layoutWidget2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font3);

        verticalLayout_11->addWidget(label_13);

        label_14 = new QLabel(layoutWidget2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font3);

        verticalLayout_11->addWidget(label_14);

        label_15 = new QLabel(layoutWidget2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font3);

        verticalLayout_11->addWidget(label_15);


        horizontalLayout_6->addLayout(verticalLayout_11);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_12->setSizeConstraint(QLayout::SetMinimumSize);
        lineEdit_5 = new QLineEdit(layoutWidget2);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        sizePolicy4.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy4);
        lineEdit_5->setFont(font4);

        verticalLayout_12->addWidget(lineEdit_5);

        lineEdit_34 = new QLineEdit(layoutWidget2);
        lineEdit_34->setObjectName(QString::fromUtf8("lineEdit_34"));
        sizePolicy4.setHeightForWidth(lineEdit_34->sizePolicy().hasHeightForWidth());
        lineEdit_34->setSizePolicy(sizePolicy4);
        lineEdit_34->setFont(font4);

        verticalLayout_12->addWidget(lineEdit_34);

        lineEdit_35 = new QLineEdit(layoutWidget2);
        lineEdit_35->setObjectName(QString::fromUtf8("lineEdit_35"));
        sizePolicy4.setHeightForWidth(lineEdit_35->sizePolicy().hasHeightForWidth());
        lineEdit_35->setSizePolicy(sizePolicy4);
        lineEdit_35->setFont(font4);

        verticalLayout_12->addWidget(lineEdit_35);

        lineEdit_36 = new QLineEdit(layoutWidget2);
        lineEdit_36->setObjectName(QString::fromUtf8("lineEdit_36"));
        sizePolicy4.setHeightForWidth(lineEdit_36->sizePolicy().hasHeightForWidth());
        lineEdit_36->setSizePolicy(sizePolicy4);
        lineEdit_36->setFont(font4);

        verticalLayout_12->addWidget(lineEdit_36);


        horizontalLayout_6->addLayout(verticalLayout_12);


        verticalLayout_10->addLayout(horizontalLayout_6);


        verticalLayout_3->addLayout(verticalLayout_10);


        gridLayout->addWidget(frame, 0, 0, 6, 1);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 1, 4, 1, 1);

        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy5);
        QFont font5;
        font5.setFamily(QString::fromUtf8("Courier New"));
        font5.setPointSize(12);
        font5.setBold(false);
        textBrowser->setFont(font5);
        textBrowser->setFrameShape(QFrame::Box);
        textBrowser->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(textBrowser, 5, 1, 1, 1);

        textEdit_2 = new QTextEdit(centralwidget);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Maiandra GD"));
        font6.setPointSize(12);
        textEdit_2->setFont(font6);

        gridLayout->addWidget(textEdit_2, 2, 1, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        gridLayout->addWidget(label_3, 4, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 2, 1, 2, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1081, 26));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; color:#00aa00;\">Techie Tribe</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Registers", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("MainWindow", "Data Section", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Stalls", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" color:#0055ff;\">Text Section</span></p></body></html>", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "With Forwarding", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Load File", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Load Parameters", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Memory Latency", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600; color:#aa007f;\">Level1 cache</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Cache Size", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Block Size", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Associativity", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Access Latency", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600; color:#aa007f;\">Level2 cache</span></p></body></html>", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Cache Size", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Block Size", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Associativity", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Access Latency", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" color:#0000ff;\">Console</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
