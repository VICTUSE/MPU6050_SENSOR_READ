################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/MPU6050drivers/MPU6050_Driver.c 

OBJS += \
./Drivers/MPU6050drivers/MPU6050_Driver.o 

C_DEPS += \
./Drivers/MPU6050drivers/MPU6050_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/MPU6050drivers/%.o Drivers/MPU6050drivers/%.su Drivers/MPU6050drivers/%.cyclo: ../Drivers/MPU6050drivers/%.c Drivers/MPU6050drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Drivers/MPU6050drivers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-MPU6050drivers

clean-Drivers-2f-MPU6050drivers:
	-$(RM) ./Drivers/MPU6050drivers/MPU6050_Driver.cyclo ./Drivers/MPU6050drivers/MPU6050_Driver.d ./Drivers/MPU6050drivers/MPU6050_Driver.o ./Drivers/MPU6050drivers/MPU6050_Driver.su

.PHONY: clean-Drivers-2f-MPU6050drivers

