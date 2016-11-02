#include <iostream>
#include <QtGui/QGuiApplication>
#include "particleswindow.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    ParticlesWindow window;
    window.show();
    window.setAnimating(true);

    return app.exec();
}

//#include <QtCore/QCoreApplication>
//#include "particle.h"
//#include <iostream>

//extern "C"
//void runCudaPart(Particle* _p);

//int main(int argc, char *argv[])
//{
//    Particle* pArray = new Particle[32];

//    std::cout << "Before code ran on GPU" << '\n';
//    for (int i = 0; i < 32; i++) {
//        std::cout << "At i=" << i << " is " << pArray[i].m_value << '\n';
//    }

//    runCudaPart(pArray);

//    std::cout << "After code ran on GPU" << '\n';
//    for (int i = 0; i < 32; i++) {
//        std::cout << "At i=" << i << " is " << pArray[i].m_value << '\n';
//    }

//}
