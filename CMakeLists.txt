cmake_minimum_required(VERSION 3.24)
project(oscarGame)

set(CMAKE_CXX_STANDARD 17)

# Définir le chemin vers les fichiers de configuration de SDL2
set(SDL2_DIR "C:/libC++/SDL2/cmake")
set(SDL2_TTF_DIR "C:/libC++/SDL2_ttf/cmake")

# Recherche des bibliothèques SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_TTF REQUIRED)

# Inclure les répertoires d'en-tête de SDL2
include_directories(${SDL2_INCLUDE_DIRS})
set(SDL2_TTF_PERSO_INCLUDE_DIR "C:/libC++/SDL2_ttf/include")
include_directories(${SDL2_TTF_PERSO_INCLUDE_DIR})

# Définition des fichiers sources
set(SOURCES src/main.cpp src/Trash.h src/header.h src/Game.cpp src/Game.h src/Trash.cpp src/Rocket.cpp src/Rocket.h)

# Création de l'exécutable
add_executable(oscarGame ${SOURCES})

# Lier les bibliothèques SDL2 à l'exécutable
set(SDL2_TTF_LIBRARY "C:/libC++/SDL2_ttf/lib/x64/SDL2_ttf.lib")
target_link_libraries(oscarGame ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARY})