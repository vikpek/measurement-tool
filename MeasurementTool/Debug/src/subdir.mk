################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BinaryRunner.cpp \
../src/LogEntry.cpp \
../src/MeasurementTool.cpp \
../src/SQLiteCommunicator.cpp \
../src/StringTransformer.cpp \
../src/Timer.cpp 

OBJS += \
./src/BinaryRunner.o \
./src/LogEntry.o \
./src/MeasurementTool.o \
./src/SQLiteCommunicator.o \
./src/StringTransformer.o \
./src/Timer.o 

CPP_DEPS += \
./src/BinaryRunner.d \
./src/LogEntry.d \
./src/MeasurementTool.d \
./src/SQLiteCommunicator.d \
./src/StringTransformer.d \
./src/Timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


