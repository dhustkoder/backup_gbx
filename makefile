
CXX_FLAGS=-std=c++11 -nodefaultlibs -pedantic -pedantic-errors -Wall -Wextra -Werror \
          -O3 -DNDEBUG -flto \
          -fno-exceptions -fno-rtti -fomit-frame-pointer \
          -s -ffunction-sections -fdata-sections -Wl,--gc-sections

CXX_INCLUDE=-IDependencies/Utix/Utix/include
CXX_LINK_LIBS_PATH=
CXX_LINK_LIBS= -lc
FILES=Source/*.cpp

compile:
	$(CXX) $(FILES) $(CXX_LINK_LIBS_PATH) $(CXX_LINK_LIBS) $(CXX_INCLUDE) $(CXX_FLAGS) -ogbx.exe
