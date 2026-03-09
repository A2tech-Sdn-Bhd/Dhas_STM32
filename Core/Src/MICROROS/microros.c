/*
 * microros.c
 *
 *  Created on: Sep 18, 2025
 *      Author: ahmed
 */

#include "microros.h"

rclc_support_t support;

rcl_subscription_t vel_subscriber;
rcl_subscription_t control_subscriber;
rcl_subscription_t reset_subscriber;
rcl_subscription_t buzzer_subscriber;

rcl_allocator_t allocator;
rcl_node_t node;
rclc_executor_t executor;
geometry_msgs__msg__Twist vel;
uint8_t vel_heartbeat=0;

dhas_stm32_interfaces__msg__Stm32Encoder ros_encoder;
dhas_stm32_interfaces__msg__Stm32Battery ros_battery;
dhas_stm32_interfaces__msg__Stm32State   ros_status;
dhas_stm32_interfaces__msg__Stm32Safety   ros_safety;
dhas_stm32_interfaces__msg__Stm32Control ros_control_flags;
std_msgs__msg__Bool ros_reset;
std_msgs__msg__Bool ros_buzzer;

rcl_publisher_t encoder_publisher;
rcl_publisher_t safety_publisher;
rcl_publisher_t status_publisher;
rcl_publisher_t battery_publisher;

microros_state_t microros_state = MICROROS_STATE_UNINITIALIZED;



void microros_createsubscribers(void){

	rclc_subscription_init_default(
			&vel_subscriber,
			&node,
			ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg,Twist),
			"/cmd_vel");
	rclc_executor_add_subscription(
	  &executor,
	  &vel_subscriber,
	  &vel,
	  &vel_subscription_callback,
	  ON_NEW_DATA);


	rclc_subscription_init_default(
			&control_subscriber,
			&node,
			ROSIDL_GET_MSG_TYPE_SUPPORT(dhas_stm32_interfaces, msg,Stm32Control),
			"/stm32/flags");
	rclc_executor_add_subscription(
	  &executor,
	  &control_subscriber,
	  &ros_control_flags,
	  &subscription_callback,
	  ON_NEW_DATA);


	rclc_subscription_init_default(
			&reset_subscriber,
			&node,
			ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg,Bool),
			"/stm32/reset");
	rclc_executor_add_subscription(
	  &executor,
	  &reset_subscriber,
	  &ros_reset,
	  &reset_subscription_callback,
	  ON_NEW_DATA);


	rclc_subscription_init_default(
			&buzzer_subscriber,
			&node,
			ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg,Bool),
			"/stm32/buzzer");
	rclc_executor_add_subscription(
	  &executor,
	  &buzzer_subscriber,
	  &ros_buzzer,
	  &subscription_callback,
	  ON_NEW_DATA);



}



void microros_createpublishers(void){

	  rclc_publisher_init_best_effort(
	    &encoder_publisher,
	    &node,
	    ROSIDL_GET_MSG_TYPE_SUPPORT(dhas_stm32_interfaces, msg, Stm32Encoder),
	    "stm32/encoder");

	  dhas_stm32_interfaces__msg__Stm32Encoder__init(&ros_encoder);


	  rclc_publisher_init_best_effort(
	    &battery_publisher,
	    &node,
	    ROSIDL_GET_MSG_TYPE_SUPPORT(dhas_stm32_interfaces, msg, Stm32Battery),
	    "stm32/battery");

	  dhas_stm32_interfaces__msg__Stm32Battery__init(&ros_battery);


	  rclc_publisher_init_best_effort(
	    &status_publisher,
	    &node,
	    ROSIDL_GET_MSG_TYPE_SUPPORT(dhas_stm32_interfaces, msg, Stm32State),
	    "stm32/status");

	  dhas_stm32_interfaces__msg__Stm32State__init(&ros_status);


	  rclc_publisher_init_best_effort(
	    &safety_publisher,
	    &node,
	    ROSIDL_GET_MSG_TYPE_SUPPORT(dhas_stm32_interfaces, msg, Stm32Safety),
		"stm32/safety");

	  dhas_stm32_interfaces__msg__Stm32Safety__init(&ros_safety);



}


void microros_spinnode(void){
	rclc_executor_spin_some(&executor, 50 * 1000000);
}



void vel_subscription_callback(void){

	vel_heartbeat++;
}


