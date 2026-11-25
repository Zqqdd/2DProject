cmake_minimum_required(VERSION 3.50)
project(Sylven LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF) # Pas de modules C++

# ---- Commun à toutes les plateformes ----
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(game ${GAME_SOURCES})
target_include_directories(game PRIVATE src)

set(SDL3_ROOT "${CMAKE_SOURCE_DIR}/third_party/SDL3")

# ---- Spécifique à chaque plateforme (définit la cible SDL3::SDL3) ----
if(WIN32)
    include(cmake/Windows.cmake)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    include(cmake/Linux.cmake)
else()
    message(FATAL_ERROR "Plateforme non supportée : ${CMAKE_SYSTEM_NAME}")
endif()

# ---- Commun à toutes les plateformes ----
# L'exécutable va dans build/<plateforme> ; les fichiers intermédiaires restent dans .build-cache
# ($<0:> empêche Visual Studio d'ajouter un sous-dossier Debug/Release)
set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/${GAME_PLATFORM}/$<0:>")

find_package(OpenGL REQUIRED)
target_link_libraries(game PRIVATE SDL3::SDL3 OpenGL::GL)

# Copie SDL3 et les assets à côté de l'exécutable
add_custom_command(TARGET game POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL3::SDL3> $<TARGET_FILE_DIR:game> VERBATIM)
add_custom_command(TARGET game POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${CMAKE_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:game>/assets" VERBATIM)
