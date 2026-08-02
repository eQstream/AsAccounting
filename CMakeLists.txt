cmake_minimum_required(VERSION 3.15)
project(AsAccounting VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)

# --- Force dynamic system Qt6 (skip Qt6-static) ---
if(UNIX AND NOT APPLE)
    # Linux: prefer system Qt6 over custom static builds
    if(NOT CMAKE_PREFIX_PATH MATCHES "^/usr(;|$)")
        set(CMAKE_PREFIX_PATH "/usr;${CMAKE_PREFIX_PATH}")
    endif()
elseif(WIN32)
    # Windows/MinGW: don't force any prefix, let user set QT_DIR or use qmake
    # System Qt6 on MSYS2 will be found automatically
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Sql Widgets)

add_executable(asaccounting
    src/main.cpp
    src/domain/Owner.cpp
    src/domain/Spot.cpp
    src/domain/User.cpp
    src/domain/AuthService.cpp
    src/infrastructure/SqliteSpotRepository.cpp
    src/infrastructure/SqliteUserRepository.cpp
    src/application/SpotService.cpp
    src/ui/MainWindow.cpp
    src/ui/SpotDialog.cpp
    src/ui/LoginDialog.cpp
)
target_include_directories(asaccounting PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(asaccounting PRIVATE Qt6::Core Qt6::Sql Qt6::Widgets)

# Windows-specific: encode string literals as UTF-8
if(MINGW)
    target_compile_options(asaccounting PRIVATE -fexec-charset=UTF-8)
endif()

# Optional: link native sqlite3 if not relying solely on Qt's SQLite plugin
# find_package(SQLite3 REQUIRED)
# target_link_libraries(asaccounting PRIVATE SQLite::SQLite3)