void subscription_callback(){








}


void reset_subscription_callback(){



	HAL_NVIC_SystemReset();




}


bool setup_transport(void) {

		rmw_uros_set_custom_transport(
				true,
				(void *) &hpcd_USB_OTG_FS,
				cubemx_transport_open,
				cubemx_transport_close,
				cubemx_transport_write,
				cubemx_transport_read);

    return true; // Add actual validation
}


void microros_cleanup(void) {



    if (microros_state >= MICROROS_STATE_NODE_CREATED) {
        rcl_node_fini(&node);
    }
    if (microros_state >= MICROROS_STATE_AGENT_CONNECTED) {
        rclc_support_fini(&support);

    }
    microros_state = MICROROS_STATE_UNINITIALIZED;
}


bool microros_init(void) {
    rcl_ret_t ret;
    uint8_t attempts = 0;


    // 1. Initialize allocator
    allocator = rcl_get_default_allocator();

    // 2. Setup transport (UART/USB/etc.)
    if (!setup_transport()) {
        return false;
    }
    microros_state = MICROROS_STATE_TRANSPORT_OK;

    // 3. Ping agent with retries
    while (attempts < MICROROS_RETRY_ATTEMPTS) {
        if (rmw_uros_ping_agent(MICROROS_INIT_TIMEOUT_MS, 1) == RMW_RET_OK) {
            microros_state = MICROROS_STATE_AGENT_CONNECTED;
            break;
        }
        attempts++;
    }

    // 4. Initialize support structure
    ret = rclc_support_init(&support, 0, NULL, &allocator);
    if (ret != RCL_RET_OK) {
        return false;
    }

    microros_state = MICROROS_STATE_SUPPORT_INITILIZED;

    // 5. Create node

    ret = rclc_node_init_default(&node, "stm32_node", "", &support);
    if (ret != RCL_RET_OK) {
        rclc_support_fini(&support);
        return false;
    }
    microros_state = MICROROS_STATE_NODE_CREATED;

    // 6. Initialize executor
    ret = rclc_executor_init(&executor, &support.context,
                            4, &allocator);
    if (ret != RCL_RET_OK) {
        rcl_node_fini(&node);
        rclc_support_fini(&support);
        return false;
    }

    microros_state = MICRORS_STATE_EXECUTAR_INITILIZED;
    return true;
}

void microros_recovery(){

	if(rmw_uros_ping_agent(250, 5)){
		microros_state=MICROROS_STATE_ERROR;

		ros_control_flags.auto_mode=0;
		ros_control_flags.ros_manual=0;
		ros_control_flags.safety_override=0;


		while(microros_state !=MICRORS_STATE_EXECUTAR_INITILIZED ){
			microros_cleanup();
			microros_init();
		}

		microros_createsubscribers();
		microros_createpublishers();
		microros_state=MICROROS_STATE_READY;
	}


}


void microros_encoder_publish(){


        x3cator_velocity_fromRPM(&ros_encoder.linear_velocity,&ros_encoder.angular_velocity);

		rcl_publish(&encoder_publisher, &ros_encoder, NULL);

}


void microros_battery_publish(){

    ros_battery.voltage=bmsData.TotalVoltage_V;
    ros_battery.current=bmsData.Current_A;
    ros_battery.capacity=bmsData.Capacity_Ah;

	rcl_publish(&battery_publisher, &ros_battery, NULL);

}


void microros_state_publish(){

	ros_status.current_mode=x3cator_state;
	ros_status.rc_validity=x3cator_RC.validity;
	ros_status.safety_override_state=safety_lidars.override;

	rcl_publish(&status_publisher, &ros_status, NULL);


}


void microros_safety_publish(){

    ros_safety.zone1=safety_lidars.zone1;
    ros_safety.zone2=safety_lidars.zone2;
    ros_safety.zone3=safety_lidars.zone3;
    ros_safety.zone4=safety_lidars.zone4;
    ros_safety.zone5=safety_lidars.zone5;
    ros_safety.zone6=safety_lidars.zone6;

    ros_safety.bumper=x3cator_PCB.safety_bumper;

	rcl_publish(&safety_publisher, &ros_safety, NULL);


}



void microros_vel_heartbeat(void){

	if(vel_heartbeat == 0){
		vel.linear.x=0;
		vel.angular.z=0;
	}

	vel_heartbeat=0;



}











