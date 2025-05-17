#include <BrowserWidget.hpp>

#include <QUrl>
#include <QString>
#include <QVariant>

Browser::Browser(QWidget *parent):
    QWidget(parent)
{
    layout = new QVBoxLayout(this);

    setupBar();
    setupWebView();
}

Browser::~Browser() {
    for (auto &i : pages) {
        delete i;
    }
    pages.clear();
}

void Browser::setupBar() {
    tab_bar = new QTabBar(this);

    tab_bar->setMovable(true);
    tab_bar->setShape(QTabBar::RoundedNorth);
    tab_bar->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);
    //tab_bar->setTabButton();

    layout->addWidget(tab_bar);
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
    SETATTR(S::ShowScrollBars, true);
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

    layout->addWidget(web_view);
}

void Browser::newSession() {
    if (tab_bar->tabData(0) == QVariant(Browser::MAIN_SESSION)) return;

    QWebEnginePage *kc = pages[0];
    QVariant tabData(Browser::MAIN_SESSION);

    kc->setUrl(QUrl("https://games.dmm.com/detail/kancolle"));
    tab_bar->setTabData(0, tabData);
    tab_bar->setTabText(0, tr("Kancolle"));
}

void Browser::closeSession() {
    if (tab_bar->tabData(0) == QVariant(Browser::MAIN_SESSION_CLOSED)) return;

    QWebEnginePage *kc = pages[0];
    kc->setUrl(QUrl("about:blank"));
    tab_bar->setTabText(0, tr("Please start a new session."));
    tab_bar->setTabData(0, QVariant(Browser::MAIN_SESSION_CLOSED));
}

void Browser::openInNewTab() {}

void Browser::moveTab(int from, int to) {}

void Browser::mute() {}
