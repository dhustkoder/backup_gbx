cmake_minimum_required(VERSION 3.5.2)
project(gbx)

set(CMAKE_CXX_FLAGS "-std=c++11 -pedantic -pedantic-errors -Wall -Wextra -Werror -fno-exceptions -fno-rtti")


if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "No build type selected! default to release")
	set(CMAKE_BUILD_TYPE "Release")
endif()


# "Release" full optimization , no debug info.
if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNDEBUG -O3 -g0 -nodefaultlibs -flto -fomit-frame-pointer -ffunction-sections \
	-fdata-sections")

	set(CMAKE_EXE_LINKER_FLAGS "-s -nodefaultlibs -Wl,--gc-sections")

# "Debug" full debug information, no optimization, asserts enabled
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_DEBUG -O0 -g3 -fsanitize=address -fsanitize=undefined")

endif()



file(GLOB_RECURSE SRC ./Source/*.cpp)
include_directories(./Dependencies/Utix/Utix/include/)
add_executable(${PROJECT_NAME} ${SRC})
#link libc
target_link_libraries(${PROJECT_NAME} -lc)
