FIND_PACKAGE( Boost 1.40 COMPONENTS regex REQUIRED )

include_directories(
        ${Boost_INCLUDE_DIR}
)

set(LIB_SOURCES
        obj_parser.cc
        vertex.cc
        model.cc
        converter.cc
)

set(HEADERS
        ${CONFIG_HEADER}
        obj_data.h
        obj_parser.h
        vertex.h
        model.h
        converter.h
)

add_library(viewer_models_lib STATIC ${LIB_SOURCES} ${HEADERS})

TARGET_LINK_LIBRARIES(viewer_models_lib LINK_PUBLIC ${Boost_LIBRARIES} )
