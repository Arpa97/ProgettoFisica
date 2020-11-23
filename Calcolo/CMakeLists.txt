cmake_minimum_required(VERSION 3.0.0)
project(TEST VERSION 1.0.1)

set(VERBOSE 1)

# Aggiunta opzioni compilatore
list(APPEND CMAKE_CXX_FLAGS 
    "-std=c++1z" 
)

# Inclusione delle directories principali
include_directories(
    ${PROJECT_SOURCE_DIR}/Classi/Include
    ${PROJECT_SOURCE_DIR}/Librerie/Include
    ${PROJECT_SOURCE_DIR}
)

# Compilazione classi/librerie
set(Classi Vertex CiclicVector WaveFront Fire Fuel Cell Environment)
set(Librerie Rothermel)

add_subdirectory(${PROJECT_SOURCE_DIR}/Librerie)
link_libraries(${Librerie})

add_subdirectory(${PROJECT_SOURCE_DIR}/Classi)

# -------Creazione eseguibile-------

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Main.cxx)

configure_file(${PROJECT_SOURCE_DIR}/File/FuelTypes.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

target_link_libraries(${PROJECT_NAME} 
    ${Classi} 
    ${Librerie}
)
