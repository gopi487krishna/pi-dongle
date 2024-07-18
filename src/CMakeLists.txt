add_library(pi_dongle_lib pi_dongle_lib.cpp)

find_package(PkgConfig REQUIRED)

pkg_check_modules(PC_EVDEV libevdev REQUIRED)

find_path(EVDEV_INCLUDE_DIR libevdev/libevdev.h
        HINTS ${PC_EVDEV_INCLUDE_DIRS} ${PC_EVDEV_INCLUDEDIR})
find_library(EVDEV_LIBRARY
        NAMES evdev libevdev)


include_directories(. ${EVDEV_INCLUDE_DIR} )
target_link_libraries(pi_dongle_lib ${EVDEV_LIBRARY})

