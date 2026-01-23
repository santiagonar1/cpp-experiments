find_package(Threads REQUIRED)

add_executable(${EXECUTABLE_NAME}
        main.cpp
)

target_link_libraries(${EXECUTABLE_NAME}
        PRIVATE ${LIBRARY_NAME}
        PRIVATE Threads::Threads
)
