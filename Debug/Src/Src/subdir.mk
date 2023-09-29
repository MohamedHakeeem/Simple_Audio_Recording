################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Src/Audio.c \
../Src/Src/Gpio.c \
../Src/Src/Nvic.c \
../Src/Src/Systick.c \
../Src/Src/flash.c \
../Src/Src/main.c \
../Src/Src/stm32f4xx_it.c \
../Src/Src/syscalls.c \
../Src/Src/sysmem.c \
../Src/Src/system_stm32f4xx.c 

OBJS += \
./Src/Src/Audio.o \
./Src/Src/Gpio.o \
./Src/Src/Nvic.o \
./Src/Src/Systick.o \
./Src/Src/flash.o \
./Src/Src/main.o \
./Src/Src/stm32f4xx_it.o \
./Src/Src/syscalls.o \
./Src/Src/sysmem.o \
./Src/Src/system_stm32f4xx.o 

C_DEPS += \
./Src/Src/Audio.d \
./Src/Src/Gpio.d \
./Src/Src/Nvic.d \
./Src/Src/Systick.d \
./Src/Src/flash.d \
./Src/Src/main.d \
./Src/Src/stm32f4xx_it.d \
./Src/Src/syscalls.d \
./Src/Src/sysmem.d \
./Src/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Src/%.o Src/Src/%.su Src/Src/%.cyclo: ../Src/Src/%.c Src/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401VEHx -DSTM32F401xE -c -I../Inc -I"E:/Embedded System/7-STM 32/My Projects After Training/Ideas Projects/Hand_Free/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/Embedded System/7-STM 32/My Projects After Training/Ideas Projects/Hand_Free/Drivers/Core/Include" -I"E:/Embedded System/7-STM 32/My Projects After Training/Ideas Projects/Hand_Free/Src/Inc" -I"E:/Embedded System/7-STM 32/My Projects After Training/Ideas Projects/Hand_Free/Drivers/Core" -I"E:/Embedded System/7-STM 32/My Projects After Training/Ideas Projects/Hand_Free/Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-Src

clean-Src-2f-Src:
	-$(RM) ./Src/Src/Audio.cyclo ./Src/Src/Audio.d ./Src/Src/Audio.o ./Src/Src/Audio.su ./Src/Src/Gpio.cyclo ./Src/Src/Gpio.d ./Src/Src/Gpio.o ./Src/Src/Gpio.su ./Src/Src/Nvic.cyclo ./Src/Src/Nvic.d ./Src/Src/Nvic.o ./Src/Src/Nvic.su ./Src/Src/Systick.cyclo ./Src/Src/Systick.d ./Src/Src/Systick.o ./Src/Src/Systick.su ./Src/Src/flash.cyclo ./Src/Src/flash.d ./Src/Src/flash.o ./Src/Src/flash.su ./Src/Src/main.cyclo ./Src/Src/main.d ./Src/Src/main.o ./Src/Src/main.su ./Src/Src/stm32f4xx_it.cyclo ./Src/Src/stm32f4xx_it.d ./Src/Src/stm32f4xx_it.o ./Src/Src/stm32f4xx_it.su ./Src/Src/syscalls.cyclo ./Src/Src/syscalls.d ./Src/Src/syscalls.o ./Src/Src/syscalls.su ./Src/Src/sysmem.cyclo ./Src/Src/sysmem.d ./Src/Src/sysmem.o ./Src/Src/sysmem.su ./Src/Src/system_stm32f4xx.cyclo ./Src/Src/system_stm32f4xx.d ./Src/Src/system_stm32f4xx.o ./Src/Src/system_stm32f4xx.su

.PHONY: clean-Src-2f-Src

