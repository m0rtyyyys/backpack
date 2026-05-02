cmake_minimum_required(VERSION 3.15)

# Имя проекта, версия и язык
project(MyProject 
    VERSION 1.0.0 
    LANGUAGES CXX
)

# Настройки стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Рекомендуется выводить исполняемые файлы в отдельную папку
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Добавляем подпапки
add_subdirectory(src)

# Опционально: тесты
option(BUILD_TESTING "Build tests" ON)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()