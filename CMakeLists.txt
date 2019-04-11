cmake_minimum_required(VERSION 2.8.12)
project(Runnerlinuxcommands)

find_package(ECM 5.12.0 REQUIRED NO_MODULE)
set (CMAKE_MODULE_PATH
     ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_MODULE_PATH}
)


find_package (Qt5 ${QT_MIN_VERSION} REQUIRED CONFIG COMPONENTS Widgets Core Network Quick QuickWidgets)
find_package (KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS I18n Service Runner TextWidgets ConfigWidgets PlasmaQuick)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

set(krunner_linuxcommands_SRCS
    linux_commands.cpp
)

add_library(krunner_linuxcommands MODULE ${krunner_linuxcommands_SRCS})
target_link_libraries(krunner_linuxcommands KF5::Runner Qt5::Widgets Qt5::Network
                      KF5::I18n
                      KF5::Service
                      KF5::ConfigWidgets
                      KF5::Plasma)

#add_dependencies(krunner_linuxcommands)

install(TARGETS krunner_linuxcommands DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-runner-linuxcommands.desktop DESTINATION ${SERVICES_INSTALL_DIR})
