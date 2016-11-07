#include <iostream>

#include <QtGui/QOpenGLShaderProgram>
#include "particleswindow.h"

void advance_particles(ParticleSystem& _ps, float *_vertices);
void modifying_vbo(unsigned int VBO_id);

static const char *vertexShaderSource =
    "attribute highp vec3 posAttr;\n"
    "void main() {\n"
    "   gl_PointSize = 1.0;\n"
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
    this->resize(1920, 1080);
    this->setFormat(format);
    m_particle_system = ParticleSystem();
}

void ParticlesWindow::initialize()
{
//    for (int i = 0; i < 1000000; i++) {
//        m_particle_system.birth_particle();
//    }
    m_particle_system.initialize_system(1000000);

    m_vertices = std::vector<float>(3*m_particle_system.numParts);
    std::fill(m_vertices.begin(), m_vertices.end(), 0.0f);

    glViewport(0, 0, width(), height());

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();

    m_posAttr = m_program->attributeLocation("posAttr");

    m_VAO = new QOpenGLVertexArrayObject(this);
    m_VBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

    m_VAO->create();
    m_VBO->create();
    m_VBO->setUsagePattern(QOpenGLBuffer::DynamicDraw);

    m_VAO->bind();
    m_VBO->bind();

    std::cout << "Number of particles: " << m_particle_system.numParts << std::endl;

    m_VBO->allocate(&m_vertices[0], 3 * m_particle_system.numParts * sizeof(GLfloat));

    m_program->setAttributeBuffer(m_posAttr, GL_FLOAT, 0, 3);
    m_program->enableAttributeArray(m_posAttr);

    m_VBO->release();
    m_VAO->release();
}

void ParticlesWindow::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    m_particle_system.advance_particles(m_VBO->bufferId());

    m_program->bind();
    m_VAO->bind();

    glEnable(GL_PROGRAM_POINT_SIZE);
    glDrawArrays(GL_POINTS, 0, m_particle_system.numParts);

    m_VAO->release();
    m_program->release();

    ++m_frame;
}

void ParticlesWindow::keyPressEvent(QKeyEvent *ev)
{
    m_particle_system.birth_particle();
    m_VBO->bind();
    m_VBO->allocate(&m_vertices[0], 3 * m_particle_system.numParts * sizeof(GLfloat));
    m_VBO->release();
}
