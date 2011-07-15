################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/gnuplotplusplus/process.c 

CC_SRCS += \
../src/gnuplotplusplus/gp_base.cc \
../src/gnuplotplusplus/gp_components.cc \
../src/gnuplotplusplus/gp_plot.cc 

OBJS += \
./src/gnuplotplusplus/gp_base.o \
./src/gnuplotplusplus/gp_components.o \
./src/gnuplotplusplus/gp_plot.o \
./src/gnuplotplusplus/process.o 

C_DEPS += \
./src/gnuplotplusplus/process.d 

CC_DEPS += \
./src/gnuplotplusplus/gp_base.d \
./src/gnuplotplusplus/gp_components.d \
./src/gnuplotplusplus/gp_plot.d 


# Each subdirectory must supply rules for building sources it contributes
src/gnuplotplusplus/%.o: ../src/gnuplotplusplus/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/sqlite-autoconf-3070701 -O0 -g3 -Wall -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/gnuplotplusplus/%.o: ../src/gnuplotplusplus/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/local/sqlite-autoconf-3070701 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


