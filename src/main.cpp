#include <cef_app.h>

#include "qtcefwindow.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>

#include "simple_app.h"

/**
 * 初始化QT以及CEF相关
 */
int init_qt_cef(int& argc, char** argv)
{
    const HINSTANCE h_instance = static_cast<HINSTANCE>(GetModuleHandle(nullptr));

    const CefMainArgs main_args(h_instance);
    const CefRefPtr<SimpleApp> app(new SimpleApp); //CefApp实现，用于处理进程相关的回调。

    const int exit_code = CefExecuteProcess(main_args, app.get(), nullptr);
    if (exit_code >= 0)
    {
        return exit_code;
    }

    // 设置配置
    CefSettings settings;
    settings.multi_threaded_message_loop = true; //多线程消息循环
    settings.log_severity = LOGSEVERITY_DISABLE; //日志
    settings.no_sandbox = true; //沙盒

    CefInitialize(main_args, settings, app, nullptr);

    return -1;
}


int main(int argc, char* argv[])
{
    // 将init_qt_cef提取到QApplication初始化之前
    // 对于CEF多进程架构模型
    // 因为【渲染进程】启动后，init_qt_cef中执行的CefExecuteProcess会阻塞住，
    // 如果在此之前启动了QT的事件循环，那么会导致QT出现异常
    // 所以，我们将init_qt_cef提前到QApplication初始化之前，
    // 保证无论是浏览器进程还是渲染进程启动，都会进入init_qt_cef，但渲染进程会在里面阻塞，
    // 不会进入后续的QT应用初始化
    const int result = init_qt_cef(argc, argv);
    if (result >= 0)
    {
        return result;
    }

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);  // 解决高DPI下，界面比例问题
    QApplication a(argc, argv);

    QtCefWindow w;
    w.show();
    a.exec();

    CefShutdown(); // 关闭CEF，释放资源

    return 0;
}
