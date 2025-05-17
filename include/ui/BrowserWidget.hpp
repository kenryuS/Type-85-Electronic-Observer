#ifndef BROWSER_WIDGET_HXX_
#define BROWSER_WIDGET_HXX_

#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineSettings>
#include <QWebEngineProfile>
#include <QTabBar>
#include <QVBoxLayout>
#include <QList>

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
        void openInNewTab();
        void moveTab(int from, int to);
        void mute();

    private:
        enum TabType {
            MAIN_SESSION,
            MAIN_SESSION_CLOSED,
            NORMAL
        };

        void setupBar();
        void setupWebView();

        QVBoxLayout *layout;
        QTabBar *tab_bar;
        QWebEngineView *web_view;
        QWebEngineSettings *global_settings;
        QList<QWebEnginePage*> pages;
};

#endif // BROWSER_WIDGET_HXX_
