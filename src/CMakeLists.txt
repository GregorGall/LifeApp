set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/forms)

set(PROJECT_INCLUDES ${CMAKE_SOURCE_DIR}/include/View/View.h
                     ${CMAKE_SOURCE_DIR}/include/View/PlayGround.h)
set(PROJECT_FORMES ${CMAKE_SOURCE_DIR}/forms/View.ui)

aux_source_directory(View VIEW_SOURCES)
aux_source_directory(App APP_SOURCES)
aux_source_directory(./ MAIN)

set(PROJECT_SOURCES ${MAIN}
                    ${APP_SOURCES}
                    ${VIEW_SOURCES}
                    ${PROJECT_INCLUDES}
                    ${PROJECT_FORMES} )

add_executable(LifeApp ${PROJECT_SOURCES})

target_include_directories(LifeApp PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(LifeApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
