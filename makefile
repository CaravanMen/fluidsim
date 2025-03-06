# Set up source directory
SRCDIR=src

# Set the library directory
LIBDIR=libraries

# Set the header directory
INCDIR=include

# Set the build directory
OUT=build

# Collect source files
CSRC=${wildcard ./${SRCDIR}/*.c}
CXXSRC=${wildcard ./${SRCDIR}/*.cpp}
# Directive files names
OUTFILES=${CXXSRC:./${SRCDIR}/%.cpp=./${OUT}/%.o} ${CSRC:./${SRCDIR}/%.c=${OUT}/%.o}

# Dependency files
DEPENDENCIES=${OUTFILES:./${OUT}/%.o=./{OUT}/%.d}

# Executable name
TARGET=test

# Compiler arguments
CXFLAGS=-L${LIBDIR} -I${INCDIR} -lglfw3 -lGL

default: deps run

${TARGET}: ${OUTFILES}
	@echo "Linking executable $@ from object files $^"
	g++ $^ ${CXFLAGS} -o $@

${OUT}/%.o: ${SRCDIR}/%.cpp
	@echo "Building $@ from $^"
	@mkdir -p ${dir $@}
	g++ -c $^ ${CXFLAGS} -o $@ -MMD
	
${OUT}/%.o: ${SRCDIR}/%.c
	@echo "Building $@ from $^"
	@mkdir -p ${dir $@}
	g++ -c $^ ${CXFLAGS} -o $@ -MMD

-include ${DEPENDENCIES}



# GLFW Stuff
temp/glfw-master:
	@echo "Downloading GLFW from online"
	@mkdir -p ./temp
	@echo "Downloading GLFW library"
	wget https://github.com/glfw/glfw/archive/refs/heads/master.zip -O ./temp/glfw.zip
	unzip ./temp/glfw.zip -d ./temp

${INCDIR}/GLFW/glfw.h: temp/glfw-master/include/GLFW/glfw.h
	cp -dr ./temp/glfw-master/include/GLFW ./${INCDIR}

${INCDIR}/GLFW/glfwnative.h: temp/glfw-master/include/GLFW/glfwnative.h
	cp -dr ./temp/glfw-master/include/GLFW ./${INCDIR}

# Building glfw
${LIBDIR}/libglfw3.a: temp/glfw-master
	@echo "Compiling GLFW library"
	@mkdir -p ./temp/glfw-master/build
	cmake --graphviz=test.dot -S ./temp/glfw-master/ -B ./temp/glfw-master/build -D BUILD_SHARED_LIBS=OFF -D GLFW_BUILD_EXAMPLES=OFF -D GLFW_BUILD_TESTS=OFF -D GLFW_BUILD_DOCS=OFF -D GLFW_LIBRARY_TYPE=STATIC
	dot -Tpng ./test.dot > dependencies.png
	(cd ./temp/glfw-master/build && make)

	@mkdir -p ${LIBDIR}
	cp ./temp/glfw-master/build/src/libglfw3.a ./${LIBDIR}/

# GLAD stuff
temp/glad/include/%.h temp/glad/include/%.c:
	@echo "Uncompressing GLAD compressed archive"
	unzip ./temp/glad.zip -d ./temp/glad

${INCDIR}/KHR/khrplatform.h: temp/glad/include/KHR/khrplatform.h
	@echo "Copying $@ GLAD include file"
	@mkdir -p ${dir $@}
	cp $^ $@

${INCDIR}/glad/glad.h: temp/glad/include/glad/glad.h
	@echo "Copying $@ GLAD include file"
	@mkdir -p ${dir $@}
	cp $^ $@

${SRCDIR}/%.c: temp/glad/src/%.c
	@echo "Copying $@ GLAD loader file"
	@mkdir -p ${dir $@}
	cp $^ $@

# Dependencies download
deps: ${LIBDIR}/libglfw3.a ${INCDIR}/GLFW/glfw3.h ${INCDIR}/GLFW/glfw3native.h ${INCDIR}/glad/glad.h ${INCDIR}/KHR/khrplatform.h ${SRCDIR}/glad.c


# Debug and running
debug | run: ${TARGET}
	@echo "------ DEBUGGING BEGINS HERE ------"
	@./${TARGET}
clean:
	@# @echo "Cleaning temporary files"
	@# # rm -rd ./temp/* -f
	@echo "Cleaning the build files";
	rm -rd ./build/* -f

# Setting up phony targets
.PHONY: clean deps run debug