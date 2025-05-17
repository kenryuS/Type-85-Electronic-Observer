#include "MainWindow.hpp"

#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    browser = new Browser(this);
    m_ui->setupUi(this);

    #if defined(DEBUG)
    this->setWindowTitle(tr("Type 85 Electronic Observer - Prototype"));
    #endif

    createActions();

    centralWidget()->layout()->addWidget(browser);
}

MainWindow::~MainWindow() {
    delete m_ui;
}

void MainWindow::createActions() {
    connect(m_ui->action_About_Qt, &QAction::triggered, this, [&](){
        QMessageBox::aboutQt(this, tr("About Qt"));
    });
    connect(m_ui->action_About, &QAction::triggered, this, [&](){
        QMessageBox::about(this, tr("Type 85 Electronic Observer"), tr("Cross platform Kancolle tool"));
    });
    connect(m_ui->actionOffical_Twitter, &QAction::triggered, this, [](){
        QDesktopServices::openUrl(QUrl("https://x.com/KanColle_STAFF"));
    });
    connect(m_ui->actionKancolle_Wiki, &QAction::triggered, this, [](){
        QDesktopServices::openUrl(QUrl("https://wikiwiki.jp/kancolle"));
    });
    connect(m_ui->action_New_Session, &QAction::triggered, browser, &Browser::newSession);
    connect(m_ui->action_Close_Session, &QAction::triggered, browser, &Browser::closeSession);
}
