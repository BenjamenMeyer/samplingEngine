C_FLAGS=-I../public -I../include
CXX_FLAGS=-I../public -I../include -std=c++0x

all: .o
	ar rcs libsamplingengine.a *.o filters/*.o 

.o: samplingengine.o filters
	make -C filters

samplingengine.o: samplingengine.cpp
	g++ ${CXX_FLAGS} -c samplingengine.cpp -o samplingengine.o


clean:
	-rm *.o *.a
	-make clean -C filters
