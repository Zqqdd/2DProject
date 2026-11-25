# Configuration Linux uniquement (incluse par CMakeLists.txt sous Linux)

set(GAME_PLATFORM "linux")

# SDL3 : bibliothèque Linux rangée dans third_party, aucune installation nécessaire
add_library(SDL3::SDL3 SHARED IMPORTED)
set_target_properties(SDL3::SDL3 PROPERTIES
    IMPORTED_LOCATION "${SDL3_ROOT}/lib/linux-x64/libSDL3.so.0"
    IMPORTED_SONAME "libSDL3.so.0"
    INTERFACE_INCLUDE_DIRECTORIES "${SDL3_ROOT}/include"
)

# Le jeu cherche libSDL3.so.0 dans son propre dossier
set_target_properties(game PROPERTIES BUILD_RPATH "$ORIGIN" INSTALL_RPATH "$ORIGIN")
