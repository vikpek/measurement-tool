################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/gnup/InterfaceGnuplot.cpp \
../src/gnup/Plotter.cpp 

OBJS += \
./src/gnup/InterfaceGnuplot.o \
./src/gnup/Plotter.o 

CPP_DEPS += \
./src/gnup/InterfaceGnuplot.d \
./src/gnup/Plotter.d 


# Each subdirectory must supply rules for building sources it contributes
src/gnup/%.o: ../src/gnup/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


