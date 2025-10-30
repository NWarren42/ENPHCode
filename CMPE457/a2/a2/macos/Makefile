# Makefile

LDFLAGS  = -L. -lfftw3 -lglfw -ldl
CXXFLAGS = -g -std=c++11 -stdlib=libc++ -Wall -Wno-write-strings -Wno-parentheses -Wno-unused-variable -Wno-uninitialized -Wno-self-assign -Wno-overloaded-virtual -DMACOS

vpath %.cpp ../src
vpath %.c   ../src/glad/src
vpath %.o   ../obj

OBJS = main.o compute.o canvas.o gpuProgram.o linalg.o strokefont.o fg_stroke.o glad.o texture.o filter.o drawSegs.o lodepng.o

EXEC = conv

CXX = clang++

all:    $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS) 

glad.o: ../src/glad/src/glad.c

clean:
	rm -f  *~ $(EXEC) $(OBJS) Makefile.bak

depend:	
	makedepend -Y ../src/*.h ../src/*.cpp 2> /dev/null
	@echo ""
	@echo "Now edit the Makefile to remove the ../src/ prefix of all of the dependences for the .o files"
	@echo ""

# DO NOT DELETE

canvas.o: ../src/headers.h ../src/glad/include/glad/glad.h
canvas.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
canvas.o: ../src/main.h ../src/compute.h ../src/texture.h
canvas.o: ../src/gpuProgram.h ../src/seq.h ../src/filter.h
canvas.o: ../src/drawSegs.h
compute.o: ../src/headers.h ../src/glad/include/glad/glad.h
compute.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
compute.o: ../src/texture.h ../src/gpuProgram.h ../src/seq.h
compute.o: ../src/filter.h
drawSegs.o: ../src/headers.h ../src/glad/include/glad/glad.h
drawSegs.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
drawSegs.o: ../src/gpuProgram.h ../src/seq.h
fg_stroke.o: ../src/headers.h ../src/glad/include/glad/glad.h
fg_stroke.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
filter.o: ../src/headers.h ../src/glad/include/glad/glad.h
filter.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
gpuProgram.o: ../src/headers.h ../src/glad/include/glad/glad.h
gpuProgram.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
gpuProgram.o: ../src/seq.h
headers.o: ../src/glad/include/glad/glad.h
headers.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
main.o: ../src/headers.h ../src/glad/include/glad/glad.h
main.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
strokefont.o: ../src/headers.h ../src/glad/include/glad/glad.h
strokefont.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
strokefont.o: ../src/gpuProgram.h ../src/seq.h
texture.o: ../src/headers.h ../src/glad/include/glad/glad.h
texture.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
texture.o: ../src/gpuProgram.h ../src/seq.h
canvas.o: ../src/canvas.h ../src/headers.h
canvas.o: ../src/glad/include/glad/glad.h
canvas.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
canvas.o: ../src/main.h ../src/compute.h ../src/texture.h
canvas.o: ../src/gpuProgram.h ../src/seq.h ../src/filter.h
canvas.o: ../src/drawSegs.h ../src/strokefont.h
compute.o: ../src/compute.h ../src/headers.h
compute.o: ../src/glad/include/glad/glad.h
compute.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
compute.o: ../src/texture.h ../src/gpuProgram.h ../src/seq.h
compute.o: ../src/filter.h
drawSegs.o: ../src/headers.h ../src/glad/include/glad/glad.h
drawSegs.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
drawSegs.o: ../src/drawSegs.h ../src/gpuProgram.h ../src/seq.h
fg_stroke.o: ../src/fg_stroke.h ../src/headers.h
fg_stroke.o: ../src/glad/include/glad/glad.h
fg_stroke.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
filter.o: ../src/headers.h ../src/glad/include/glad/glad.h
filter.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
filter.o: ../src/filter.h
gpuProgram.o: ../src/gpuProgram.h ../src/headers.h
gpuProgram.o: ../src/glad/include/glad/glad.h
gpuProgram.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
gpuProgram.o: ../src/seq.h
linalg.o: ../src/linalg.h
lodepng.o: ../src/lodepng.h
main.o: ../src/headers.h ../src/glad/include/glad/glad.h
main.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
main.o: ../src/gpuProgram.h ../src/seq.h ../src/canvas.h ../src/main.h
main.o: ../src/compute.h ../src/texture.h ../src/filter.h
main.o: ../src/drawSegs.h ../src/strokefont.h
strokefont.o: ../src/strokefont.h ../src/headers.h
strokefont.o: ../src/glad/include/glad/glad.h
strokefont.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
strokefont.o: ../src/gpuProgram.h ../src/seq.h ../src/fg_stroke.h
texture.o: ../src/texture.h ../src/headers.h
texture.o: ../src/glad/include/glad/glad.h
texture.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
texture.o: ../src/gpuProgram.h ../src/seq.h ../src/lodepng.h
