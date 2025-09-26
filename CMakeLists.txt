cmake_minimum_required(VERSION 3.16)
project(SimpleQMLApp)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置OSG路径（请根据实际安装路径修改）
set(OSG_ROOT "D:/OpenSceneGraph" CACHE PATH "Path to OpenSceneGraph root directory")
set(OSG_BUILD_PATH "${OSG_ROOT}/build")

# 检查OSG路径是否存在
if(NOT EXISTS ${OSG_ROOT})
    message(WARNING "OSG root directory not found: ${OSG_ROOT}")
else()
    message(STATUS "OSG root directory: ${OSG_ROOT}")
endif()

# 添加OSG包含目录
include_directories("${OSG_ROOT}/include")
include_directories("${OSG_BUILD_PATH}/include")

# 添加OSG库目录
link_directories("${OSG_BUILD_PATH}/lib")

# 查找Qt包
find_package(Qt5 REQUIRED COMPONENTS Core Quick Widgets QuickControls2 Qml OpenGL Gui)

# 启用自动moc、rcc和uic处理
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 设置Qt路径（请根据实际安装路径修改）
set(CMAKE_PREFIX_PATH "D:/Qt/5.15.2/msvc2019_64")

# 添加可执行文件
add_executable(${PROJECT_NAME}
    main.cpp
    osgviewer.cpp
    osgviewer.h
    osgviewerrenderer.cpp
    osgviewerrenderer.h
    qml.qrc
)

# 定义OSG库列表（不包含osgQt）
set(OSG_LIBRARIES
    optimized osg debug osgd
    optimized osgViewer debug osgViewerd
    optimized osgManipulator debug osgManipulatord
    optimized osgGA debug osgGAd
    optimized osgDB debug osgDBd
    optimized osgUtil debug osgUtild
    optimized osgText debug osgTextd
    optimized OpenThreads debug OpenThreadsd
)

# 链接Qt库和OSG库到主程序
target_link_libraries(${PROJECT_NAME} 
    Qt5::Core 
    Qt5::Quick 
    Qt5::Widgets
    Qt5::QuickControls2 
    Qt5::Qml
    Qt5::OpenGL
    Qt5::Gui
    ${OSG_LIBRARIES}
    opengl32
)
