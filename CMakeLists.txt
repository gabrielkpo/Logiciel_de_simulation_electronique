cmake_minimum_required(VERSION 3.10)
project(be-sim VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Programme principal
add_executable(be-sim 
    main.cpp
    # Ajouter ici vos fichiers sources au fur et à mesure
)

