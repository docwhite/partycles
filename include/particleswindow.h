#ifndef PARTICLESWINDOW_H
#define PARTICLESWINDOW_H

#include <QtGui/QOpenGLShaderProgram>
#include "viewport.h"
#include "particlesystem.h"
#include "particle.h"

class ParticlesWindow : public Viewport
{
public:
    ParticlesWindow();

    void initialize() Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;

private:
    GLuint m_posAttr;
    ParticleSystem m_particle_system;
    QOpenGLShaderProgram *m_program;
    int m_frame;

protected:
    void keyPressEvent(QKeyEvent* ev);
};

#endif // PARTICLESWINDOW_H
