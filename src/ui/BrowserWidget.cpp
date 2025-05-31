#include <BrowserWidget.hpp>

#include <QVariant>
#include <QSizePolicy>
#include <QObject>

Browser::Browser(QWidget *parent):
    QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);

    setupTabBar();
    setupUrlBar();
    setupWebView();
}

Browser::~Browser() {
    for (auto &i : pages) {
        delete i;
    }
    pages.clear();
}

void Browser::setupTabBar() {
    tab_bar = new QTabBar(this);

    tab_bar->setMovable(true);
    tab_bar->setShape(QTabBar::RoundedNorth);
    tab_bar->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);
    //tab_bar->setTabButton();

    connect(tab_bar, &QTabBar::tabMoved, this, &Browser::moveTab);

    mainLayout->addWidget(tab_bar);
}

void Browser::setupUrlBar() {
    url_bar_parent = new QWidget(this);
    url_bar_layout = new QHBoxLayout(url_bar_parent);

    url_bar = new QLineEdit(url_bar_parent);
    mute_button = new QPushButton(QString("mute"), url_bar_parent);

    connect(url_bar, &QLineEdit::returnPressed, this, &Browser::openLink);
    connect(mute_button, &QPushButton::pressed, this, &Browser::toggleMute);

    url_bar_layout->addWidget(mute_button);
    url_bar_layout->addWidget(url_bar);

    url_bar_parent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    mainLayout->addWidget(url_bar_parent);
}

void Browser::setupWebView() {
    web_view = new QWebEngineView(this);
    QWebEngineProfile *default_profile = QWebEngineProfile::defaultProfile();
    global_settings = default_profile->settings();

    {
        using S = QWebEngineSettings::WebAttribute;
        #define SETATTR(A, B) global_settings->setAttribute((A), (B))
        SETATTR(S::AutoLoadImages, true);
        SETATTR(S::JavascriptEnabled, true);
        SETATTR(S::JavascriptCanOpenWindows, false);
        SETATTR(S::JavascriptCanAccessClipboard, false);
        SETATTR(S::LinksIncludedInFocusChain, true);
        SETATTR(S::LocalStorageEnabled, true);
        SETATTR(S::LocalContentCanAccessRemoteUrls, false);
        SETATTR(S::HyperlinkAuditingEnabled, false);
        SETATTR(S::ScrollAnimatorEnabled, false);
        SETATTR(S::ErrorPageEnabled, true);
        SETATTR(S::PluginsEnabled, false);
        SETATTR(S::FullScreenSupportEnabled, false);
        SETATTR(S::ScreenCaptureEnabled, true);
        SETATTR(S::WebGLEnabled, true);
        SETATTR(S::Accelerated2dCanvasEnabled, true);
        SETATTR(S::AutoLoadIconsForPage, false);
        SETATTR(S::TouchIconsEnabled, false);
        SETATTR(S::FocusOnNavigationEnabled, false);
        SETATTR(S::PrintElementBackgrounds, false);
        SETATTR(S::AllowRunningInsecureContent, true);
        SETATTR(S::AllowGeolocationOnInsecureOrigins, false);
        SETATTR(S::AllowWindowActivationFromJavaScript, false);
        SETATTR(S::ShowScrollBars, false);
        SETATTR(S::PlaybackRequiresUserGesture, false);
        SETATTR(S::JavascriptCanPaste, false);
        SETATTR(S::WebRTCPublicInterfacesOnly, false);
        SETATTR(S::DnsPrefetchEnabled, true);
        SETATTR(S::PdfViewerEnabled, false);
        SETATTR(S::NavigateOnDropEnabled, false);
        SETATTR(S::ReadingFromCanvasEnabled, true);
        SETATTR(S::ForceDarkMode, false);
        SETATTR(S::PrintHeaderAndFooter, false);
        SETATTR(S::PreferCSSMarginsForPrinting, false);
        SETATTR(S::TouchEventsApiEnabled, false);
        default_profile->setSpellCheckEnabled(false);
        default_profile->setPushServiceEnabled(false);
        #undef SETATTR
    }

    QWebEnginePage *emptyPage = new QWebEnginePage();
    QVariant tabData(Browser::MAIN_SESSION_CLOSED);
    emptyPage->setUrl(QUrl("about:blank"));
    pages.append(emptyPage);
    web_view->setPage(pages[0]);
    tab_bar->addTab(tr("Please start a new session."));
    tab_bar->setTabButton(0, QTabBar::LeftSide, nullptr);
    tab_bar->setTabData(0, tabData);
    mainSessionIndex = 0;
    connect(web_view, &QWebEngineView::urlChanged, this, &Browser::setUrlToBar);
    connect(tab_bar, &QTabBar::currentChanged, web_view, [=](int index) {
        web_view->setPage(pages[index]);
    });

    mainLayout->addWidget(web_view);
}

