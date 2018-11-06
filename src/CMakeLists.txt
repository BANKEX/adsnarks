add_library(adsnarks STATIC oracle_gadget.cpp oracle_protoboard.cpp)
target_link_libraries(adsnarks ethsnarks_common ethsnarks_jubjub)

add_executable(generator generator.cpp)
target_link_libraries(generator adsnarks)

add_executable(prover prover.cpp)
target_link_libraries(prover adsnarks)

add_executable(verifier verifier.cpp)
target_link_libraries(verifier adsnarks)