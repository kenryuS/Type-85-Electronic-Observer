#ifndef MAINWINDOW_HXX_
#define MAINWINDOW_HXX_

#include <QMainWindow>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
	public:
	        MainWindow(QWidget* parent = 0);
		~MainWindow();
	
	private:
	        Ui::MainWindow m_ui;
};

#endif // MAINWINDOW_HXX_
