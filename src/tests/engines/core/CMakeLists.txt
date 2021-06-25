FILE(GLOB TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR} test_*.cpp)
ADD_EXECUTABLE(test_coreEngine_basic ${TEST_SRC})
TARGET_LINK_LIBRARIES(test_coreEngine_basic ${Boost_LIBRARIES} SamplingEngine)

ADD_TEST(NAME test_coreEngine_basic WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMMAND test_coreEngine_basic)
