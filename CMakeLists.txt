cmake_minimum_required(VERSION 3.15)
project(AsAccounting VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)

# --------------------------------------------------------------------------
# Поиск Qt6 (динамическая сборка)
# Путь задаётся через CMAKE_PREFIX_PATH при вызове cmake:
#   Windows: cmake -B build -DCMAKE_PREFIX_PATH="C:/msys64/ucrt64"
#   Linux:   cmake -B build
# --------------------------------------------------------------------------
find_package(Qt6 REQUIRED COMPONENTS Core Sql Widgets)

set(SOURCES
    src/main.cpp
    src/Mesto.cpp
    src/database/Database.cpp
    src/ui/MainWindow.cpp
    src/ui/MestoDialog.cpp
)

set(HEADERS
    src/Mesto.h
    src/database/Database.h
    src/ui/MainWindow.h
    src/ui/MestoDialog.h
)

add_executable(asaccounting ${SOURCES} ${HEADERS})
target_include_directories(asaccounting PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(asaccounting PRIVATE Qt6::Core Qt6::Sql Qt6::Widgets)

# --------------------------------------------------------------------------
# Платформозависимые настройки
# --------------------------------------------------------------------------

if(MINGW)
    # Корректная кодировка консольного вывода
    target_compile_options(asaccounting PRIVATE -fexec-charset=UTF-8)

    # Копирование DLL Qt в каталог сборки (Windows)
    add_custom_target(copy_qt_dlls ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:asaccounting>
            $<TARGET_FILE_DIR:asaccounting>
        COMMAND_EXPAND_LISTS
        DEPENDS asaccounting
        COMMENT "Copying Qt DLLs to build directory..."
    )
endif()