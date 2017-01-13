add_library(timecurve MODULE "")

target_sources(timecurve
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/timecurve.cpp"
)

include(FindPkgConfig)
pkg_check_modules(LIB2GEOM REQUIRED 2geom)

target_include_directories(timecurve
    SYSTEM BEFORE PUBLIC
        ${LIB2GEOM_INCLUDE_DIRS}
)
target_link_libraries(timecurve ${LIB2GEOM_LIBRARIES} synfig)

install (
    TARGETS timecurve
    DESTINATION lib/synfig/modules
)
