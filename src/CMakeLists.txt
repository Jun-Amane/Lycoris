## Setup cross-compile toolchain 
set(CROSS_COMPILE_PREFIX arm-none-eabi-)
include(${STM32_CMAKE_DIR}/cmake/gcc-arm-none-eabi.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/target-def.cmake)

## auto-set variables from user input
set(MCU_FLAGS "${CPU} -mthumb ${FPU} ${FLOAT_ABI}")
set(LINK_FLAGS "${MCU_FLAGS} -Wl,--gc-sections")
set(EXTRA_LINK_FLAGS "-Wl,-Map=${PROJECT_NAME}.map,--cref,--no-warn-mismatch -specs=nano.specs -specs=nosys.specs")
include(${STM32_CMAKE_DIR}/cmake/stm32-gcc-flags.cmake)

# print summary of configurations
message(STATUS "MCU_FAMILY: ${MCU_FAMILY}")
message(STATUS "MCU_NAME: ${MCU_NAME}")
message(STATUS "Specified C compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Linker script: ${LINKER_SCRIPT}")
message(STATUS "Use LL library: ${USE_LL_LIB}")
message(STATUS "Use HAL library: ${USE_HAL_LIB}")
message(STATUS "Use Segger SystemView library: ${USE_SYSTEM_VIEW}")

## version information
set(VERSION_MAJOR 0 CACHE STRING "Project major version number.")
set(VERSION_MINOR 1 CACHE STRING "Project minor version number.")
set(VERSION_PATCH 0 CACHE STRING "Project patch version number.")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/source/Core/Inc ${STM32_PROJ_FOLDER}/dev/inc ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/source/USB_DEVICE/App ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/source/USB_DEVICE/Target ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/source/Middlewares/ST/STM32_USB_Device_Library/Core/Inc ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/source/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc)
if(USE_SYSTEM_VIEW)
add_definitions("-DENABLE_SYSTEMVIEW")
endif()

## add project components
set(ELF_TARGET ${PROJECT_NAME}.elf)
set(PROJ_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libraries)

# project-specific modules
# add_subdirectory(driver)

# common libraries
add_subdirectory(${PROJ_LIB_PATH}/CMSIS ${CMAKE_BINARY_DIR}/libraries/CMSIS)

#${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/source/Middlewares/ST/STemWin/inc ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/source/Middlewares/ST/STM32_USB_Device_Library/Core/Inc ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/source/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc
add_subdirectory(${PROJ_LIB_PATH}/STM32F1xx_HAL_Driver ${CMAKE_BINARY_DIR}/libraries/STM32F1xx_HAL_Driver)

# STM32CubeMX generated source files
set(PROJ_SRC
    ${STM32_PROJ_FOLDER}/source/Core/Src/main.cpp
    ${STM32_PROJ_FOLDER}/source/Core/Src/Lycoris_init.cpp
    ${STM32_PROJ_FOLDER}/source/Core/Src/Lycoris.cpp
    ${STM32_PROJ_FOLDER}/source/Core/Src/stm32f1xx_it.c
    ${STM32_PROJ_FOLDER}/source/Core/Src/system_stm32f1xx.c
    ${STM32_PROJ_FOLDER}/source/Core/Src/stm32f1xx_hal_msp.c
    ${STM32_PROJ_FOLDER}/source/USB_DEVICE/App/usb_device.c
    ${STM32_PROJ_FOLDER}/source/USB_DEVICE/App/usbd_desc.c
    ${STM32_PROJ_FOLDER}/source/USB_DEVICE/App/usbd_custom_hid_if.c
    ${STM32_PROJ_FOLDER}/source/USB_DEVICE/Target/usbd_conf.c
    ${STM32_PROJ_FOLDER}/source/startup_stm32f103x6.s
)

set(DEV_SRC
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_pwr.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_i2c.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_gpio.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_flash.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_iwdg.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_spi.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_sdio.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_crc.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_wwdg.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_adc.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_dbgmcu.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_cec.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_fsmc.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_can.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_rtc.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_rcc.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_exti.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_usart.c
${STM32_PROJ_FOLDER}/dev/src/misc.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_dma.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_dac.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_bkp.c
${STM32_PROJ_FOLDER}/dev/src/stm32f10x_tim.c

)

set(USB_SRC
${STM32_PROJ_FOLDER}/source/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c
${STM32_PROJ_FOLDER}/source/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c
${STM32_PROJ_FOLDER}/source/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c

${STM32_PROJ_FOLDER}/source/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Src/usbd_customhid.c
)

add_executable(${ELF_TARGET} ${PROJ_SRC} ${USB_SRC} ${DEV_SRC})
target_compile_definitions(${ELF_TARGET} PUBLIC -D${MCU_FAMILY})
target_link_libraries(${ELF_TARGET} PUBLIC cmsis stm32f1xx_hal -lc -lm -lnosys)
target_link_libraries(${ELF_TARGET} PRIVATE -T${LINKER_SCRIPT} ${EXTRA_LINK_FLAGS})
target_include_directories(${ELF_TARGET} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source/Core/Inc>)

## add post-build targets
include(${STM32_CMAKE_DIR}/cmake/stm32-gcc-postbuild.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/stm32-gcc-jlink.cmake)
