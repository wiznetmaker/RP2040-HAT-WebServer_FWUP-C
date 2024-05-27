set(TARGET_NAME blink_app)

add_executable(${TARGET_NAME}
        ${TARGET_NAME}.c
        )

target_link_libraries(${TARGET_NAME} PRIVATE
        pico_stdlib
        )

pico_enable_stdio_usb(${TARGET_NAME} 0)
pico_enable_stdio_uart(${TARGET_NAME} 1)

pico_add_extra_outputs(${TARGET_NAME})

set(TARGET_NAME_LINKER ${TARGET_NAME}_linker)
add_executable(${TARGET_NAME_LINKER}
        ${TARGET_NAME}.c
        )
target_link_libraries(${TARGET_NAME_LINKER} PRIVATE
        pico_stdlib
        )
        
pico_set_linker_script(${TARGET_NAME_LINKER} ${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_NAME_LINKER}.ld)
pico_enable_stdio_usb(${TARGET_NAME_LINKER} 0)
pico_enable_stdio_uart(${TARGET_NAME_LINKER} 1)
pico_add_extra_outputs(${TARGET_NAME_LINKER})
