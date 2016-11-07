TARGET = Partycles

QT += core gui widgets

INCLUDEPATH += \
    /usr/include/cuda \   #for thrust
    include/

HEADERS += \
    include/particleswindow.h \
    include/particlesystem.h \
    include/viewport.h

SOURCES += \
    src/main.cpp \
    src/particleswindow.cpp \
    src/viewport.cpp

CUDA_CU_FILES= \
    cu/kernel_modifying_vbo.cu

CUDA_HYBRID_CPP_FILES = \
    src/particlesystem.cpp


CXXFLAGS = -c
OBJECTS_DIR = build/obj
MOC_DIR = build/moc

CUDA_INCLUDES = -I/usr/include/cuda -I$$PWD/include

LIBS += $$OBJECTS_DIR/dlink.o
LIBS += -L/usr/lib64 -lcudart
LIBS += -L/usr/lib64/nvidia -lcuda

cuda_hybrid.input = CUDA_HYBRID_CPP_FILES
cuda_hybrid.output = $$OBJECTS_DIR/${QMAKE_FILE_BASE}_hybrid_cuda.o
cuda_hybrid.commands = /usr/bin/nvcc $$CUDA_INCLUDES -x cu -arch=sm_20 -dc -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
cuda_hybrid.dependency_type = TYPE_C
QMAKE_EXTRA_COMPILERS += cuda_hybrid

cuda_kernels.input = CUDA_CU_FILES
cuda_kernels.output = $$OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
cuda_kernels.commands = /usr/bin/nvcc $$CUDA_INCLUDES -arch=sm_20 -dc -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
cuda_kernels.dependency_type = TYPE_C
QMAKE_EXTRA_COMPILERS += cuda_kernels

QMAKE_PRE_LINK = /usr/bin/nvcc $$CUDA_INCLUDES -arch=sm_20 -dlink $$OBJECTS_DIR/*_cuda.o -o $$OBJECTS_DIR/dlink.o
