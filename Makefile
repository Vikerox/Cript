# mingw32-make clean ; mingw32-make
# .\Crpt.exe examples\hello.crpt

exec = Crpt.exe
RM = del /Q /F
sources = $(wildcard src/*.cpp)
objects = $(sources:.cpp=.o)
flags = -g -std=c++2a -Wall -Wextra -Wpedantic -O2

$(exec): $(objects)
	g++ $(objects) $(flags) -o $(exec)

%.o: %.cpp include/%.hpp
	g++ -c $(flags) $< -o $@

clean:
	-$(RM) *.exe *.o src\*.o