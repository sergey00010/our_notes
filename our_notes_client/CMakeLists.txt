cmake_minimum_required(VERSION 3.16)

project(our_notes_client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Core Quick Network Sql REQUIRED)

qt_add_executable(appour_notes_client
    main.cpp
)

qt_add_qml_module(appour_notes_client
    URI our_notes_client
    VERSION 1.0
    QML_FILES main.qml
    SOURCES client.h client.cpp
    QML_FILES
    SOURCES noteslistmodel.h noteslistmodel.cpp
    SOURCES notemanager.h notemanager.cpp
    QML_FILES CustomButton.qml
    QML_FILES NoteItem.qml
    SOURCES login.h login.cpp
    SOURCES globalparameters.h globalparameters.cpp
    SOURCES workwithdb.h workwithdb.cpp
    QML_FILES ManageNote.qml
    QML_FILES LoginForm.qml
    QML_FILES ListNotesForm.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appour_notes_client PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appour_notes_client
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appour_notes_client
    PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Network
    Qt6::Sql
)

include(GNUInstallDirs)
install(TARGETS appour_notes_client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
