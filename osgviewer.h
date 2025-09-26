#ifndef OSGVIEWER_H
#define OSGVIEWER_H

#include <QtQuick/QQuickFramebufferObject>

class OSGViewer : public QQuickFramebufferObject
{
    Q_OBJECT

public:
    explicit OSGViewer(QQuickItem *parent = nullptr);
    QQuickFramebufferObject::Renderer *createRenderer() const override;
};

#endif // OSGVIEWER_H