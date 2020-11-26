foreach(libreria IN LISTS Librerie)

add_library(
    ${libreria} 
    Include/${libreria}.hxx
    src/${libreria}.cxx
)

endforeach()