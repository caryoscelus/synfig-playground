add_library(skeleton MODULE "")

target_sources(skeleton
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/skeleton.cpp"
)

target_link_libraries(skeleton synfig)

install (
    TARGETS skeleton
    DESTINATION lib/synfig/modules
)
