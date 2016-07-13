CXX=clang++
CXX_FLAGS=-std=c++11 -pedantic-errors -Wall -Wextra -g -O2
CXX_INCLUDE=-IDependencies/Utix/Utix/include/
FILES=Source/*.cpp

compile:
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDE) $(FILES) -ogbx.exe
