# MCU dependency files
add_library(MCU_FILES STATIC)

target_link_libraries(MCU_FILES PUBLIC
        cmsis_core
        pico_stdlib
        pico_stdlib_headers
        hardware_clocks
        hardware_dma
        hardware_flash
        hardware_resets
        hardware_spi
        hardware_structs
        )

add_library(DEVICE_FILES STATIC)

target_sources(DEVICE_FILES PUBLIC
        ${PORT_DIR}/device/src/device_fwup.c
        )

target_include_directories(DEVICE_FILES PUBLIC
        ${PORT_DIR}/device/inc
        ${PORT_DIR}
        )
        
target_link_libraries(DEVICE_FILES PUBLIC
        MCU_FILES
        )

# ioLibrary_Driver
add_library(IOLIBRARY_FILES STATIC)

target_sources(IOLIBRARY_FILES PUBLIC
        ${PORT_DIR}/ioLibrary_Driver/src/w5x00_spi.c
        )

target_include_directories(IOLIBRARY_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${PORT_DIR}/ioLibrary_Driver/inc
        ${PORT_DIR}
        )

target_link_libraries(IOLIBRARY_FILES PRIVATE
        MCU_FILES
        ETHERNET_FILES
        )

# HTTP_SERVER
add_library(HTTPSERVER_FILES STATIC)

target_sources(HTTPSERVER_FILES PUBLIC
        ${PORT_DIR}/http_server/src/http_fwup.c
        ${PORT_DIR}/http_server/src/httpParser.c
        ${PORT_DIR}/http_server/src/httpServer.c
        ${PORT_DIR}/http_server/src/httpUtil.c
        )

target_include_directories(HTTPSERVER_FILES PUBLIC
        ${PORT_DIR}/http_server/inc
        ${PORT_DIR}
        )
        
target_link_libraries(HTTPSERVER_FILES PUBLIC
        MCU_FILES
        DEVICE_FILES
        IOLIBRARY_FILES
        )
