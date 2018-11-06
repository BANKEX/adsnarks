cmake_minimum_required(VERSION 3.12)
project(ad_snark)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_subdirectory(depends/ethsnarks)

add_definitions(-DCURVE_${CURVE})

if(${CURVE} STREQUAL "BN128")
    add_definitions(-DBN_SUPPORT_SNARK=1)
endif()

if("${MULTICORE}")
    add_definitions(-DMULTICORE=1)
endif()

if("${DEBUG}" OR "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_definitions(-DDEBUG=1)
endif()


if("${BINARY_OUTPUT}")
    add_definitions(-DBINARY_OUTPUT)
endif()

if("${MONTGOMERY_OUTPUT}")
    add_definitions(-DMONTGOMERY_OUTPUT)
endif()

if(NOT "${USE_PT_COMPRESSION}")
    add_definitions(-DNO_PT_COMPRESSION=1)
endif()


if("${USE_MIXED_ADDITION}")
    add_definitions(-DUSE_MIXED_ADDITION=1)
endif()

if("${CPPDEBUG}")
    add_definitions(-D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC)
endif()

include_directories(
        depends/ethsnarks/src
        depends/ethsnarks/depends/libsnark
        depends/ethsnarks/depends/libsnark/depends/libff
        depends/ethsnarks/depends/libsnark/depends/libfqfft
)


add_subdirectory(src)