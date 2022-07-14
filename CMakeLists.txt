cmake_minimum_required(VERSION 3.0)
project(extract-xiso)

string(TOUPPER __${CMAKE_SYSTEM_NAME}__ TARGET_OS)

set(SOURCE_FILES
	extract-xiso.c
)

add_executable(extract-xiso ${SOURCE_FILES})
target_compile_definitions(extract-xiso PRIVATE ${TARGET_OS})

# 64-bit builds of extract-xiso are known to create bad images.
# See https://github.com/XboxDev/extract-xiso/issues/29
target_compile_options(extract-xiso PUBLIC -m32)
target_link_options(extract-xiso PUBLIC -m32)

install(TARGETS extract-xiso RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
