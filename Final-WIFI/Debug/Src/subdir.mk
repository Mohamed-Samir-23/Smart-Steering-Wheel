################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HESP_program.c \
../Src/MGPIO_program.c \
../Src/MNVIC_program.c \
../Src/MRCC_program.c \
../Src/MSYSTICK_program.c \
../Src/MUART_program.c \
../Src/SWIFI_program.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/HESP_program.o \
./Src/MGPIO_program.o \
./Src/MNVIC_program.o \
./Src/MRCC_program.o \
./Src/MSYSTICK_program.o \
./Src/MUART_program.o \
./Src/SWIFI_program.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/HESP_program.d \
./Src/MGPIO_program.d \
./Src/MNVIC_program.d \
./Src/MRCC_program.d \
./Src/MSYSTICK_program.d \
./Src/MUART_program.d \
./Src/SWIFI_program.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/HESP_program.d ./Src/HESP_program.o ./Src/HESP_program.su ./Src/MGPIO_program.d ./Src/MGPIO_program.o ./Src/MGPIO_program.su ./Src/MNVIC_program.d ./Src/MNVIC_program.o ./Src/MNVIC_program.su ./Src/MRCC_program.d ./Src/MRCC_program.o ./Src/MRCC_program.su ./Src/MSYSTICK_program.d ./Src/MSYSTICK_program.o ./Src/MSYSTICK_program.su ./Src/MUART_program.d ./Src/MUART_program.o ./Src/MUART_program.su ./Src/SWIFI_program.d ./Src/SWIFI_program.o ./Src/SWIFI_program.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

