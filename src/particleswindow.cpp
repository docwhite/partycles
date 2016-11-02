#include <iostream>

#include <QtGui/QOpenGLShaderProgram>
#include "particleswindow.h"

extern "C"
void ramon(ParticleSystem& _ps, float *_vertices);

static const char *vertexShaderSource =
    "attribute highp vec4 posAttr;\n"
    "void main() {\n"
    "   gl_PointSize = 10.0;\n"
    "   gl_Position = posAttr;\n"
    "}\n";

static const char *fragmentShaderSource =
    "void main() {\n"
    "   gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
    "}\n";

ParticlesWindow::ParticlesWindow()
    : m_program(0)
    , m_frame(0)
{
    QSurfaceFormat format;
    format.setSamples(16);
    this->resize(640, 480);
    this->setFormat(format);
    m_particle_system = ParticleSystem();
}

void ParticlesWindow::initialize()
{
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");

    m_particle_system.birth_particle();
}

void ParticlesWindow::render()
{
    float vertices[m_particle_system.m_particles.size()*3];
    ramon(m_particle_system, vertices);

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, vertices);

    glEnableVertexAttribArray(m_posAttr);

    glDrawArrays(GL_POINTS, 0, m_particle_system.m_particles.size());
    glEnable(GL_PROGRAM_POINT_SIZE);

    glDisableVertexAttribArray(m_posAttr);

    m_program->release();

    ++m_frame;
}

void ParticlesWindow::keyPressEvent(QKeyEvent *ev) {
    std::cout << "HEY!" << std::endl;
    m_particle_system.birth_particle();
}

//void ParticlesWindow::pass_particle(std::vector<Particle> _particles)
//{
//    for(std::vector<Particle>::iterator it = _particles.begin(); it != _particles.end(); ++it) {
//        std::cout << "HELLO" << std::endl;
//        /* std::cout << *it; ... */
//    }
//}
