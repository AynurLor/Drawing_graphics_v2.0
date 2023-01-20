QT       += core
QT += openglwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets openglwidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../FileReader/objectfilereader.cc \
    ../RecordModel/GifSource/giflib/dgif_lib.c \
    ../RecordModel/GifSource/giflib/egif_lib.c \
    ../RecordModel/GifSource/giflib/gif_err.c \
    ../RecordModel/GifSource/giflib/gif_font.c \
    ../RecordModel/GifSource/giflib/gif_hash.c \
    ../RecordModel/GifSource/giflib/gifalloc.c \
    ../RecordModel/GifSource/giflib/quantize.c \
    ../RecordModel/GifSource/qgifimage.cpp \
    ../RecordModel/recordmodel.cc \
    ../Scene/scene_paint.cc \
    main.cpp \
    view.cpp

HEADERS += \
    ../FacadeController/facadecontroller.hpp \
    ../FacadeModel/facademodel.hpp \
    ../FileReader/filereader.hpp \
    ../NormalizationParameters/normalizationparameters.hpp \
    ../ObjectDataModel/objectdatamodel.hpp \
    ../RecordModel/GifSource/giflib/gif_hash.h \
    ../RecordModel/GifSource/giflib/gif_lib.h \
    ../RecordModel/GifSource/giflib/gif_lib_private.h \
    ../RecordModel/GifSource/qgifglobal.h \
    ../RecordModel/GifSource/qgifimage.h \
    ../RecordModel/GifSource/qgifimage_p.h \
    ../RecordModel/recordmodel.hpp \
    ../Scene/scene_paint.hpp \
    ../Scene/scene_style.hpp \
    ../TransformModel/transformmodel.hpp \
    view.h

FORMS += \
    view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    ../RecordModel/GifSource/gifimage.pro

DISTFILES += \
    ../RecordModel/GifSource/giflib/AUTHORS \
    ../RecordModel/GifSource/giflib/COPYING \
    ../RecordModel/GifSource/giflib/README

RESOURCES += \
    icons.qrc
