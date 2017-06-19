################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/go/Go.cpp \
../src/go/GoActor.cpp \
../src/go/GoAspect.cpp \
../src/go/GoAttack.cpp \
../src/go/GoBody.cpp \
../src/go/GoCommon.cpp \
../src/go/GoComponent.cpp \
../src/go/GoDb.cpp \
../src/go/GoDefend.cpp \
../src/go/GoInventory.cpp \
../src/go/GoMind.cpp \
../src/go/GoPlacement.cpp \
../src/go/GoScriptComponent.cpp 

OBJS += \
./src/go/Go.o \
./src/go/GoActor.o \
./src/go/GoAspect.o \
./src/go/GoAttack.o \
./src/go/GoBody.o \
./src/go/GoCommon.o \
./src/go/GoComponent.o \
./src/go/GoDb.o \
./src/go/GoDefend.o \
./src/go/GoInventory.o \
./src/go/GoMind.o \
./src/go/GoPlacement.o \
./src/go/GoScriptComponent.o 

CPP_DEPS += \
./src/go/Go.d \
./src/go/GoActor.d \
./src/go/GoAspect.d \
./src/go/GoAttack.d \
./src/go/GoBody.d \
./src/go/GoCommon.d \
./src/go/GoComponent.d \
./src/go/GoDb.d \
./src/go/GoDefend.d \
./src/go/GoInventory.d \
./src/go/GoMind.d \
./src/go/GoPlacement.d \
./src/go/GoScriptComponent.d 


# Each subdirectory must supply rules for building sources it contributes
src/go/%.o: ../src/go/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/libxml2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


