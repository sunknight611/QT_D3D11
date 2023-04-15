/********************************************************************************
** Form generated from reading UI file 'QT_D3D11.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_D3D11_H
#define UI_QT_D3D11_H

#include <DxWindow.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QT_D3D11Class
{
public:
    QAction *actionOpenFile;
    QAction *actionNew;
    QAction *actionTex;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QCheckBox *cBtnSpec;
    QRadioButton *radioWhiteLight;
    QRadioButton *radioBlueLight;
    QRadioButton *radioRedLight;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *rBtnNormal;
    QRadioButton *rBtnWater;
    QRadioButton *rBtnFire;
    QRadioButton *rBtnShadow;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_3;
    DxWindow *W_DxWindow;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_4;
    QPlainTextEdit *FileText;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QSlider *lightSlider;
    QLabel *label;
    QSlider *camSlider;
    QSpacerItem *horizontalSpacer;
    QPushButton *BtnModify;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;

    void setupUi(QMainWindow *QT_D3D11Class)
    {
        if (QT_D3D11Class->objectName().isEmpty())
            QT_D3D11Class->setObjectName(QString::fromUtf8("QT_D3D11Class"));
        QT_D3D11Class->resize(924, 720);
        actionOpenFile = new QAction(QT_D3D11Class);
        actionOpenFile->setObjectName(QString::fromUtf8("actionOpenFile"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/Resources/open3.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenFile->setIcon(icon);
        actionNew = new QAction(QT_D3D11Class);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/Resources/new2.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon1);
        actionTex = new QAction(QT_D3D11Class);
        actionTex->setObjectName(QString::fromUtf8("actionTex"));
        actionTex->setIcon(icon);
        centralWidget = new QWidget(QT_D3D11Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cBtnSpec = new QCheckBox(groupBox);
        cBtnSpec->setObjectName(QString::fromUtf8("cBtnSpec"));

        horizontalLayout->addWidget(cBtnSpec);

        radioWhiteLight = new QRadioButton(groupBox);
        radioWhiteLight->setObjectName(QString::fromUtf8("radioWhiteLight"));

        horizontalLayout->addWidget(radioWhiteLight);

        radioBlueLight = new QRadioButton(groupBox);
        radioBlueLight->setObjectName(QString::fromUtf8("radioBlueLight"));

        horizontalLayout->addWidget(radioBlueLight);

        radioRedLight = new QRadioButton(groupBox);
        radioRedLight->setObjectName(QString::fromUtf8("radioRedLight"));

        horizontalLayout->addWidget(radioRedLight);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        rBtnNormal = new QRadioButton(groupBox_2);
        rBtnNormal->setObjectName(QString::fromUtf8("rBtnNormal"));

        horizontalLayout_2->addWidget(rBtnNormal);

        rBtnWater = new QRadioButton(groupBox_2);
        rBtnWater->setObjectName(QString::fromUtf8("rBtnWater"));

        horizontalLayout_2->addWidget(rBtnWater);

        rBtnFire = new QRadioButton(groupBox_2);
        rBtnFire->setObjectName(QString::fromUtf8("rBtnFire"));

        horizontalLayout_2->addWidget(rBtnFire);

        rBtnShadow = new QRadioButton(groupBox_2);
        rBtnShadow->setObjectName(QString::fromUtf8("rBtnShadow"));

        horizontalLayout_2->addWidget(rBtnShadow);


        verticalLayout->addWidget(groupBox_2);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_3 = new QHBoxLayout(tab);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        W_DxWindow = new DxWindow(tab);
        W_DxWindow->setObjectName(QString::fromUtf8("W_DxWindow"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(W_DxWindow->sizePolicy().hasHeightForWidth());
        W_DxWindow->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(W_DxWindow);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout_4 = new QHBoxLayout(tab_2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        FileText = new QPlainTextEdit(tab_2);
        FileText->setObjectName(QString::fromUtf8("FileText"));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush1(QColor(5, 239, 13, 128));
        brush1.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush1);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush1);
#endif
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        QBrush brush3(QColor(0, 0, 0, 128));
        brush3.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush3);
#endif
        FileText->setPalette(palette);

        horizontalLayout_4->addWidget(FileText);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_3);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_5->addWidget(label_2);

        lightSlider = new QSlider(groupBox_3);
        lightSlider->setObjectName(QString::fromUtf8("lightSlider"));
        lightSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(lightSlider);

        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_5->addWidget(label);

        camSlider = new QSlider(groupBox_3);
        camSlider->setObjectName(QString::fromUtf8("camSlider"));
        camSlider->setValue(0);
        camSlider->setSliderPosition(0);
        camSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(camSlider);

        horizontalSpacer = new QSpacerItem(207, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        BtnModify = new QPushButton(groupBox_3);
        BtnModify->setObjectName(QString::fromUtf8("BtnModify"));

        horizontalLayout_5->addWidget(BtnModify);


        verticalLayout->addWidget(groupBox_3);

        QT_D3D11Class->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(QT_D3D11Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        QT_D3D11Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QT_D3D11Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QT_D3D11Class->setStatusBar(statusBar);
        menuBar = new QMenuBar(QT_D3D11Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 924, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        QT_D3D11Class->setMenuBar(menuBar);

        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionOpenFile);
        mainToolBar->addAction(actionTex);
        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(actionOpenFile);
        menu->addAction(actionNew);
        menu->addAction(actionTex);

        retranslateUi(QT_D3D11Class);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(QT_D3D11Class);
    } // setupUi

    void retranslateUi(QMainWindow *QT_D3D11Class)
    {
        QT_D3D11Class->setWindowTitle(QApplication::translate("QT_D3D11Class", "QT_D3D11", nullptr));
        actionOpenFile->setText(QApplication::translate("QT_D3D11Class", "\346\211\223\345\274\200", nullptr));
#ifndef QT_NO_TOOLTIP
        actionOpenFile->setToolTip(QApplication::translate("QT_D3D11Class", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#endif // QT_NO_TOOLTIP
        actionNew->setText(QApplication::translate("QT_D3D11Class", "\346\226\260\345\273\272", nullptr));
#ifndef QT_NO_TOOLTIP
        actionNew->setToolTip(QApplication::translate("QT_D3D11Class", "\346\226\260\345\273\272\346\250\241\345\236\213", nullptr));
#endif // QT_NO_TOOLTIP
        actionTex->setText(QApplication::translate("QT_D3D11Class", "\351\200\211\346\213\251\350\264\264\345\233\276", nullptr));
#ifndef QT_NO_TOOLTIP
        actionTex->setToolTip(QApplication::translate("QT_D3D11Class", "\350\264\264\345\233\276", nullptr));
#endif // QT_NO_TOOLTIP
        groupBox->setTitle(QApplication::translate("QT_D3D11Class", "\345\205\211\347\205\247", nullptr));
        cBtnSpec->setText(QApplication::translate("QT_D3D11Class", "\351\253\230\345\205\211", nullptr));
        radioWhiteLight->setText(QApplication::translate("QT_D3D11Class", "\347\231\275\345\205\211", nullptr));
        radioBlueLight->setText(QApplication::translate("QT_D3D11Class", "\350\223\235\345\205\211", nullptr));
        radioRedLight->setText(QApplication::translate("QT_D3D11Class", "\347\272\242\345\205\211", nullptr));
        groupBox_2->setTitle(QString());
        rBtnNormal->setText(QApplication::translate("QT_D3D11Class", "\346\231\256\351\200\232", nullptr));
        rBtnWater->setText(QApplication::translate("QT_D3D11Class", "\346\260\264\351\235\242", nullptr));
        rBtnFire->setText(QApplication::translate("QT_D3D11Class", "\347\201\253\347\204\260\346\225\210\346\236\234", nullptr));
        rBtnShadow->setText(QApplication::translate("QT_D3D11Class", "\351\230\264\345\275\261\346\225\210\346\236\234", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("QT_D3D11Class", "\346\250\241\345\236\213\346\230\276\347\244\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("QT_D3D11Class", "\346\250\241\345\236\213\346\226\207\344\273\266", nullptr));
        groupBox_3->setTitle(QString());
        label_2->setText(QApplication::translate("QT_D3D11Class", "\345\205\211\347\205\247\346\226\271\345\220\221", nullptr));
        label->setText(QApplication::translate("QT_D3D11Class", "\347\233\270\346\234\272\346\226\271\345\220\221", nullptr));
        BtnModify->setText(QApplication::translate("QT_D3D11Class", "\344\277\256\346\224\271\346\250\241\345\236\213", nullptr));
        menu->setTitle(QApplication::translate("QT_D3D11Class", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QApplication::translate("QT_D3D11Class", "\347\274\226\350\276\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QT_D3D11Class: public Ui_QT_D3D11Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_D3D11_H
