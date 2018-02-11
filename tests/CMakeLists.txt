add_executable(
    options_test

    options.cpp
)
target_link_libraries(
    options_test

    options
)

add_test(NAME OptionsTest COMMAND $<TARGET_FILE:options_test>)