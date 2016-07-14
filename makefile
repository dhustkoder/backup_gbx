CC=clang
CXX=clang++

CXX_FLAGS=-std=c++11 -pedantic -pedantic-errors -Wall -Wextra -Werror \
          -O3 -DNDEBUG \
          -fno-exceptions -fno-rtti -fomit-frame-pointer \
          -s -ffunction-sections -fdata-sections -nodefaultlibs -Wl,--gc-sections \

CXX_INCLUDE=-IDependencies/Utix/Utix/include
CXX_LINK_LIBS_PATH=
CXX_LINK_LIBS= -lc
FILES=Source/*.cpp

compile_objs:
	$(CXX) $(FILES) $(CXX_LINK_LIBS_PATH) $(CXX_LINK_LIBS) $(CXX_INCLUDE) $(CXX_FLAGS) -ogbx.exe
