cmake_minimum_required(VERSION 3.6)

project(fcitx-virtualkeyboard-adapter VERSION 5.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(REQUIRED_FCITX5_VERSION 5.0.14)
find_package(Fcitx5Core "${REQUIRED_FCITX5_VERSION}" REQUIRED)
# find_package(Fcitx5Module REQUIRED COMPONENTS NotificationItem)
# find_package(PkgConfig REQUIRED)

add_subdirectory(src)
