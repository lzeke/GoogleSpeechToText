cmake_minimum_required(VERSION 3.10.0)
project(googlespeechtotext VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)

set(OPENSSL_ROOT_DIR "~/vcpkg/packages/openssl_arm64-linux")
find_package(OpenSSL REQUIRED)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}
    ~/vcpkg/packages/google-cloud-cpp_arm64-linux/share/google_cloud_cpp_speech
    ~/vcpkg/packages/google-cloud-cpp_arm64-linux/share/google_cloud_cpp_grpc_utils
    ~/vcpkg/packages/google-cloud-cpp_arm64-linux/share/google_cloud_cpp_common
    ~/vcpkg/packages/google-cloud-cpp_arm64-linux/share/google_cloud_cpp_googleapis
    ~/vcpkg/packages/grpc_arm64-linux/share/grpc
    ~/vcpkg/packages/utf8-range_arm64-linux/share/utf8_range
    ~/vcpkg/packages/abseil_arm64-linux/share/absl
    ~/vcpkg/packages/c-ares_arm64-linux/share/c-ares
    ~/vcpkg/packages/re2_arm64-linux/share
    ~/vcpkg/packages/protobuf_arm64-linux/share)

find_package(google_cloud_cpp_speech REQUIRED)
find_package(gRPC REQUIRED)

file(GLOB SOURCES "src/*.cpp")

add_library(googlespeechtotext SHARED ${SOURCES})

target_include_directories(googlespeechtotext PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/../include
                           ~/vcpkg/packages/google-cloud-cpp_arm64-linux/include
                           ~/vcpkg/packages/abseil_arm64-linux/include                          
                           ~/vcpkg/packages/grpc_arm64-linux/include
                           ~/vcpkg/packages/protobuf_arm64-linux/include)


target_link_libraries(googlespeechtotext PUBLIC google-cloud-cpp::speech)

install(TARGETS googlespeechtotext DESTINATION ${CMAKE_BINARY_DIR}/../lib)
