CC=g++
FILES = src/main.cpp src/point.cpp src/boundary.cpp src/octree.cpp

downsampler: $(FILES)
	$(CC) $(FILES) -o downsampler