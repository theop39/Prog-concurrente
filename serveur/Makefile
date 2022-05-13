ifeq ($(OPT),n)
OPTFLAGS=-O0
else
OPTFLAGS=-Os
endif

ifeq ($(ETU),y)
DEFINES = -DETUDIANTS
endif

compilo-gcc = g++ $(OPTFLAGS) -g -std=c++14 -Wall -W -Werror
compilo-clang = clang++ $(OPTFLAGS) -g -std=c++14 -Weverything -Werror -Wno-zero-as-null-pointer-constant -Wno-c++98-compat -fcaret-diagnostics -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors

executables = $(patsubst %.cpp,%,$(wildcard [a-z]*.cpp))

executables-gcc = $(foreach exe,$(executables),bin-gcc/$(exe))
executables-clang = $(foreach exe,$(executables),bin-clang/$(exe))

headers = $(wildcard *.hpp)
objets = $(patsubst %.cpp,%.o, $(wildcard [A-Z]*.cpp))
objets-gcc = $(foreach obj,$(objets),bin-gcc/$(obj))
objets-clang = $(foreach obj,$(objets),bin-clang/$(obj))

default: $(executables-gcc)

$(executables-gcc): %: %.o $(objets-gcc)
	@make --no-print-directory $(subst bin-gcc,bin-clang,$@)
	$(compilo-gcc) $^ -o $@ -lpthread -lcurses -lboost_thread -lboost_system

$(executables-clang): %: %.o $(objets-clang)
	$(compilo-clang) $^ -o $@ -lpthread -lcurses -lboost_thread -lboost_system

bin-gcc/%.o: %.cpp $(headers)
	@mkdir -p bin-gcc
	@make --no-print-directory $(subst bin-gcc,bin-clang,$@)
	$(compilo-gcc) $(DEFINES) -c $< -o $@

bin-clang/%.o: %.cpp $(headers)
	@mkdir -p bin-clang
	$(compilo-clang) $(DEFINES) -c $< -o $@

menage:
	rm -rf *~ bin* a.out core
