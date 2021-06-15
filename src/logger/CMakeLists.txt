set(LIB_NAME logger)
set(LIBS_NAME ${LIB_NAME}_LIBS)

set(LIB_SRC_PATH ${CMAKE_CURRENT_LIST_DIR}/src)

set(LIB_INC_PATH_PRI ${CMAKE_CURRENT_LIST_DIR}/inc/private)

set(LIB_INC_PATH_PUB ${CMAKE_CURRENT_LIST_DIR}/inc/public)

message(status "Loggerfsdmfsjdfkj:     ${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB SOURCES "${LIB_SRC_PATH}/*.c*")

# Place here all component source files that should be included in this library except all the generated files
set(SRC_FILES_OWN ${SOURCES})

# Place here all generated source files
set(SRC_FILES_GEN
  # ./gen/Example/example.cc
)

set(SRC_FILES
  ${SRC_FILES_OWN}
  ${SRC_FILES_GEN}
)

message(STATUS "SRC_FILES: ${SRC_FILES}")
message(STATUS "PRIVATE INCLUDE_DIRS: ${LIB_INC_PATH_PRI}")
message(STATUS "PUBLIC INCLUDE_DIRS: ${LIB_INC_PATH_PUB}")

# create library for this directory that the main executable and the main library will link against
add_library(${LIB_NAME} STATIC ${SRC_FILES})

# set include directories to PUBLIC for them to be propagated to targets that link against this library
target_include_directories(${LIB_NAME}
  PUBLIC ${LIB_INC_PATH_PUB}
  PRIVATE ${LIB_INC_PATH_PRI}
)

target_compile_options(${LIB_NAME}
  PUBLIC -Wall -DLINUX
  $<$<CONFIG:Debug>:
    -DVERBOSE_LEVEL=2 -O0 -g3
  >
)

# This needs to be repeated in order to have the right order of -l flags for the linker
set(${LIBS_NAME}
  ${LIB_NAME}
  ${LIB_NAME}
  PARENT_SCOPE
)

#install (TARGETS ${LIB_NAME} DESTINATION lib)
