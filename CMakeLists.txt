cmake_minimum_required(VERSION 3.26)
project(ClientDB)
add_executable(ClientDB main.cpp clientManager.h clientManager.cpp)

add_subdirectory("C:\\Users\\oo43\\source\\libs\\libpqxx-7.7.5" libpqxx-build)

target_compile_features(ClientDB PRIVATE cxx_std_17)

target_link_libraries(ClientDB pqxx)