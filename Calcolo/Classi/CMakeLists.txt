foreach(classe IN LISTS Classi)

add_library(
    ${classe} 
    Include/${classe}.hxx
    src/${classe}.cxx
)

link_libraries(${classe})

endforeach()