#ifndef PARTICLESWINDOW_H
#define PARTICLESWINDOW_H

#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLVertexArrayObject>
#include <QtGui/QOpenGLBuffer>
#include "viewport.h"
#include "particlesystem.h"

class ParticlesWindow : public Viewport
{
public:
    ParticlesWindow();

    void initialize() Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;

private:
    std::vector<GLfloat> m_vertices;
    GLuint m_posAttr;
    QOpenGLShaderProgram *m_program;
    QOpenGLBuffer* m_VBO;
    QOpenGLVertexArrayObject* m_VAO;
    ParticleSystem m_particle_system;
    int m_frame;

protected:
    void keyPressEvent(QKeyEvent* ev);
};

#endif // PARTICLESWINDOW_H
