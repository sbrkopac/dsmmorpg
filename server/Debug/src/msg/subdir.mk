################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/msg/WorldMessage.cpp 

OBJS += \
./src/msg/WorldMessage.o 

CPP_DEPS += \
./src/msg/WorldMessage.d 


# Each subdirectory must supply rules for building sources it contributes
src/msg/%.o: ../src/msg/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/libxml2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


