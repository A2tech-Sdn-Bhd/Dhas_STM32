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
#include <std_msgs/msg/int32.h>
#include <geometry_msgs/msg/twist.h>
#include "usb_device.h"


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




rcl_ret_t microros_intitilize(void);
void microros_createnode(void);
void microros_createsubscribers(void);
void microros_createpublishers(void);
void microros_spinnode(void);
void subscription_callback();


#endif /* SRC_MICROROS_MICROROS_H_ */
