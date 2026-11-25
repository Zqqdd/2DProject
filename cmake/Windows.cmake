# Configuration Windows uniquement (incluse par CMakeLists.txt quand WIN32)

set(GAME_PLATFORM "windows")

# Fichiers de debug (.pdb) gardés hors de build/windows
set_target_properties(game PROPERTIES PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/pdb")

# SDL3 : paquet officiel Windows (SDL3-devel-VC) rangé dans third_party/SDL3
set(SDL3_DIR "${SDL3_ROOT}/cmake")
find_package(SDL3 REQUIRED CONFIG)
