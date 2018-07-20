set(CMAKE_C_FLAGS_DEBUG "-DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG")

set(STM8_TARGET sensor)

if(CMAKE_CROSSCOMPILING)
    set(EXTRA_SRC stm8s_it.c os_stm8s.c)
else()
    set(EXTRA_SRC os_linux.c)
endif()

include_directories(
    ${stdperiph_SOURCE_DIR}
    ${stdperiph_SOURCE_DIR}/inc
    )

add_executable(${STM8_TARGET}
    main.c
    stdio.c
    time.c
    utility.c
    ${EXTRA_SRC}
    )

if(CMAKE_CROSSCOMPILING)
    target_link_libraries(${STM8_TARGET} stdperiph)
else()
    target_link_libraries(${STM8_TARGET} pthread)

    include_directories("${gtest_SOURCE_DIR}/include")

    enable_testing()

    add_executable(unittest unittest.cpp stdio.c utility.c os_linux.c)
    target_link_libraries(unittest gtest gtest_main)
endif()

