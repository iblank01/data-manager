cmake_minimum_required(VERSION 3.24)
project(data_managing)

set(CMAKE_CXX_STANDARD 23)

# adding SQLiteCpp for use in this project
set(SQLiteCpp_DIR "${PROJECT_SOURCE_DIR}/../git/SQLiteCpp/build")

# adding main executable for use in this project
add_executable(data_managing main.cpp)

# adding SQLiteCpp for use in this project
find_package(SQLiteCpp REQUIRED)

# linking SQLiteCpp to this project
target_link_libraries(data_managing PRIVATE SQLiteCpp)

