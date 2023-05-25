################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/Source/portable/MemMang/heap_4.c 

OBJS += \
./FreeRTOS/Source/portable/MemMang/heap_4.o 

C_DEPS += \
./FreeRTOS/Source/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/Source/portable/MemMang/%.o FreeRTOS/Source/portable/MemMang/%.su FreeRTOS/Source/portable/MemMang/%.cyclo: ../FreeRTOS/Source/portable/MemMang/%.c FreeRTOS/Source/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"F:/Courses/Emb/C_ARM_NTI/ARM_NTI_enrolled/workspace_ARM/RTOS_NowWeKnowTheDispatcher_lab003/FreeRTOS/Source/include" -I"F:/Courses/Emb/C_ARM_NTI/ARM_NTI_enrolled/workspace_ARM/RTOS_NowWeKnowTheDispatcher_lab003/FreeRTOS" -I"F:/Courses/Emb/C_ARM_NTI/ARM_NTI_enrolled/workspace_ARM/RTOS_NowWeKnowTheDispatcher_lab003/FreeRTOS/Source/portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FreeRTOS-2f-Source-2f-portable-2f-MemMang

clean-FreeRTOS-2f-Source-2f-portable-2f-MemMang:
	-$(RM) ./FreeRTOS/Source/portable/MemMang/heap_4.cyclo ./FreeRTOS/Source/portable/MemMang/heap_4.d ./FreeRTOS/Source/portable/MemMang/heap_4.o ./FreeRTOS/Source/portable/MemMang/heap_4.su

.PHONY: clean-FreeRTOS-2f-Source-2f-portable-2f-MemMang

