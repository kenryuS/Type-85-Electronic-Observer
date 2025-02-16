#ifndef CEFVIEWWIDGET_HXX_
#define CEFVIEWWIDGET_HXX_

#include <QCefView.h>

class CefViewWidget : public QCefView
{
        public:
	        CefViewWidget(const QString url, const QCefSetting* setting, QWidget* parent = 0);
		~CefViewWidget();
	
	private:
};

#endif // CEFVIEWWIDGET_HXX_
