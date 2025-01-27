add_library(linked_list linked_list.c)
target_compile_options(linked_list PUBLIC
    $<$<PLATFORM_ID:Linux,GNU>:-std=c23>
)
add_executable(llTest linked_list.t.c)
target_link_libraries(llTest PRIVATE linked_list)
set(sanitizerOpts
    "-fsanitize=address,undefined"
    -fno-omit-frame-pointer
)
target_compile_options(llTest PRIVATE
    "$<$<AND:$<CONFIG:Debug>,$<PLATFORM_ID:Linux,GNU>>:${sanitizerOpts}>"
)
target_link_options(llTest PRIVATE
    "$<$<AND:$<CONFIG:Debug>,$<PLATFORM_ID:Linux,GNU>>:${sanitizerOpts}>"
)
add_test(NAME linked_list.t COMMAND llTest 100)

