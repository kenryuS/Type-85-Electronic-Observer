#ifndef MAINWINDOW_HXX_
#define MAINWINDOW_HXX_

#include <QMainWindow>
#include <QObject>

#include "BrowserWidget.hpp"

#include "ui/ui_MainWindow.h"
#include "MainWindow.moc"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        void createActions();

        Ui::MainWindow *m_ui;
        Browser *browser;
        bool hasMainBrowser = false;
};

#endif // MAINWINDOW_HXX_
