cmake_minimum_required(VERSION 3.16)

# Nom et version du projet
project(CPPRT VERSION 0.1 LANGUAGES CXX)

# Activer les fonctionnalités automatiques de Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Configurer la version standard de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Trouver les modules Qt requis (Widgets et Network)
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Network)
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

# Fichiers sources et en-têtes
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    tcpserverwindow.cpp
    tcpserverwindow.h
    clientwindow.cpp
    clientwindow.h

)

# Ajouter l'exécutable
qt_add_executable(CPPRT
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    clientwindow.ui

)

# Lier les bibliothèques Qt nécessaires
target_link_libraries(CPPRT PRIVATE Qt6::Widgets Qt6::Network)

# Configuration pour macOS (si applicable)
if(APPLE)
    set_target_properties(CPPRT PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CPPRT
    )
endif()

# Configuration pour Windows (si applicable)
if(WIN32)
    set_target_properties(CPPRT PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# Installation des fichiers
install(TARGETS CPPRT
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalisation pour Qt 6
qt_finalize_executable(CPPRT)
