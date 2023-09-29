################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f401vehx.s 

OBJS += \
./Startup/startup_stm32f401vehx.o 

S_DEPS += \
./Startup/startup_stm32f401vehx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.s Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"E:/Embedded System/7-STM 32/My Projects After Training/Ideas Projects/Hand_Free/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/Embedded System/7-STM 32/My Projects After Training/Ideas Projects/Hand_Free/Drivers/Core/Include" -I"E:/Embedded System/7-STM 32/My Projects After Training/Ideas Projects/Hand_Free/Src/Inc" -I"E:/Embedded System/7-STM 32/My Projects After Training/Ideas Projects/Hand_Free/Drivers/Core" -I"E:/Embedded System/7-STM 32/My Projects After Training/Ideas Projects/Hand_Free/Drivers" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Startup

clean-Startup:
	-$(RM) ./Startup/startup_stm32f401vehx.d ./Startup/startup_stm32f401vehx.o

.PHONY: clean-Startup

