################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/gnuplotpp/src/process.c 

CC_SRCS += \
../src/gnuplotpp/src/gp_base.cc \
../src/gnuplotpp/src/gp_components.cc \
../src/gnuplotpp/src/gp_plot.cc 

OBJS += \
./src/gnuplotpp/src/gp_base.o \
./src/gnuplotpp/src/gp_components.o \
./src/gnuplotpp/src/gp_plot.o \
./src/gnuplotpp/src/process.o 

C_DEPS += \
./src/gnuplotpp/src/process.d 

CC_DEPS += \
./src/gnuplotpp/src/gp_base.d \
./src/gnuplotpp/src/gp_components.d \
./src/gnuplotpp/src/gp_plot.d 


# Each subdirectory must supply rules for building sources it contributes
src/gnuplotpp/src/%.o: ../src/gnuplotpp/src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/sqlite-autoconf-3070701 -O0 -g3 -Wall -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/gnuplotpp/src/%.o: ../src/gnuplotpp/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/local/sqlite-autoconf-3070701 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


