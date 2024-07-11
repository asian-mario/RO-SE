project(ROSE)

add_library(ROSE STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/musicBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/musicBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/soundBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/soundBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/soundDevice.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/soundDevice.h
    ${CMAKE_CURRENT_SOURCE_DIR}/soundSource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/soundSource.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ROSE.h
    
)

target_include_directories(ROSE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ROSE sndfile OpenAL)
