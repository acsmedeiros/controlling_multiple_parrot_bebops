#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/UInt8.h>
#include <tf/transform_datatypes.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Float64.h>
#include <stdio.h>

#define PI 3.141592653589793238462


int main(int argc, char** argv)
{

  ros::init(argc,argv,"bebop_two_drones");		//Initializing a ROS program


  ros::NodeHandle n;				//Creating a ROS node

  ros::Publisher takeoff_bebop1;			//Sends the message to make the drone take off
  ros::Publisher takeoff_bebop2;			//Sends the message to make the drone take off
  ros::Publisher land_bebop1;			//Sends the message to make the drone land
  ros::Publisher land_bebop2;			//Sends the message to make the drone land
  ros::Publisher cmd_vel_pub_bebop1;		//Sends the message to move the drone
  ros::Publisher cmd_vel_pub_bebop2;		//Sends the message to move the drone


  std_msgs::Empty msg_takeoff, msg_land;		//Messages created to take-off and land procedures
  geometry_msgs::Twist cmd_vel_bebop;		//Contains the data to make the drone fly in certain direction



  takeoff_bebop1 = n.advertise<std_msgs::Empty>("/bebopA/takeoff",1000);					//Publish data to the take-off topic
  takeoff_bebop2 = n.advertise<std_msgs::Empty>("/bebopB/takeoff",1000);					//Publish data to the take-off topic

  land_bebop1 = n.advertise<std_msgs::Empty>("/bebopA/land",1000);						//Publish data to the land topic
  land_bebop2 = n.advertise<std_msgs::Empty>("/bebopB/land",1000);						//Publish data to the land topic

  cmd_vel_pub_bebop1 = n.advertise<geometry_msgs::Twist>("/bebopA/cmd_vel",1000);				//Publish data to the movement topic
  cmd_vel_pub_bebop2 = n.advertise<geometry_msgs::Twist>("/bebopB/cmd_vel",1000);				//Publish data to the movement topic




  //Puts the drone in HOVER setting everything to 0.
  cmd_vel_bebop.linear.x = 0;
  cmd_vel_bebop.linear.y = 0;
  cmd_vel_bebop.linear.z = 0;

  cmd_vel_bebop.angular.x = 0;
  cmd_vel_bebop.angular.y = 0;
  cmd_vel_bebop.angular.z = 0;

  ros::Duration(5).sleep();					//Waits 5 seconds
  printf("\n========== T A K E O F F ==========\n");
  takeoff_bebop1.publish(msg_takeoff);				//Give the order to take-off
  takeoff_bebop2.publish(msg_takeoff);
  ros::Duration(4.5).sleep();					//Waits 4.5 seconds

printf("\n========== G O I N G   U P ==========\n");
  for(int i=0;i<12;i++) //up
  {
      cmd_vel_bebop.linear.x = 0;
      cmd_vel_bebop.linear.y = 0;
      cmd_vel_bebop.linear.z = 0.2;

      cmd_vel_bebop.angular.x = 0;
      cmd_vel_bebop.angular.y = 0;
      cmd_vel_bebop.angular.z = 0;

      cmd_vel_pub_bebop1.publish(cmd_vel_bebop);		//Load the order to hover
      cmd_vel_pub_bebop2.publish(cmd_vel_bebop);		//Load the order to hover
      ros::spinOnce();					//Refresh the topics
      ros::spinOnce();
      ros::Duration(0.1).sleep();				//Stays on hover 0.1 seconds
      ros::spinOnce();
  }

  ros::Duration(2).sleep();				//Stays on hover 2 seconds

printf("\n========== D O W N ==========\n");
  for(int i=0;i<12;i++) // Down
  {
      cmd_vel_bebop.linear.x = 0;
      cmd_vel_bebop.linear.y = 0;
      cmd_vel_bebop.linear.z = -0.2;

      cmd_vel_bebop.angular.x = 0;
      cmd_vel_bebop.angular.y = 0;
      cmd_vel_bebop.angular.z = 0;

      cmd_vel_pub_bebop1.publish(cmd_vel_bebop);		//Load the order to hover
      cmd_vel_pub_bebop2.publish(cmd_vel_bebop);		//Load the order to hover
      ros::spinOnce();					//Refresh the topics
      ros::spinOnce();
      ros::Duration(0.1).sleep();				//Stays on hover 0.1 seconds
      ros::spinOnce();
  }
  ros::Duration(2).sleep();				//Stays on hover 2 seconds

printf("\n========== F O R W A R D ==========\n");
  for(int i=0;i<7;i++) // Front
  {
      cmd_vel_bebop.linear.x = 0.2;
      cmd_vel_bebop.linear.y = 0;
      cmd_vel_bebop.linear.z = 0;

      cmd_vel_bebop.angular.x = 0;
      cmd_vel_bebop.angular.y = 0;
      cmd_vel_bebop.angular.z = 0;

      cmd_vel_pub_bebop1.publish(cmd_vel_bebop);		//Load the order to hover
      cmd_vel_pub_bebop2.publish(cmd_vel_bebop);		//Load the order to hover
      ros::spinOnce();					//Refresh the topics
      ros::spinOnce();
      ros::Duration(0.1).sleep();				//Stays on hover 0.1 seconds
      ros::spinOnce();
  }

  ros::Duration(2).sleep();				//Stays on hover 2 seconds

printf("\n========== B A C K W A R D S ==========\n");
  for(int i=0;i<7;i++) // go back
  {
      cmd_vel_bebop.linear.x = -0.2;
      cmd_vel_bebop.linear.y = 0;
      cmd_vel_bebop.linear.z = 0;

      cmd_vel_bebop.angular.x = 0;
      cmd_vel_bebop.angular.y = 0;
      cmd_vel_bebop.angular.z = 0;

      cmd_vel_pub_bebop1.publish(cmd_vel_bebop);		//Load the order to hover
      cmd_vel_pub_bebop2.publish(cmd_vel_bebop);		//Load the order to hover
      ros::spinOnce();					//Refresh the topics
      ros::spinOnce();
      ros::Duration(0.1).sleep();				//Stays on hover 0.1 seconds
      ros::spinOnce();
  }

  ros::Duration(2).sleep();				//Stays on hover 2 seconds

printf("\n========== G O I N G  L E F T ==========\n");
  for(int i=0;i<7;i++) // go left
  {
      cmd_vel_bebop.linear.x = 0;
      cmd_vel_bebop.linear.y = 0.2;
      cmd_vel_bebop.linear.z = 0;

      cmd_vel_bebop.angular.x = 0;
      cmd_vel_bebop.angular.y = 0;
      cmd_vel_bebop.angular.z = 0;

      cmd_vel_pub_bebop1.publish(cmd_vel_bebop);		//Load the order to hover
      cmd_vel_pub_bebop2.publish(cmd_vel_bebop);		//Load the order to hover
      ros::spinOnce();					//Refresh the topics
      ros::spinOnce();
      ros::Duration(0.1).sleep();				//Stays on hover 0.1 seconds
      ros::spinOnce();
  }

  ros::Duration(2).sleep();				//Stays on hover 2 seconds


printf("\n========== G O I N G  R I G H T ==========\n");
  for(int i=0;i<7;i++) // go right
  {
      cmd_vel_bebop.linear.x = 0;
      cmd_vel_bebop.linear.y = -0.2;
      cmd_vel_bebop.linear.z = 0;

      cmd_vel_bebop.angular.x = 0;
      cmd_vel_bebop.angular.y = 0;
      cmd_vel_bebop.angular.z = 0;

      cmd_vel_pub_bebop1.publish(cmd_vel_bebop);		//Load the order to hover
      cmd_vel_pub_bebop2.publish(cmd_vel_bebop);		//Load the order to hover
      ros::spinOnce();					//Refresh the topics
      ros::spinOnce();
      ros::Duration(0.1).sleep();				//Stays on hover 0.1 seconds
      ros::spinOnce();
  }
  ros::Duration(2).sleep();				//Stays on hover 2 seconds

printf("\n========== R O T A T I N G  L E F T ==========\n");
  for(int i=0;i<10;i++) //rotate left
  {
      cmd_vel_bebop.linear.x = 0;
      cmd_vel_bebop.linear.y = 0;
      cmd_vel_bebop.linear.z = 0;

      cmd_vel_bebop.angular.x = 0;
      cmd_vel_bebop.angular.y = 0;
      cmd_vel_bebop.angular.z = 0.5;

      cmd_vel_pub_bebop1.publish(cmd_vel_bebop);		//Load the order to hover
      cmd_vel_pub_bebop2.publish(cmd_vel_bebop);		//Load the order to hover
      ros::spinOnce();					//Refresh the topics
      ros::spinOnce();
      ros::Duration(0.1).sleep();				//Stays on hover 0.1 seconds
      ros::spinOnce();
  }

   ros::Duration(2).sleep();				//Stays on hover 2 seconds


printf("\n========== R O T A T I N G  R I G H T ==========\n");
  for(int i=0;i<10;i++)  //rotate right
  {
      cmd_vel_bebop.linear.x = 0;
      cmd_vel_bebop.linear.y = 0;
      cmd_vel_bebop.linear.z = 0;

      cmd_vel_bebop.angular.x = 0;
      cmd_vel_bebop.angular.y = 0;
      cmd_vel_bebop.angular.z = -0.5;

      cmd_vel_pub_bebop1.publish(cmd_vel_bebop);		//Load the order to hover
      cmd_vel_pub_bebop2.publish(cmd_vel_bebop);		//Load the order to hover
      ros::spinOnce();					//Refresh the topics
      ros::spinOnce();
      ros::Duration(0.1).sleep();				//Stays on hover 0.1 seconds
      ros::spinOnce();
  }


  ros::Duration(4).sleep();					//Waits 4 seconds

  printf("\n========== L A N D ==========\n");
  land_bebop1.publish(msg_land);					//Give the order to land
  land_bebop2.publish(msg_land);					//Give the order to land

  cmd_vel_pub_bebop1.publish(cmd_vel_bebop);			//Sets the droneA to HOVER
  cmd_vel_pub_bebop2.publish(cmd_vel_bebop);			//Sets the droneB to HOVER
  return 0;



}