void Browser::newSession() {
    if (tab_bar->tabData(mainSessionIndex) == QVariant(Browser::MAIN_SESSION)) return;

    QWebEnginePage *kc = pages[mainSessionIndex];
    QVariant tabData(Browser::MAIN_SESSION);

    kc->setUrl(QUrl("https://games.dmm.com/detail/kancolle"));
    tab_bar->setTabData(mainSessionIndex, tabData);
    tab_bar->setTabText(mainSessionIndex, tr("Kancolle"));
}

void Browser::closeSession() {
    if (tab_bar->tabData(mainSessionIndex) == QVariant(Browser::MAIN_SESSION_CLOSED)) return;

    QWebEnginePage *kc = pages[mainSessionIndex];
    kc->setUrl(QUrl("about:blank"));
    tab_bar->setTabText(mainSessionIndex, tr("Please start a new session."));
    tab_bar->setTabData(mainSessionIndex, QVariant(Browser::MAIN_SESSION_CLOSED));
}

void Browser::newTab() {
    int newTabIndex = tab_bar->addTab(tr("New Tab"));
    tab_bar->setTabButton(newTabIndex, QTabBar::RightSide, nullptr);
    tab_bar->setTabData(newTabIndex, QVariant(Browser::NORMAL));

    QWebEnginePage *emptyPage = new QWebEnginePage();
    std::function<void(const QString&)> callback = titleChangedCallbackGenerator(newTabIndex);
    emptyPage->setUrl(QUrl("about:blank"));
    pages.append(emptyPage);
    web_view->setPage(pages[newTabIndex]);
    url_bar->setText(web_view->url().toString());
    connect(pages[newTabIndex], &QWebEnginePage::titleChanged, tab_bar, callback);
    connect(pages[newTabIndex], &QWebEnginePage::newWindowRequested, this, &Browser::openLinkInNewTab);

    tab_bar->setCurrentIndex(newTabIndex);
}

void Browser::closeTab() {
    int currentTab = tab_bar->currentIndex();
    QVariant tabData = tab_bar->tabData(currentTab);
    if (tabData == QVariant(Browser::MAIN_SESSION) || tabData == QVariant(Browser::MAIN_SESSION_CLOSED)) {
        return;
    }

    tab_bar->removeTab(currentTab);
    delete pages[currentTab];
    pages.remove(currentTab);
}

void Browser::openLink() {
    int currentTab = tab_bar->currentIndex();
    QVariant tabData = tab_bar->tabData(currentTab);
    if (tabData == QVariant(Browser::MAIN_SESSION) || tabData == QVariant(Browser::MAIN_SESSION_CLOSED)) {
        url_bar->setText(pages[currentTab]->url().toString());
        return;
    }
    QUrl dest(url_bar->text());

    pages[currentTab]->setUrl(dest);

    url_bar->clearFocus();
}

void Browser::openLinkInNewTab(const QWebEngineNewWindowRequest &req) {
    int newTabIndex = tab_bar->addTab(tr("New Tab"));
    tab_bar->setTabButton(newTabIndex, QTabBar::RightSide, nullptr);
    tab_bar->setTabData(newTabIndex, QVariant(Browser::NORMAL));

    QWebEnginePage *newPage = new QWebEnginePage();
    std::function<void(const QString&)> callback = titleChangedCallbackGenerator(newTabIndex);
    newPage->setUrl(req.requestedUrl());
    pages.append(newPage);
    web_view->setPage(pages[newTabIndex]);
    url_bar->setText(web_view->url().toString());
    connect(pages[newTabIndex], &QWebEnginePage::titleChanged, tab_bar, callback);
    connect(pages[newTabIndex], &QWebEnginePage::newWindowRequested, this, &Browser::openLinkInNewTab);

    tab_bar->setCurrentIndex(newTabIndex);
}

void Browser::setUrlToBar(const QUrl &url) {
    int currentTab = tab_bar->currentIndex();
    url_bar->setText(pages[currentTab]->url().toString());
}

void Browser::moveTab(int from, int to) {
    if (from == mainSessionIndex) {
        mainSessionIndex = to;
    }

    if (to == mainSessionIndex) {
        mainSessionIndex = from;
    }

    if (from != mainSessionIndex || to != mainSessionIndex) {
        disconnect(pages[from], &QWebEnginePage::titleChanged, 0, 0);
        disconnect(pages[to], &QWebEnginePage::titleChanged, 0, 0);
    }
    pages.swapItemsAt(from, to);

    if (from != mainSessionIndex || to != mainSessionIndex) {
        connect(pages[from], &QWebEnginePage::titleChanged, tab_bar, titleChangedCallbackGenerator(from));
        connect(pages[to], &QWebEnginePage::titleChanged, tab_bar, titleChangedCallbackGenerator(to));
    }

    web_view->setPage(pages[to]);
}

void Browser::toggleMute() {
    int currentTab = tab_bar->currentIndex();

    QWebEnginePage *currentPage = pages[currentTab];

    currentPage->setAudioMuted(!currentPage->isAudioMuted());
}

std::function<void(const QString&)> Browser::titleChangedCallbackGenerator(int tabIndex) {
    return [this, tabIndex](const QString &title) {
        tab_bar->setTabText(tabIndex, title);
    };
}
