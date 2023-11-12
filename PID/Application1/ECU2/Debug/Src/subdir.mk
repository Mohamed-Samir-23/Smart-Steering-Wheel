################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HHBDG_program.c \
../Src/MAFIO_program.c \
../Src/MCAN_program.c \
../Src/MEXTI_program.c \
../Src/MGPIO_program.c \
../Src/MNVIC_program.c \
../Src/MRCC_program.c \
../Src/MSYSTICK_program.c \
../Src/MTIM2_program.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/HHBDG_program.o \
./Src/MAFIO_program.o \
./Src/MCAN_program.o \
./Src/MEXTI_program.o \
./Src/MGPIO_program.o \
./Src/MNVIC_program.o \
./Src/MRCC_program.o \
./Src/MSYSTICK_program.o \
./Src/MTIM2_program.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/HHBDG_program.d \
./Src/MAFIO_program.d \
./Src/MCAN_program.d \
./Src/MEXTI_program.d \
./Src/MGPIO_program.d \
./Src/MNVIC_program.d \
./Src/MRCC_program.d \
./Src/MSYSTICK_program.d \
./Src/MTIM2_program.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/HHBDG_program.cyclo ./Src/HHBDG_program.d ./Src/HHBDG_program.o ./Src/HHBDG_program.su ./Src/MAFIO_program.cyclo ./Src/MAFIO_program.d ./Src/MAFIO_program.o ./Src/MAFIO_program.su ./Src/MCAN_program.cyclo ./Src/MCAN_program.d ./Src/MCAN_program.o ./Src/MCAN_program.su ./Src/MEXTI_program.cyclo ./Src/MEXTI_program.d ./Src/MEXTI_program.o ./Src/MEXTI_program.su ./Src/MGPIO_program.cyclo ./Src/MGPIO_program.d ./Src/MGPIO_program.o ./Src/MGPIO_program.su ./Src/MNVIC_program.cyclo ./Src/MNVIC_program.d ./Src/MNVIC_program.o ./Src/MNVIC_program.su ./Src/MRCC_program.cyclo ./Src/MRCC_program.d ./Src/MRCC_program.o ./Src/MRCC_program.su ./Src/MSYSTICK_program.cyclo ./Src/MSYSTICK_program.d ./Src/MSYSTICK_program.o ./Src/MSYSTICK_program.su ./Src/MTIM2_program.cyclo ./Src/MTIM2_program.d ./Src/MTIM2_program.o ./Src/MTIM2_program.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

