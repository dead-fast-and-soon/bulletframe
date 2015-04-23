cmake_minimum_required(VERSION 2.8.5)
cmake_policy(SET CMP0048 NEW)

# Project Name
# ===============================================

project(bulletframe VERSION 0.1 LANGUAGES CXX)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") #for g++

include(ExternalProject)

set(ROOT        ${CMAKE_HOME_DIRECTORY})

set(INCLUDE_DIR ${ROOT}/lib)

# for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${INCLUDE_DIR}")

# for static libraries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  "${INCLUDE_DIR}")

# for shared (dynamic) libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${INCLUDE_DIR}")

# Add Dependencies
# ===============================================

# set a variable to a external projects directory
set(EXT_DIR        "${CMAKE_HOME_DIRECTORY}/ext")
set(EXT_STAMP_DIR  "${EXT_DIR}/.stamp")
set(EXT_TMP_DIR    "${EXT_DIR}/.tmp")

# this will be the target for ExternalProject (NOT the target for the library)
set(OCTAL_NAME          "octal-git")
# root directory
set(OCTAL_ROOT          "${EXT_DIR}/${OCTAL_NAME}")

ExternalProject_Add(${OCTAL_NAME}
    PREFIX          "${OCTAL_ROOT}"
    TMP_DIR         "${EXT_TMP_DIR}/${OCTAL_NAME}"
    STAMP_DIR       "${EXT_STAMP_DIR}/${OCTAL_NAME}"
    # - Download Step ------------------
    GIT_REPOSITORY  "https://github.com/TheOctopod/octal-cpp.git"
    # - Update Step --------------------
    UPDATE_COMMAND  "" # no update step
    # - Configure Step -----------------
    SOURCE_DIR      "${OCTAL_ROOT}" # source folder is the root directory
    # - Build Step ---------------------
    BINARY_DIR      "${OCTAL_ROOT}/bin"
    # - Install Step -------------------
    INSTALL_COMMAND "" # no install step
    CMAKE_ARGS
    "-DCMAKE_BUILD_TYPE=Release"
)


add_library("octal" STATIC IMPORTED)
if(MSVC)
    # find the .lib
    set_target_properties("octal" PROPERTIES
        IMPORTED_LOCATION_DEBUG       "${OCTAL_ROOT}/lib/Debug/octal.lib"
        IMPORTED_LOCATION_RELEASE     "${OCTAL_ROOT}/lib/Release/octal.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${OCTAL_ROOT}/include"
    )
else()
    # find the .a
    set_target_properties("octal" PROPERTIES
        IMPORTED_LOCATION             "${OCTAL_ROOT}/lib/liboctal.a"
        INTERFACE_INCLUDE_DIRECTORIES "${OCTAL_ROOT}/include"
    )
endif()

# Add Source Folder
# ===============================================

add_subdirectory(src) # will set BF_SOURCES and BF_LINKS variables

add_dependencies(${PROJECT_NAME} ${OCTAL_NAME})

set(COLOR TRUE)

if(COLOR)
    string(ASCII 27 ESCAPE)
    set(C_3 "${ESCAPE}[33m") # yellow
    set(C_R "${ESCAPE}[0m")  # reset
endif()


message("${C_3}===========================================${C_R}")
message("  Pre-build Information")
message("${C_3} ----------------------------------------- ${C_R}")
message("  CMAKE Generator  : ${CMAKE_GENERATOR}")
message("  System Name      : ${CMAKE_SYSTEM_NAME}")
message("  Binary Directory : ${CMAKE_BINARY_DIR}")
message("  Source Directory : ${CMAKE_SOURCE_DIR}")
message("  Install Directory: ${CMAKE_INSTALL_PREFIX}")

message("${C_3}===========================================${C_R}")
message("  Including Sources")
message("${C_3} ----------------------------------------- ${C_R}")

foreach(ARG ${BF_SOURCES})
    message("    - ${ARG}")
endforeach()

message("${C_3}===========================================${C_R}")
message("  Linking Libraries")
message("${C_3} ----------------------------------------- ${C_R}")

foreach(ARG ${BF_LINKS})
    get_target_property(LINK_TYPE ${ARG} TYPE)
    message("    - ${ARG} [${LINK_TYPE}]")
endforeach()

message("${C_3}===========================================${C_R}")
