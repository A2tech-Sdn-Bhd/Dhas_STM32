/*
 * microros.c
 *
 *  Created on: Sep 18, 2025
 *      Author: ahmed
 */

#include "microros.h"

rclc_support_t support;
rcl_subscription_t subscriber;
rcl_allocator_t allocator;
rcl_node_t node;
rclc_executor_t executor;
geometry_msgs__msg__Twist vel;



rcl_ret_t microros_intitilize(void){

	rmw_uros_set_custom_transport(
			true,
			(void *) &hpcd_USB_OTG_FS,
			cubemx_transport_open,
			cubemx_transport_close,
			cubemx_transport_write,
			cubemx_transport_read);

	rcl_allocator_t freeRTOS_allocator = rcutils_get_zero_initialized_allocator();
	freeRTOS_allocator.allocate = microros_allocate;
	freeRTOS_allocator.deallocate = microros_deallocate;
	freeRTOS_allocator.reallocate = microros_reallocate;
	freeRTOS_allocator.zero_allocate =  microros_zero_allocate;

	rcutils_set_default_allocator(&freeRTOS_allocator);


    allocator = rcl_get_default_allocator();

    //create init_options
//    rcl_ret_t ret = rclc_support_init(&support, 0, NULL, &allocator);

//    return ret;

}


void microros_createnode(void){


    rclc_node_init_default(&node, "Stm32_node", "", &support);
    executor = rclc_executor_get_zero_initialized_executor();
    rclc_executor_init(&executor, &support.context, 2, &allocator);


}



void microros_createsubscribers(void){

	rclc_subscription_init_default(
			&subscriber,
			&node,
			ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg,Twist),
			"/cmd_vel");
	rclc_executor_add_subscription(
	  &executor,
	  &subscriber,
	  &vel,
	  &subscription_callback,
	  ON_NEW_DATA);


}



void microros_createpublishers(void){








}


void microros_spinnode(void){
	rclc_executor_spin_some(&executor, 50 * 1000000);
}





void subscription_callback(){








}
