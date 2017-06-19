################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/net/Connection.cpp \
../src/net/ListeningSocket.cpp \
../src/net/Network.cpp \
../src/net/Packet.cpp 

OBJS += \
./src/net/Connection.o \
./src/net/ListeningSocket.o \
./src/net/Network.o \
./src/net/Packet.o 

CPP_DEPS += \
./src/net/Connection.d \
./src/net/ListeningSocket.d \
./src/net/Network.d \
./src/net/Packet.d 


# Each subdirectory must supply rules for building sources it contributes
src/net/%.o: ../src/net/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/libxml2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


