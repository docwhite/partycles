TARGET = Partycles
CONFIG += console c++11

# Define output directories
DESTDIR = release
OBJECTS_DIR = release/obj
CUDA_OBJECTS_DIR = release/cuda

INCLUDEPATH += \
    $$PWD/include \
    /usr/include/cuda


# Project Source files
SOURCES += \
    $$PWD/src/main.cpp \
    $$PWD/src/viewport.cpp \
    $$PWD/src/particleswindow.cpp \
    $$PWD/src/particle.cpp \
    $$PWD/src/particlesystem.cpp

# Project header files
HEADERS += \
    $$PWD/include/viewport.h \
    $$PWD/include/particleswindow.h \
    $$PWD/include/particle.h \
    $$PWD/include/particlesystem.h

LIBS += -L/usr/lib64/nvidia -lcuda -L/usr/lib64 -lcudart -L/usr/lib64/nvidia -lGL

# Cuda
CUDA_SOURCES += $$PWD/kernel/*.cu
CUDA_INCLUDEPATH=/usr/include/cuda
NVCC_OPTS = -O3 -arch=sm_20 -Xcompiler -Wall -Xcompiler -Wextra -m64

cuda_d.input = CUDA_SOURCES
cuda_d.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
cuda_d.commands = /usr/bin/nvcc $$NVCC_OPTS -I$$PWD/include -I $$CUDA_INCLUDEPATH -L/usr/lib64/nvidia -lcuda -L/usr/lib64 -lcudart -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
cuda_d.dependency_type = TYPE_C
QMAKE_EXTRA_COMPILERS += cuda_d

DISTFILES += \
    kernel/ramon.cu
