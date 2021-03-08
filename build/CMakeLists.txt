cmake_minimum_required(VERSION 3.13)  # CMake version check
project(LEF)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set (ROOT_DIR ..)
set(SRC_DIR ${ROOT_DIR}/src)
set(MAIN_DIR ${SRC_DIR}/main)
set(CONNECTION_DIR ${SRC_DIR}/connection)
set(MSG_DIR ${SRC_DIR}/msg)
set(SHARED_DIR ${SRC_DIR}/shared)
set(RECEIVER_DIR ${SRC_DIR}/receiver)
set(DISPATCHER_DIR ${SRC_DIR}/dispatcher)
set(HANDLER_DIR ${SRC_DIR}/handler)
set(CHANNEL_DIR ${SRC_DIR}/channel)
set(SENDER_DIR ${SRC_DIR}/sender)


# Add main.cpp file of project root directory as source file
set(SOURCE_FILES  ${CONNECTION_DIR}/UDPConnectionCustomer.cpp 
                    ${MSG_DIR}/MessageHeader.cpp 
                    ${MSG_DIR}/ConnectToNet_Msg.cpp
                    ${MSG_DIR}/DisconnectFromNet_Msg.cpp
                    ${MSG_DIR}/LeaderAlive_Msg.cpp
                    ${MSG_DIR}/BaseMessage.cpp
                    ${MSG_DIR}/MessageFactory.cpp
                    ${SHARED_DIR}/SharedData.cpp
                    ${RECEIVER_DIR}/Receiver_Thread.cpp
                    ${DISPATCHER_DIR}/Dispatcher_Thread.cpp
                    ${HANDLER_DIR}/ConnectDisconnectMsg_Handler.cpp
                    ${HANDLER_DIR}/LeaderAliveMsg_Handler.cpp
                    ${CHANNEL_DIR}/Channel.cpp
                    ${CHANNEL_DIR}/ChannelDefinition.cpp
                    ${SENDER_DIR}/Sender_Thread.cpp
                    ${MAIN_DIR}/Main_Thread.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(main_example ${MAIN_DIR}/main.cpp ${SOURCE_FILES})

target_include_directories(main_example PUBLIC ${SRC_DIR})
target_link_libraries(main_example PUBLIC pthread)

################################### TESTS #####################################

set (TEST_DIR ${ROOT_DIR}/test)
add_executable(sender ${TEST_DIR}/send_receive/sender.cpp ${SOURCE_FILES})
target_include_directories(sender PUBLIC ${SRC_DIR})
add_executable(receiver ${TEST_DIR}/send_receive/receiver.cpp ${SOURCE_FILES})
target_include_directories(receiver PUBLIC ${SRC_DIR})


###############################################################################