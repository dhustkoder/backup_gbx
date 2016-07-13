CC=clang
CXX=clang++
CXX_FLAGS=-std=c++11 -pedantic-errors -Wall -Wextra -g -O0
CXX_INCLUDE=-IDependencies/Utix/Utix/include
CXX_LINK_LIBS_PATH=-LDependencies/Utix/build/Debug/lib/
CXX_LINK_LIBS= -lUtix
FILES=Source/*.cpp

compile_objs:
	$(CXX) $(FILES) $(CXX_LINK_LIBS_PATH) $(CXX_LINK_LIBS) $(CXX_INCLUDE) $(CXX_FLAGS) -ogbx.exe
