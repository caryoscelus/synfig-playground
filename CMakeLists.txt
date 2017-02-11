cmake_minimum_required(VERSION 3.1)

project(synfig-playground)

enable_testing()

set(CMAKE_CXX_STANDARD 14)

##
## Deps
##

find_package(synfig REQUIRED)

##
## Modules
##

## TODO: make configurable
## TODO: write some macros

set(MODS_ENABLED
    timecurve
    skeleton
)

## Process selected modules
set(SYNFIG_MODULES_CONTENT "")

message("-- Synfig modules:")
foreach(MOD IN ITEMS ${MODS_ENABLED})
    message("--   ${MOD}")
    set(SYNFIG_MODULES_CONTENT "${SYNFIG_MODULES_CONTENT}\n${MOD}")
    add_subdirectory(${MOD})
endforeach(MOD)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/playground.lst ${SYNFIG_MODULES_CONTENT})

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/playground.lst
    DESTINATION etc/synfig/synfig_modules.cfg.d
)
