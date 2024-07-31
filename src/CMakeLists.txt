add_library(pi_dongle_lib pi_dongle_lib.cpp)

find_package(Libinput)
find_package(PkgConfig REQUIRED)

pkg_check_modules(LIBUDEV libudev REQUIRED)


include_directories(. ${LIBUDEV_INCLUDE_DIRECTORIES})
target_link_libraries(pi_dongle_lib PRIVATE Libinput::Libinput ${LIBUDEV_LIBRARIES})

