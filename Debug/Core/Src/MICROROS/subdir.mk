################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/MICROROS/custom_memory_manager.c \
../Core/Src/MICROROS/microros.c \
../Core/Src/MICROROS/microros_allocators.c \
../Core/Src/MICROROS/microros_time.c \
../Core/Src/MICROROS/usb_cdc_transport.c 

OBJS += \
./Core/Src/MICROROS/custom_memory_manager.o \
./Core/Src/MICROROS/microros.o \
./Core/Src/MICROROS/microros_allocators.o \
./Core/Src/MICROROS/microros_time.o \
./Core/Src/MICROROS/usb_cdc_transport.o 

C_DEPS += \
./Core/Src/MICROROS/custom_memory_manager.d \
./Core/Src/MICROROS/microros.d \
./Core/Src/MICROROS/microros_allocators.d \
./Core/Src/MICROROS/microros_time.d \
./Core/Src/MICROROS/usb_cdc_transport.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/MICROROS/%.o Core/Src/MICROROS/%.su Core/Src/MICROROS/%.cyclo: ../Core/Src/MICROROS/%.c Core/Src/MICROROS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Core/Src/MAIN -I../Core/Src/MICROROS -I../micro_ros_stm32cubemx_utils/microros_static_library_ide/libmicroros/include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-MICROROS

clean-Core-2f-Src-2f-MICROROS:
	-$(RM) ./Core/Src/MICROROS/custom_memory_manager.cyclo ./Core/Src/MICROROS/custom_memory_manager.d ./Core/Src/MICROROS/custom_memory_manager.o ./Core/Src/MICROROS/custom_memory_manager.su ./Core/Src/MICROROS/microros.cyclo ./Core/Src/MICROROS/microros.d ./Core/Src/MICROROS/microros.o ./Core/Src/MICROROS/microros.su ./Core/Src/MICROROS/microros_allocators.cyclo ./Core/Src/MICROROS/microros_allocators.d ./Core/Src/MICROROS/microros_allocators.o ./Core/Src/MICROROS/microros_allocators.su ./Core/Src/MICROROS/microros_time.cyclo ./Core/Src/MICROROS/microros_time.d ./Core/Src/MICROROS/microros_time.o ./Core/Src/MICROROS/microros_time.su ./Core/Src/MICROROS/usb_cdc_transport.cyclo ./Core/Src/MICROROS/usb_cdc_transport.d ./Core/Src/MICROROS/usb_cdc_transport.o ./Core/Src/MICROROS/usb_cdc_transport.su

.PHONY: clean-Core-2f-Src-2f-MICROROS

