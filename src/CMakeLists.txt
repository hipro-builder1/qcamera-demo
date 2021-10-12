set (CMAKE_AUTOMOC ON)

add_library (app
  app.h
  app.cxx
  )

target_link_libraries(app
  nseit
  ${Boost_LIBRARIES}
  Qt5::Gui
  Qt5::Core
  Qt5::Widgets
  Qt5::Multimedia
  Qt5::MultimediaWidgets
  )

add_executable (qcamera-demo
  main.cxx
  )

target_link_libraries(qcamera-demo
  nseit
  app
  )
