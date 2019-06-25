cmake_minimum_required(VERSION 3.10)

project(cli-table-cpp)

set(CMAKE_CXX_STANDARD 17)

set(FILES src/main.cpp src/Table.hpp src/Utils.hpp src/Utils.cpp src/Table.cpp)



#------------------------------

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.14/conan.cmake"
                 "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(CONANFILE conanfile.txt
                    BASIC_SETUP CMAKE_TARGETS
                    BUILD missing
                    )

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(tests)

add_executable(cli-table-cpp ${FILES})

target_link_libraries(cli-table-cpp ${CONAN_LIBS})

