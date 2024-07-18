# Dimacs Converter
add_executable(pi_dongle_test pi_dongle_test.cpp)
target_link_libraries(pi_dongle_test PRIVATE pi_dongle_lib)

add_test(NAME pi_dongle_test
         COMMAND pi_dongle_test
)   

