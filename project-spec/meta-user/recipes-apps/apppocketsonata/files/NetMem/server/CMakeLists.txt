ADD_EXECUTABLE(NetMem main.cpp ServerSocket.cpp ClientSocket.cpp MemoryPage.cpp)
TARGET_LINK_LIBRARIES(NetMem testUtils)
TARGET_LINK_LIBRARIES(NetMem apiNetMem)

ADD_LIBRARY (serverNetMem ServerSocket.cpp ClientSocket.cpp MemoryPage.cpp)
TARGET_LINK_LIBRARIES(serverNetMem apiNetMem)


IF (WIN32)
	TARGET_LINK_LIBRARIES(NetMem Ws2_32.lib)
	TARGET_LINK_LIBRARIES(serverNetMem Ws2_32.lib)
ELSE(WIN32)
	TARGET_LINK_LIBRARIES(NetMem boost_thread)
	TARGET_LINK_LIBRARIES(serverNetMem boost_thread)
ENDIF(WIN32)
