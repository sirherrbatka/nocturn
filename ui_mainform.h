/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <phonon/seekslider.h>
#include <phonon/volumeslider.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTabWidget *PlayListsTabs;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *clearButton;
    QHBoxLayout *horizontalLayout_2;
    Phonon::VolumeSlider *volumeSlider;
    Phonon::SeekSlider *seekSlider;
    QHBoxLayout *horizontalLayout;
    QToolButton *prevButton;
    QToolButton *toggleButton;
    QToolButton *nextButton;
    QLabel *statusLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(342, 504);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        PlayListsTabs = new QTabWidget(centralwidget);
        PlayListsTabs->setObjectName(QString::fromUtf8("PlayListsTabs"));
        PlayListsTabs->setElideMode(Qt::ElideMiddle);
        PlayListsTabs->setDocumentMode(false);
        PlayListsTabs->setTabsClosable(true);

        verticalLayout->addWidget(PlayListsTabs);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        clearButton = new QPushButton(centralwidget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));

        horizontalLayout_6->addWidget(clearButton);


        verticalLayout->addLayout(horizontalLayout_6);


        gridLayout->addLayout(verticalLayout, 12, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        volumeSlider = new Phonon::VolumeSlider(centralwidget);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(volumeSlider->sizePolicy().hasHeightForWidth());
        volumeSlider->setSizePolicy(sizePolicy);
        volumeSlider->setMinimumSize(QSize(90, 15));
        volumeSlider->setMaximumSize(QSize(90, 15));
        volumeSlider->setTracking(true);
        volumeSlider->setMuteVisible(false);

        horizontalLayout_2->addWidget(volumeSlider);

        seekSlider = new Phonon::SeekSlider(centralwidget);
        seekSlider->setObjectName(QString::fromUtf8("seekSlider"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(seekSlider->sizePolicy().hasHeightForWidth());
        seekSlider->setSizePolicy(sizePolicy1);
        seekSlider->setMinimumSize(QSize(50, 15));
        seekSlider->setMaximumSize(QSize(16777215, 15));
        seekSlider->setIconVisible(false);

        horizontalLayout_2->addWidget(seekSlider);


        gridLayout->addLayout(horizontalLayout_2, 6, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        prevButton = new QToolButton(centralwidget);
        prevButton->setObjectName(QString::fromUtf8("prevButton"));
        prevButton->setMinimumSize(QSize(22, 22));
        prevButton->setMaximumSize(QSize(25, 25));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("media-skip-backward");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8(""), QSize(), QIcon::Normal, QIcon::Off);
        }
        prevButton->setIcon(icon);
        prevButton->setIconSize(QSize(22, 22));
        prevButton->setAutoRaise(true);

        horizontalLayout->addWidget(prevButton);

        toggleButton = new QToolButton(centralwidget);
        toggleButton->setObjectName(QString::fromUtf8("toggleButton"));
        toggleButton->setMinimumSize(QSize(22, 22));
        toggleButton->setMaximumSize(QSize(25, 25));
        QIcon icon1;
        iconThemeName = QString::fromUtf8("media-playback-pause");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8(""), QSize(), QIcon::Normal, QIcon::Off);
        }
        toggleButton->setIcon(icon1);
        toggleButton->setIconSize(QSize(22, 22));
        toggleButton->setAutoRaise(true);

        horizontalLayout->addWidget(toggleButton);

        nextButton = new QToolButton(centralwidget);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        sizePolicy.setHeightForWidth(nextButton->sizePolicy().hasHeightForWidth());
        nextButton->setSizePolicy(sizePolicy);
        nextButton->setMinimumSize(QSize(22, 22));
        nextButton->setMaximumSize(QSize(25, 25));
        QIcon icon2;
        iconThemeName = QString::fromUtf8("media-skip-forward");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8(""), QSize(), QIcon::Normal, QIcon::Off);
        }
        nextButton->setIcon(icon2);
        nextButton->setIconSize(QSize(22, 22));
        nextButton->setAutoRaise(true);

        horizontalLayout->addWidget(nextButton);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        sizePolicy1.setHeightForWidth(statusLabel->sizePolicy().hasHeightForWidth());
        statusLabel->setSizePolicy(sizePolicy1);
        statusLabel->setMinimumSize(QSize(50, 22));
        statusLabel->setMaximumSize(QSize(16777215, 22));
        statusLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(statusLabel);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 342, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Nocturn", 0, QApplication::UnicodeUTF8));
        clearButton->setText(QApplication::translate("MainWindow", "Clear Playlist", 0, QApplication::UnicodeUTF8));
        prevButton->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        toggleButton->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        nextButton->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        statusLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
