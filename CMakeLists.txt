cmake_minimum_required(VERSION 3.24)
project(oscarGame)

set(CMAKE_CXX_STANDARD 17)

# Définir le chemin vers les fichiers de configuration de SDL2
set(SDL2_DIR "C:/libC++/SDL2/cmake")  # Remplacez par le chemin réel de votre installation SDL2

# Recherche de la bibliothèque SDL2
find_package(SDL2 REQUIRED)

# Inclure les répertoires d'en-tête de SDL2
include_directories(${SDL2_INCLUDE_DIRS})

# Définir les fichiers source de votre programme
set(SOURCES src/main.cpp src/Trash.h src/header.h src/Game.cpp src/Game.h src/Trash.cpp src/Rocket.cpp src/Rocket.h)

# Créer l'exécutable
add_executable(oscarGame ${SOURCES})

# Lier les bibliothèques SDL2 à l'exécutable
target_link_libraries(oscarGame ${SDL2_LIBRARIES})