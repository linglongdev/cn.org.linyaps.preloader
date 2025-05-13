cmake_minimum_required(VERSION 3.16)

project(
  preloader
  VERSION 0.0.2
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(QT_VERSION_MAJOR "6" CACHE STRING "The major version of Qt.")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(QT_COMPONENTS Core Gui DBus Widgets Quick)

# linyaps dtk runtime only supports either Qt5 or Qt6
message(STATUS "compiling with Qt${QT_VERSION_MAJOR}")
find_package(
  Qt${QT_VERSION_MAJOR}
  COMPONENTS Core Gui Quick
  REQUIRED)

find_package(Dtk${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widget)

add_executable(preloader main.cpp preloader.qrc)

set(QT_COMPONENT_LIST)
foreach(COMPONENT ${QT_COMPONENTS})
  list(APPEND QT_COMPONENT_LIST "Qt${QT_VERSION_MAJOR}::${COMPONENT}")
endforeach()

target_link_libraries(
  preloader PRIVATE ${QT_COMPONENT_LIST} Dtk${QT_VERSION_MAJOR}::Core
                    Dtk${QT_VERSION_MAJOR}::Widget)

include(GNUInstallDirs)
install(TARGETS preloader RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
