cmake_minimum_required(VERSION 3.26)
project(classic)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH "D:/software/Qt/6.7.1/mingw_64")
set(CMAKE_AUTOMOC ON)
set(QT_VERSION 6)
#链接必要库文件
set(REQUIRED_LIBS Core Gui Widgets Multimedia Sql AxContainer)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Multimedia Qt6::Sql Qt6::AxContainer)
#查找对应功能包
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

include_directories(page)
set(Login page/Login.cpp)
set(Mysql page/Mysql.cpp)
set(Administrative_page page/Administrative_page.cpp)
set(Purchaser_page page/Purchaser_page.cpp)
set(General_page page/General_page.cpp)

add_executable(classic WIN32 main.cpp
    ${Login}
    ${Mysql}
    ${Administrative_page}
    ${Purchaser_page}
    ${General_page}
)
target_link_libraries(classic ${REQUIRED_LIBS_QUALIFIED})