################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../bpt.cpp \
../create_index.cpp \
../format.cpp \
../linear_hash.cpp \
../storage.cpp \
../table.cpp 

OBJS += \
./bpt.o \
./create_index.o \
./format.o \
./linear_hash.o \
./storage.o \
./table.o 

CPP_DEPS += \
./bpt.d \
./create_index.d \
./format.d \
./linear_hash.d \
./storage.d \
./table.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


