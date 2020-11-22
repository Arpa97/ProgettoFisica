cmake_minimum_required(VERSION 3.0.0)
project(TEST VERSION 1.0.1)

set(VERBOSE 1)

# Aggiunta opzioni compilatore
list(APPEND CMAKE_CXX_FLAGS 
    "-std=c++1z" 
)

# Inclusione delle directories principali
include_directories(
    ${PROJECT_SOURCE_DIR}/Applicazione/Classi/Include
    ${PROJECT_SOURCE_DIR}/Applicazione/Librerie/Include
    /usr/local/include
    ${PROJECT_SOURCE_DIR}/Applicazione
)

# Compilazione classi/librerie
set(Classi Vertex CiclicVector WaveFront Fire Fuel Cell Environnement)
set(Librerie Rothermel)

add_subdirectory(${PROJECT_SOURCE_DIR}/Applicazione/Librerie)

link_libraries(${Librerie})

add_subdirectory(${PROJECT_SOURCE_DIR}/Applicazione/Classi)

# -------Creazione eseguibile-------

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Applicazione/Main.cxx)

# Linking

link_directories(/usr/local/lib)

target_link_libraries(${PROJECT_NAME} 
    ${Classi} 
    ${Librerie}
)
