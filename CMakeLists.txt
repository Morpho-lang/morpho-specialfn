cmake_minimum_required(VERSION 3.13)
project(morpho-specialfn)

# Build the library as a plugin
add_library(specialfn MODULE "")

# Suppress 'lib' prefix
set_target_properties(specialfn PROPERTIES PREFIX "")

# Add sources
add_subdirectory(src)

find_path(MORPHO_INCLUDE_DIR
    NAMES morpho.h morpho/morpho.h
    HINTS
        $ENV{MORPHO_INCLUDE_DIR}
        /usr/local/opt/morpho/include
        /opt/homebrew/opt/morpho/include
        /home/linuxbrew/.linuxbrew/include/morpho
        /home/linuxbrew/.linuxbrew/include
        /usr/local/include/morpho
        /usr/local/include
        /opt/homebrew/include
)

find_library(MORPHO_LIBRARY
    NAMES morpho libmorpho
    HINTS
        $ENV{MORPHO_LIBRARY}
        /usr/local/opt/morpho/lib
        /opt/homebrew/opt/morpho/lib
        /home/linuxbrew/.linuxbrew/lib
        /usr/local/lib
        /opt/homebrew/lib
)

find_library(MATH_LIBRARY m)

if(NOT MORPHO_INCLUDE_DIR)
    message(FATAL_ERROR
        "Could not find Morpho headers (morpho.h). "
        "Install Morpho or set MORPHO_INCLUDE_DIR to the include directory "
        "that contains morpho.h or morpho/morpho.h.")
endif()

if(NOT MORPHO_LIBRARY)
    message(FATAL_ERROR
        "Could not find libmorpho. "
        "Install Morpho or set MORPHO_LIBRARY to the full path of the Morpho library.")
endif()

get_filename_component(MORPHO_INCLUDE_PARENT ${MORPHO_INCLUDE_DIR} DIRECTORY)

# Include path should allow #include <morpho/morpho.h> and related headers.
target_include_directories(specialfn PUBLIC
    ${MORPHO_INCLUDE_DIR}
    ${MORPHO_INCLUDE_PARENT}
)

file(GLOB morpho_subdirectories LIST_DIRECTORIES true ${MORPHO_INCLUDE_DIR}/*)
foreach(dir ${morpho_subdirectories})
    if(IS_DIRECTORY ${dir})
        target_include_directories(specialfn PUBLIC ${dir})
    endif()
endforeach()

target_link_libraries(specialfn ${MORPHO_LIBRARY} ${MATH_LIBRARY})

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "Install prefix" FORCE)
endif()

install(TARGETS specialfn LIBRARY DESTINATION lib/)
