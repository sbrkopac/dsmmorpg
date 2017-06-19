################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AIQuery.cpp \
../src/CurrentTime.cpp \
../src/Engine.cpp \
../src/Log.cpp \
../src/main.cpp 

OBJS += \
./src/AIQuery.o \
./src/CurrentTime.o \
./src/Engine.o \
./src/Log.o \
./src/main.o 

CPP_DEPS += \
./src/AIQuery.d \
./src/CurrentTime.d \
./src/Engine.d \
./src/Log.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/libxml2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


