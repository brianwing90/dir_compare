find_package(OpenSSL REQUIRED)

add_library(dir_compare Directory.cpp utils.h)
target_link_libraries(dir_compare PRIVATE ${OPENSSL_LIBRARIES})
