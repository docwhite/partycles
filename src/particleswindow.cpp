#include <iostream>

#include <QtGui/QOpenGLShaderProgram>
#include "particleswindow.h"

void advance_particles(ParticleSystem& _ps, float *_vertices);
void modifying_vbo(unsigned int VBO_id);

static const char *vertexShaderSource =
    "attribute highp vec3 posAttr;\n"
    "void main() {\n"
    "   gl_PointSize = 10.0;\n"
    "   gl_Position = vec4(posAttr, 1.0);\n"
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

//    for (int i = 0; i < 10; i++)
//        m_particle_system.birth_particle();

//    float vertices[m_particle_system.m_particles.size() * 3];
//    advance_particles(m_particle_system, vertices);
    m_vertices[0] = 0.0f;
    m_vertices[1] = 0.5f;
    m_vertices[2] = 0.0f;

    m_vertices[3] = 0.5f;
    m_vertices[4] = 0.0f;
    m_vertices[5] = 0.0f;

    m_vertices[6] = -0.5f;
    m_vertices[7] = 0.0f;
    m_vertices[8] = 0.0f;

    glViewport(0, 0, width(), height());

    m_VAO = new QOpenGLVertexArrayObject(this);
    m_VBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

    m_VAO->create();
    m_VBO->create();

    m_VBO_index = m_VBO->bufferId(); // the id will be needed by cuda to know which buffer to share

    m_VBO->setUsagePattern(QOpenGLBuffer::DynamicDraw);

    m_VAO->bind();
    m_VBO->bind();

    m_VBO->allocate(m_vertices, 9 * sizeof(GLfloat));

    m_program->setAttributeBuffer(m_posAttr, GL_FLOAT, 0, 3);
    m_program->enableAttributeArray(m_posAttr);

    m_VBO->release();
    m_VAO->release();

    modifying_vbo(m_VBO_index);
}

void ParticlesWindow::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();
    m_VAO->bind();


    glEnable(GL_PROGRAM_POINT_SIZE);
    glDrawArrays(GL_POINTS, 0, 3);

    m_VAO->release();
    m_program->release();

    ++m_frame;
}

void ParticlesWindow::keyPressEvent(QKeyEvent *ev) {
    m_vertices[6] = -0.8f;
    m_vertices[7] = 0.0f;
    m_vertices[8] = 0.0f;

    m_VBO->bind();
    m_VBO->write(0, m_vertices, 9 * sizeof(GLfloat));
    m_VBO->release();

}
