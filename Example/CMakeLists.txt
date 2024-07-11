project(Example)

add_executable(Example
    ${CMAKE_CURRENT_SOURCE_DIR}/example_impl.cpp
)

target_include_directories(Example PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../ROSE
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/openal/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/libsndfile/include
)

target_link_libraries(Example ROSE OpenAL sndfile)
