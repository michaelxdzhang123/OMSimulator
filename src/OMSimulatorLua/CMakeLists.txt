project(OMSimulatorLua C)

set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib/${HOST_SHORT}:$ORIGIN/")

include_directories(
  ${LUALibrary_INCLUDEDIR}
  ../OMSimulatorLib
)

link_directories(
  ${Boost_LIBRARY_DIRS}
  ${FMILibrary_LIBRARYDIR}
  ${LUALibrary_LIBRARYDIR}
  ${CVODELibrary_LIBRARYDIR}
  ${KINSOLLibrary_LIBRARYDIR}
  ${OMTLMSIMULATORLIB_LIBRARYDIR})

# Shared library version
add_library(OMSimulatorLua STATIC OMSimulatorLua.c)

target_link_libraries(OMSimulatorLua OMSimulatorLib fmilib sundials_kinsol sundials_cvode sundials_nvecserial)
IF(WIN32 AND MSVC)
  target_link_libraries(OMSimulatorLua lua wsock32 ws2_32)
ELSEIF (WIN32 AND MINGW)
  target_link_libraries(OMSimulatorLua lua wsock32 ws2_32 shlwapi)
ELSEIF (APPLE)
  target_link_libraries(OMSimulatorLua lua)
ENDIF ()

install(TARGETS OMSimulatorLua DESTINATION lib/${HOST_SHORT})
