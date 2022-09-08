CC=g++
FILES = src/main.cpp src/point.cpp src/boundary.cpp src/octree.cpp

# note that this uses compiler optimizations
downsampler: $(FILES)
	$(CC) -O $(FILES) -o downsampler