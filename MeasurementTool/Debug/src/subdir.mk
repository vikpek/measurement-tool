################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BinaryRunner.cpp \
../src/LogEntry.cpp \
../src/Logger.cpp \
../src/MeasurementTool.cpp \
../src/MySqlCommunicator.cpp \
../src/Timer.cpp 

OBJS += \
./src/BinaryRunner.o \
./src/LogEntry.o \
./src/Logger.o \
./src/MeasurementTool.o \
./src/MySqlCommunicator.o \
./src/Timer.o 

CPP_DEPS += \
./src/BinaryRunner.d \
./src/LogEntry.d \
./src/Logger.d \
./src/MeasurementTool.d \
./src/MySqlCommunicator.d \
./src/Timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


