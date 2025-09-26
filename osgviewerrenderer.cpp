#include "osgviewerrenderer.h"
#include <QOpenGLFramebufferObject>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>

OSGViewerRenderer::OSGViewerRenderer()
    : initialized(false), shaderProgram(nullptr), vertexBuffer(nullptr), vao(nullptr)
{
}

OSGViewerRenderer::~OSGViewerRenderer()
{
    // 清理OpenGL资源
    if (shaderProgram) {
        delete shaderProgram;
    }
    if (vertexBuffer) {
        delete vertexBuffer;
    }
    if (vao) {
        delete vao;
    }
}

void OSGViewerRenderer::initializeTriangle()
{
    // 顶点着色器源码
    const char *vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        void main()
        {
            gl_Position = vec4(position, 1.0);
        }
    )";

    // 片段着色器源码
    const char *fragmentShaderSource = R"(
        #version 330 core
        out vec4 color;
        void main()
        {
            color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        }
    )";

    // 创建着色器程序
    shaderProgram = new QOpenGLShaderProgram();
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    shaderProgram->link();

    // 定义三角形顶点
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // 创建VAO, VBO
    vao = new QOpenGLVertexArrayObject();
    vao->create();
    vao->bind();

    vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vertexBuffer->create();
    vertexBuffer->bind();
    vertexBuffer->allocate(vertices, sizeof(vertices));

    // 设置顶点属性
    shaderProgram->enableAttributeArray(0);
    shaderProgram->setAttributeBuffer(0, GL_FLOAT, 0, 3, 3 * sizeof(float));

    // 解绑
    vertexBuffer->release();
    vao->release();
}

void OSGViewerRenderer::render()
{
    if (!initialized) {
        initializeOpenGLFunctions();
        initializeTriangle();
        initialized = true;
    }

    // 清除屏幕
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 绘制三角形
    if (shaderProgram && vao) {
        shaderProgram->bind();
        vao->bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        vao->release();
        shaderProgram->release();
    }
}

QOpenGLFramebufferObject *OSGViewerRenderer::createFramebufferObject(const QSize &size)
{
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    return new QOpenGLFramebufferObject(size, format);
}