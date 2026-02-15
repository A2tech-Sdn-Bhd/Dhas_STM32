/*
 * microros.h
 *
 *  Created on: Sep 18, 2025
 *      Author: ahmed
 */

#ifndef SRC_MICROROS_MICROROS_H_
#define SRC_MICROROS_MICROROS_H_

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <uxr/client/transport.h>
#include <rmw_microxrcedds_c/config.h>
#include <rmw_microros/rmw_microros.h>

#include <geometry_msgs/msg/twist.h>
#include <std_msgs/msg/bool.h>
#include "usb_device.h"

#include <dhas_stm32_interfaces/msg/stm32_encoder.h>
#include <dhas_stm32_interfaces/msg/stm32_battery.h>
#include <dhas_stm32_interfaces/msg/stm32_state.h>
#include <dhas_stm32_interfaces/msg/stm32_safety.h>
#include <dhas_stm32_interfaces/msg/stm32_control.h>

#define MICROROS_INIT_TIMEOUT_MS 5000
#define MICROROS_RETRY_ATTEMPTS 3
#define MICROROS_RETRY_DELAY_MS 200


typedef enum {
    MICROROS_STATE_UNINITIALIZED,
    MICROROS_STATE_TRANSPORT_OK,
    MICROROS_STATE_AGENT_CONNECTED,
    MICROROS_STATE_NODE_CREATED,
	MICROROS_STATE_SUPPORT_INITILIZED,
	MICRORS_STATE_EXECUTAR_INITILIZED,
    MICROROS_STATE_READY,
    MICROROS_STATE_ERROR
} microros_state_t;

extern microros_state_t microros_state;


bool cubemx_transport_open(struct uxrCustomTransport * transport);
bool cubemx_transport_close(struct uxrCustomTransport * transport);
size_t cubemx_transport_write(struct uxrCustomTransport* transport,  uint8_t * buf, size_t len, uint8_t * err);
size_t cubemx_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err);

void * microros_allocate(size_t size, void * state);
void microros_deallocate(void * pointer, void * state);
void * microros_reallocate(void * pointer, size_t size, void * state);
void * microros_zero_allocate(size_t number_of_elements, size_t size_of_element, void * state);


extern PCD_HandleTypeDef hpcd_USB_OTG_FS;

//declare here and define in source file
extern rclc_support_t support;
extern rcl_subscription_t subscriber;
extern rcl_allocator_t allocator;
extern rcl_node_t node;
extern rclc_executor_t executor;
extern geometry_msgs__msg__Twist vel;
extern rcl_publisher_t encoder_publisher;
extern rcl_publisher_t safety_publisher;
extern rcl_publisher_t status_publisher;
extern rcl_publisher_t battery_publisher;
extern dhas_stm32_interfaces__msg__Stm32Control ros_control_flags;






rcl_ret_t microros_intitilize(void);
void microros_createnode(void);
void microros_createsubscribers(void);
void microros_createpublishers(void);
void microros_spinnode(void);
void subscription_callback();
void reset_subscription_callback();
void microros_cleanup(void);
void microros_recovery(void);

void microros_encoder_publish(void);
void microros_battery_publish(void);
void microros_state_publish(void);
void microros_safety_publish(void);


#endif /* SRC_MICROROS_MICROROS_H_ */
