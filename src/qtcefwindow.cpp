#include "qtcefwindow.h"

#include <cef_request_context.h>

#include "simple_handler.h"
#include "stdafx.h"

QtCefWindow::QtCefWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // 以下是将 SimpleHandler 与窗体进行关联的代码
    CefWindowInfo cef_wnd_info;
    QString str_url = "https://www.cnblogs.com/w4ngzhen";
    QRect rect = this->geometry();
    CefRect win_rect(
            rect.left(),
            rect.top(),
            rect.left() + rect.width() * devicePixelRatio(),
            rect.top() + rect.height() * devicePixelRatio());

    cef_wnd_info.SetAsChild((HWND)this->winId(), win_rect); //将cef界面嵌入qt界面中
    CefBrowserSettings cef_browser_settings;
    simple_handler_ = CefRefPtr<SimpleHandler>(new SimpleHandler());
    CefBrowserHost::CreateBrowser(cef_wnd_info,
        simple_handler_,
        str_url.toStdString(),
        cef_browser_settings,
        nullptr,
        CefRequestContext::GetGlobalContext());
}