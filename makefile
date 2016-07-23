

INCLUDE_DIRS := -I./Dependencies/Utix/Utix/include/
SOURCE_FILES := ./Source/*.cpp
LINK_PATHS := 
LINK_LIBS := -lc
CXX_FLAGS := $(SOURCE_FILES) \
             $(INCLUDE_DIRS) \
             -std=c++11 -pedantic -pedantic-errors -Wall -Wextra -Werror -fno-exceptions -fno-rtti
LINK_FLAGS :=

all: debug

debug: CXX_FLAGS += -D_DEBUG -g -O0
debug: compile

release: CXX_FLAGS += -DNDEBUG -O3 -flto -s -Wl,--gc-sections -fdata-sections -ffunction-sections -fomit-frame-pointer -fno-unwind-tables 
release: LINK_FLAGS +=  -nodefaultlibs -Wl,--gc-sections -flto -s -static-libgcc $(LINK_PATHS) $(LINK_LIBS)
release: compile


compile: compile_objs link clean

link: compile_objs
	$(CXX) -ogbx.exe *.o $(LINK_FLAGS)


compile_objs:
	$(CXX) -c $(CXX_FLAGS)


clean:
	rm -rf *.o

