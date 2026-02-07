idf_component_register(SRCS "SocketServer.cpp"
                            "Misc.cpp"
                            "Listener.cpp"
                            "HSPI.cpp"
                            "Connection.cpp"

                    INCLUDE_DIRS "." "include" REQUIRES arduino wifi_provisioning)

# Ensure wrapper symbols from arduino component are linked
# These are needed by the WiFi library
target_link_libraries(${COMPONENT_LIB} INTERFACE 
    "-Wl,-u,__wrap_esp_log_write"
    "-Wl,-u,__wrap_esp_log_writev"
)