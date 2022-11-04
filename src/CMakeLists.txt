cmake_minimum_required(VERSION 3.5)


project(database
        VERSION 0.1
        DESCRIPTION "Database Proejct"
        LANGUAGES CXX)

add_executable(databaseBinary main.cpp
                includes/ArrFunctions.hpp
                includes/BPMap.hpp
                includes/BPMultiMap.hpp
                includes/BPTree.hpp
                includes/Matrix.hpp
                includes/MultiPair.hpp
                includes/Pair.hpp
                includes/Parser.hpp
                includes/Queue.hpp
                includes/Record.hpp
                includes/RPN.hpp
                includes/ShuntingYard.hpp
                includes/SQL.hpp
                includes/Stack.hpp
                includes/STokenizer.cpp
                includes/Table.hpp
                includes/Vector.hpp
                includes/SToken/Token.cpp
                includes/SToken/Table.hpp)



target_compile_features(databaseBinary PRIVATE cxx_std_14)


set_target_properties(databaseBinary PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_include_directories(databaseBinary PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)
