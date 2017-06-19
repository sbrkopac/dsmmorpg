################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/map/Node.cpp \
../src/map/Region.cpp \
../src/map/WorldMap.cpp 

OBJS += \
./src/map/Node.o \
./src/map/Region.o \
./src/map/WorldMap.o 

CPP_DEPS += \
./src/map/Node.d \
./src/map/Region.d \
./src/map/WorldMap.d 


# Each subdirectory must supply rules for building sources it contributes
src/map/%.o: ../src/map/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/libxml2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


