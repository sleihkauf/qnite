project(qnanopainter)

find_package(Qt5 COMPONENTS Quick REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(BUILD_GLES_BACKEND TRUE)

add_library(
    qnanopainter
STATIC
    qnanopainter/libqnanopainter/qnanopainter.cpp
    qnanopainter/libqnanopainter/qnanocolor.cpp
    qnanopainter/libqnanopainter/qnanolineargradient.cpp
    qnanopainter/libqnanopainter/qnanoimagepattern.cpp
    qnanopainter/libqnanopainter/qnanoimage.cpp
    qnanopainter/libqnanopainter/qnanofont.cpp
    qnanopainter/libqnanopainter/qnanoradialgradient.cpp
    qnanopainter/libqnanopainter/qnanoboxgradient.cpp
    qnanopainter/libqnanopainter/qnanowindow.cpp
    qnanopainter/libqnanopainter/private/qnanodebug.cpp
    qnanopainter/libqnanopainter/qnanoquickitem.cpp
    qnanopainter/libqnanopainter/qnanoquickitempainter.cpp
    qnanopainter/libqnanopainter/nanovg/nanovg.c
    $<$<BOOL:${BUILD_GLES_BACKEND}>:qnanopainter/libqnanopainter/private/qnanobackendgles2.cpp>
    $<$<BOOL:${BUILD_GLES_BACKEND}>:qnanopainter/libqnanopainter/private/qnanobackendgles3.cpp>
    $<$<BOOL:${BUILD_GL_BACKEND}>:qnanopainter/libqnanopainter/private/qnanobackendgl2.cpp>
    $<$<BOOL:${BUILD_GL_BACKEND}>:qnanopainter/libqnanopainter/private/qnanobackendgl3.cpp>
)

target_compile_features(
    qnanopainter
PUBLIC
    cxx_std_14
)

target_compile_definitions(
    qnanopainter
PUBLIC
    NANOVG_GLES2
    QNANO_BUILD_GLES_BACKENDS
)

target_link_libraries(
    qnanopainter
PRIVATE
    Qt5::Quick
    $<$<BOOL:${BUILD_GLES_BACKEND}>:GLESv2>
    $<$<BOOL:${BUILD_GL_BACKEND}>:Gl>
)

target_include_directories(
    qnanopainter
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/qnanopainter/libqnanopainter
)
