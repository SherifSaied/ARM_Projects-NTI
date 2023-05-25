################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/Source/portable/GCC/ARM_CM3/port.c 

OBJS += \
./FreeRTOS/Source/portable/GCC/ARM_CM3/port.o 

C_DEPS += \
./FreeRTOS/Source/portable/GCC/ARM_CM3/port.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/Source/portable/GCC/ARM_CM3/%.o FreeRTOS/Source/portable/GCC/ARM_CM3/%.su FreeRTOS/Source/portable/GCC/ARM_CM3/%.cyclo: ../FreeRTOS/Source/portable/GCC/ARM_CM3/%.c FreeRTOS/Source/portable/GCC/ARM_CM3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"F:/Courses/Emb/C_ARM_NTI/ARM_NTI_enrolled/workspace_ARM/RTOS_NowWeKnowTheDispatcher_lab003/FreeRTOS/Source/include" -I"F:/Courses/Emb/C_ARM_NTI/ARM_NTI_enrolled/workspace_ARM/RTOS_NowWeKnowTheDispatcher_lab003/FreeRTOS" -I"F:/Courses/Emb/C_ARM_NTI/ARM_NTI_enrolled/workspace_ARM/RTOS_NowWeKnowTheDispatcher_lab003/FreeRTOS/Source/portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM3

clean-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM3:
	-$(RM) ./FreeRTOS/Source/portable/GCC/ARM_CM3/port.cyclo ./FreeRTOS/Source/portable/GCC/ARM_CM3/port.d ./FreeRTOS/Source/portable/GCC/ARM_CM3/port.o ./FreeRTOS/Source/portable/GCC/ARM_CM3/port.su

.PHONY: clean-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM3

