set( APP_NAME show-camera)

add_executable(${APP_NAME} 
  main.cpp
  )

target_link_libraries(${APP_NAME} 
  ${OpenCV_LIBS}  
  ${Boost_LIBRARIES}  
  )
