#include "osgviewer.h"
#include "osgviewerrenderer.h"
#include <QQuickWindow>

OSGViewer::OSGViewer(QQuickItem *parent)
    : QQuickFramebufferObject(parent)
{
}

QQuickFramebufferObject::Renderer *OSGViewer::createRenderer() const
{
    return new OSGViewerRenderer();
}