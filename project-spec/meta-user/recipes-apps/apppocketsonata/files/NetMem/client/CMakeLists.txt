ADD_LIBRARY (clientNetMem NetworkMemory.cpp ClientMemoryPage.cpp)
TARGET_LINK_LIBRARIES(clientNetMem apiNetMem)
TARGET_LINK_LIBRARIES(clientNetMem serverNetMem)

IF (WIN32)
	TARGET_LINK_LIBRARIES(clientNetMem Ws2_32.lib)
ELSE(WIN32)
	TARGET_LINK_LIBRARIES(clientNetMem boost_thread)
ENDIF(WIN32)
