#ifndef BROWSER_WIDGET_HXX_
#define BROWSER_WIDGET_HXX_

#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineSettings>
#include <QWebEngineProfile>
#include <QTabBar>
#include <QLineEdit>
#include <QVBoxLayout>
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
        void setUrlToBar(const QUrl &url);
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

        std::function<void(const QString&)> titleChangedCallbackGenerator(int tabIndex);

        QVBoxLayout *layout;
        QTabBar *tab_bar;
        QLineEdit *url_bar;
        QWebEngineView *web_view;
        QWebEngineSettings *global_settings;
        QList<QWebEnginePage*> pages;
        int mainSessionIndex;
};

#endif // BROWSER_WIDGET_HXX_
