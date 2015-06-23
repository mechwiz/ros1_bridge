// Copyright 2015 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iostream>

// include ROS 1
#include <ros/ros.h>
#include <std_msgs/String.h>

// include ROS 2
#include <rclcpp/rclcpp.hpp>
#include <std_interfaces/msg/string.hpp>


ros::Publisher pub;

void chatterCallback(const std_interfaces::msg::String::ConstSharedPtr & ros2_msg)
{
  std::cout << "I heard: [" << ros2_msg->data << "]" << std::endl;

  std_msgs::String ros1_msg;
  ros1_msg.data = ros2_msg->data;
  std::cout << "Passing along: [" << ros1_msg.data << "]" << std::endl;
  pub.publish(ros1_msg);
}

int main(int argc, char * argv[])
{
  // ROS 1 node and publisher
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  pub = n.advertise<std_msgs::String>("chatter", 10);

  // ROS 2 node and subscriber
  rclcpp::init(argc, argv);
  auto node = rclcpp::node::Node::make_shared("listener");
  auto sub = node->create_subscription<std_interfaces::msg::String>("chatter", 10, chatterCallback);

  rclcpp::spin(node);

  return 0;
}
