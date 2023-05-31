file(GLOB PROJECT_INCLUDES ${CMAKE_SOURCE_DIR}/include/*/*.h)
file(GLOB PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/*/*.cpp)
file(GLOB PROJECT_FORMES ${CMAKE_SOURCE_DIR}/forms/*.ui)
set(PROJECT_FILES main.cpp ${PROJECT_SOURCES} ${PROJECT_INCLUDES} ${PROJECT_FORMES})

message(${PROJECT_SOURCES})

qt_add_resources(PROJECT_FILES ${PROJECT_SOURCE_DIR}/resource/resource.qrc)
add_executable(LifeApp ${PROJECT_FILES})

target_include_directories(LifeApp PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(LifeApp PRIVATE ${CMAKE_SOURCE_DIR}/lib/LifeLib/include)
target_link_libraries(LifeApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(LifeApp PRIVATE LifeLib)
