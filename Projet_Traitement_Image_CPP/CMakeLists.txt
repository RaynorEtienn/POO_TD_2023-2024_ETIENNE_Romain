cmake_minimum_required(VERSION 2.8)

project(projet LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(projet_SRC
    image.h
    imageio.h
    filter.h
    parsefile.h
    image1i16.h
    image3ui16.h
    image4ui8.h
    pgmio.h
    ppmio.h
    bmpio.h
    path.h
    resolver.h
    EasyBMP.h
    EasyBMP_DataStructures.h
    EasyBMP_BMP.h
    EasyBMP_VariousBMPutilities.h
    filterrescaling.h
    filtergaussian.h
    filterbilateral.h

    main.cpp
    resolver.cpp
    path.cpp
    parsefile.cpp
    image.cpp
    image1i16.cpp
    image3ui16.cpp
    image4ui8.cpp
    imageio.cpp
    pgmio.cpp
    ppmio.cpp
    bmpio.cpp
    filter.cpp
    EasyBMP.cpp
    filterrescaling.cpp
    filtergaussian.cpp
    filterbilateral.cpp
    )

add_executable(projet ${projet_SRC}
    filterdownscaling.h filterdownscaling.cpp
    filterupscaling.h filterupscaling.cpp)

#add the PROJECT_DIR macro that is used to define the default path
add_definitions(-DPROJECT_DIR="${PROJECT_SOURCE_DIR}")

#define two build modes: Debug and Release
set(CMAKE_CONFIGURATION_TYPES Debug Release)

#define _DEBUG macro in Debug mode
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    # first for Microsoft Visual C and for the others
    if(MSVC)
      add_definitions(/D_DEBUG)
    else()
      add_definitions(-D_DEBUG)
    endif()

endif()

#turn on all warnings
# first for Microsoft Visual C and for the others
if(MSVC)
  target_compile_options(projet PRIVATE /W4)
else()
  target_compile_options(projet PRIVATE -Wall -Wextra -pedantic)
endif()

#turn on OpenMP
#it is automatic for Microsoft Visual C (MSVC) and other compiler excepted for Xcode on Apple
#for Apple, we have to install libomp
if(MSVC)
else()
  target_compile_options(projet PRIVATE -Wall -Wextra -pedantic)
  if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-gnu-anonymous-struct -Wno-c99-extensions -Wno-nested-anon-types -Wno-deprecated-register -Wno-missing-braces")

    execute_process(COMMAND bash -c "brew --prefix libomp" OUTPUT_VARIABLE LIBOMP_PREFIX)

    if(CMAKE_C_COMPILER_ID MATCHES "Clang\$")
        set(OpenMP_C "${CMAKE_C_COMPILER}" )
        set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp -I/usr/local/opt/libomp/include  -Wno-unused-command-line-argument")
        set(OpenMP_C_LIB_NAMES "omp")
        set(OpenMP_C_LIBRARIES "omp")
        set(OpenMP_omp_LIBRARY "/usr/local/opt/libomp/lib/libomp.a")
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang\$")
        set(OpenMP_CXX "${CMAKE_CXX_COMPILER}" )
        set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp -I/usr/local/opt/libomp/include -Wno-unused-command-line-argument")
        set(OpenMP_CXX_LIB_NAMES "omp")
        set(OpenMP_C_LIBRARIES "omp")
        set(OpenMP_omp_LIBRARY "/usr/local/opt/libomp/lib/libomp.a")
    endif()

  endif()
endif()

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()
