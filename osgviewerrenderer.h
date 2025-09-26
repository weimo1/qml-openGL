#ifndef OSGVIEWERRENDERER_H
#define OSGVIEWERRENDERER_H

#include <QQuickFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class OSGViewerRenderer : public QQuickFramebufferObject::Renderer, protected QOpenGLFunctions
{
public:
    OSGViewerRenderer();
    ~OSGViewerRenderer();

    void render() override;
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;

private:
    bool initialized;
    QOpenGLShaderProgram *shaderProgram;
    QOpenGLBuffer *vertexBuffer;
    QOpenGLVertexArrayObject *vao;
    void initializeTriangle();
};

#endif // OSGVIEWERRENDERER_H