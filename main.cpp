#include <QGuiApplication>
#include <QQuickView>
#include <QSurfaceFormat>
#include "osgviewer.h"

int main(int argc, char *argv[])
{
    // 设置OpenGL格式
    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    QGuiApplication app(argc, argv);

    // 注册自定义QML类型
    qmlRegisterType<OSGViewer>("OSGViewer", 1, 0, "OSGViewer");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///qml/main.qml"));
    view.show();

    return app.exec();
}