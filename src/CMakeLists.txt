# Создаем библиотеку из lib.cpp
add_library(node node.cpp)
add_library(items items.cpp)

# Указываем, где искать заголовки для этой библиотеки
target_include_directories(node PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_include_directories(items PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Создаем основной исполняемый файл
#add_executable(backpack main_multi.cpp)
add_executable(backpack main.cpp)

# Линкуем библиотеку к исполняемому файлу
target_link_libraries(backpack PRIVATE node)
target_link_libraries(backpack PRIVATE items)