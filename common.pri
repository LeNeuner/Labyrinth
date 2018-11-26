PROJECT_ROOT_PATH = $${PWD}/

win32: 	   OS_SUFFIX = win32
linux-g++: OS_SUFFIX = linux
macx:      OS_SUFFIX = macx

CONFIG(debug, debug|release){
	BUILD_FLAG = debug
	LIB_SUFFIX = d
} else {
	BUILD_FLAG = release
}

LIBS_PATH 	= $${PROJECT_ROOT_PATH}/lib.$${OS_SUFFIX}/
BIN_PATH 	= $${PROJECT_ROOT_PATH}/bin/$${BUILD_FLAG}/

BUILD_PATH 	= $${PROJECT_ROOT_PATH}/build/$${BUILD_FLAG}/$${TARGET}/
RCC_DIR 	= $${BUILD_PATH}/rcc/
UI_DIR 		= $${BUILD_PATH}/ui/
MOC_DIR 	= $${BUILD_PATH}/moc/
OBJECTS_DIR     = $${BUILD_PATH}/obj/

LIBS 		+= -L$${LIBS_PATH}/

linux-g++: QMAKE_CXXFLAGS += -std=c++11
