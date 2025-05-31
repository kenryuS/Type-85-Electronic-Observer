#ifndef BROWSER_WIDGET_HXX_
#define BROWSER_WIDGET_HXX_

#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineSettings>
#include <QWebEngineProfile>
#include <QWebEngineNewWindowRequest>
#include <QWidget>
#include <QTabBar>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QList>
#include <QUrl>
#include <QString>
#include <functional>

#include "BrowserWidget.moc"

class Browser : public QWidget
{
    Q_OBJECT

    public:
        Browser(QWidget *parent = nullptr);
        ~Browser();

    public slots:
        void newSession();
        void closeSession();
        void newTab();
        void closeTab();
        void openLink();
        void openLinkInNewTab(const QWebEngineNewWindowRequest &req);
        void setUrlToBar(const QUrl &url);
        void moveTab(int from, int to);
        void toggleMute();

    private:
        enum TabType {
            MAIN_SESSION,
            MAIN_SESSION_CLOSED,
            NORMAL
        };

        void setupTabBar();
        void setupUrlBar();
        void setupWebView();

        std::function<void(const QString&)> titleChangedCallbackGenerator(int tabIndex);

        QVBoxLayout *mainLayout;
        QTabBar *tab_bar;

        QWidget *url_bar_parent;
        QHBoxLayout *url_bar_layout;
        QLineEdit *url_bar;
        QPushButton *mute_button;

        QWebEngineView *web_view;
        QWebEngineSettings *global_settings;
        QList<QWebEnginePage*> pages;
        int mainSessionIndex;
};

#endif // BROWSER_WIDGET_HXX_
