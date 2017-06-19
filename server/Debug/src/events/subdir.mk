################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/events/SendWorldMessageEvent.cpp 

OBJS += \
./src/events/SendWorldMessageEvent.o 

CPP_DEPS += \
./src/events/SendWorldMessageEvent.d 


# Each subdirectory must supply rules for building sources it contributes
src/events/%.o: ../src/events/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/libxml2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


