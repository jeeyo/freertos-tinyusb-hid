cmake_minimum_required(VERSION 3.5)

# build configuration
option(DEBUG "Debug mode" OFF)

project(freertos-tinyusb-hid C CXX ASM)

set(FREERTOS_DIR ./3rdparty/FreeRTOS)
set(PICO_SDK_PATH ./3rdparty/pico-sdk)

set(PICO_BOARD pico2)

include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

set(SOURCES )
set(LIBS )

list(APPEND SOURCES
  ./src/hooks.c
  ${FREERTOS_DIR}/croutine.c
  ${FREERTOS_DIR}/event_groups.c
  ${FREERTOS_DIR}/list.c
  ${FREERTOS_DIR}/queue.c
  ${FREERTOS_DIR}/stream_buffer.c
  ${FREERTOS_DIR}/tasks.c
  ${FREERTOS_DIR}/timers.c
  ${FREERTOS_DIR}/portable/MemMang/heap_3.c
  ${FREERTOS_DIR}/portable/ThirdParty/GCC/RP2350_ARM_NTZ/non_secure/port.c
  ${FREERTOS_DIR}/portable/ThirdParty/GCC/RP2350_ARM_NTZ/non_secure/portasm.c
)

pico_sdk_init()

add_executable(freertos-tinyusb-hid ${SOURCES} ./src/main.c)

if(DEBUG)
  target_compile_options(freertos-tinyusb-hid PRIVATE -O0 -g)
endif()

target_include_directories(freertos-tinyusb-hid PRIVATE
  ./include
  ${FREERTOS_DIR}/include
  ${FREERTOS_DIR}/portable/ThirdParty/GCC/RP2350_ARM_NTZ/non_secure
  ${PICO_SDK_PATH}/lib/tinyusb/src
)

list(APPEND LIBS
  pico_stdlib
  pico_stdio_semihosting
  pico_multicore
  hardware_exception
  tinyusb_device
)

target_link_libraries(freertos-tinyusb-hid PRIVATE ${LIBS})

pico_enable_stdio_usb(freertos-tinyusb-hid 0)
pico_enable_stdio_uart(freertos-tinyusb-hid 0)
pico_enable_stdio_semihosting(freertos-tinyusb-hid 1)

pico_add_extra_outputs(freertos-tinyusb-hid)
