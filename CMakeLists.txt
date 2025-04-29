cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("BlackHoleSim")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set SFML install location
set(SFML_DIR "C:/Libraries/SFML-3.0.0/lib/cmake/SFML")

# Tell CMake where Boost is
set(BOOST_ROOT "C:/Libraries/boost_1_88_0")  # or wherever you extracted Boost
set(Boost_NO_SYSTEM_PATHS TRUE)

# Find SFML 3 with correct component names (note the capital letters!)
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)
find_package(Boost REQUIRED)

# Include headers
include_directories(include)

# Add sources
file(GLOB SOURCES
    src/*.cpp
)

add_executable(BlackHoleSim ${SOURCES})

target_include_directories(BlackHoleSim PRIVATE ${Boost_INCLUDE_DIRS})

# Link against SFML's modern imported targets
target_link_libraries(BlackHoleSim
    PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BlackHoleSim PROPERTY CXX_STANDARD 20)
endif()

# List of DLLs you want to copy
set(SFML_DLLS
    "sfml-graphics-3.dll"
    "sfml-graphics-d-3.dll"
    "sfml-window-3.dll"
    "sfml-window-d-3.dll"
    "sfml-system-3.dll"
    "sfml-system-d-3.dll"
)

# Copy each DLL after build
foreach(DLL ${SFML_DLLS})
    add_custom_command(TARGET BlackHoleSim POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_DIR}/../../../bin/${DLL}"
            $<TARGET_FILE_DIR:BlackHoleSim>/${DLL}
    )
endforeach()
