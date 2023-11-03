################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/APARES.c \
../Src/MFLASH_program.c \
../Src/MGPIO_program.c \
../Src/MRCC_program.c \
../Src/MSYSTICK_program.c \
../Src/USART_program.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/APARES.o \
./Src/MFLASH_program.o \
./Src/MGPIO_program.o \
./Src/MRCC_program.o \
./Src/MSYSTICK_program.o \
./Src/USART_program.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/APARES.d \
./Src/MFLASH_program.d \
./Src/MGPIO_program.d \
./Src/MRCC_program.d \
./Src/MSYSTICK_program.d \
./Src/USART_program.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/APARES.cyclo ./Src/APARES.d ./Src/APARES.o ./Src/APARES.su ./Src/MFLASH_program.cyclo ./Src/MFLASH_program.d ./Src/MFLASH_program.o ./Src/MFLASH_program.su ./Src/MGPIO_program.cyclo ./Src/MGPIO_program.d ./Src/MGPIO_program.o ./Src/MGPIO_program.su ./Src/MRCC_program.cyclo ./Src/MRCC_program.d ./Src/MRCC_program.o ./Src/MRCC_program.su ./Src/MSYSTICK_program.cyclo ./Src/MSYSTICK_program.d ./Src/MSYSTICK_program.o ./Src/MSYSTICK_program.su ./Src/USART_program.cyclo ./Src/USART_program.d ./Src/USART_program.o ./Src/USART_program.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

