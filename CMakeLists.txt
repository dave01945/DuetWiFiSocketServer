# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)
add_compile_definitions(DEBUG)
set(EXTRA_COMPONENT_DIRS src main)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(DuetWiFiSocketServer)

# Add linker wrap flags for esp_log functions to resolve WiFi library dependencies
# These wrapper implementations are provided by the arduino component (esp32-hal-log-wrapper.c)
# Force the linker to include the wrapper symbols even if not initially referenced
add_link_options(
    "-Wl,--wrap=esp_log_write" 
    "-Wl,--wrap=esp_log_writev"
    "-Wl,-u,__wrap_esp_log_write"
    "-Wl,-u,__wrap_esp_log_writev"
)


