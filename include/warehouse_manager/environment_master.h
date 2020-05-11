#ifndef ENVIRONMENT_MASTER_INCLUDED
#define ENVIRONMENT_MASTER_INCLUDED

#include "ros/ros.h"
#include "warehouse_manager/Robot_Task_Complete.h"
#include "warehouse_manager/Robot_Task_Request.h"
#include "warehouse_manager/Robot_Gen_Report.h"
#include "warehouse_manager/TaskInfo.h"
#include "warehouse_manager/RobotInfo.h"
#include <std_msgs/Int32.h>
#include <iostream>
#include <stdio.h>
#include <tuple>
#include <vector>
#include<queue>

class EnvironmentMaster {
private:
  std::map<int, std::vector<std::tuple<int, int>>> robot_tasks_;
  std::map<int, std::vector<float>> robot_time_;
  std::map<int, std::vector<float>> robot_distance_;
  ros::NodeHandle n_;

public:
  ros::ServiceServer report_task_completion;
  ros::ServiceServer request_available_task;
  ros::ServiceServer request_all_task_complete;
  ros::Subscriber collision_sub;
  
  double begin_;
  double end_;
  int robot_number_;
  int robot_count_;
  int num_collisions_;
  /**
   * @brief Construct a new Environment Master object
   * 
   */
  EnvironmentMaster();
  
  /**
   * @brief Construct a new Environment Master object
   * 
   * @param input nh Node handle 
   */
  EnvironmentMaster(ros::NodeHandle nh) { this->n_ = nh; }

  /**
   * @brief Initialize the environment master with publishers and subscribers
   * 
   * @param input void
   * @param output void
   */
  void init();

  /**
   * @brief Service server to report the task completion (Not used currently)
   * 
   * @param req It contains robot name, time taken and distance covered by the robot
   * @param res Null
   * @return true If service is completed successfully
   * @return false If service is not completed successfully
   */
  bool task_complete(warehouse_manager::Robot_Task_Complete::Request &req,
                     warehouse_manager::Robot_Task_Complete::Response &res);

  /**
   * @brief Service server to assign task to the robot
   * 
   * @param req Name of the robot
   * @param res Goal location for the robot
   * @return true If service is completed successfully
   * @return false If service is not completed successfully
   */
  bool req_task(warehouse_manager::Robot_Task_Request::Request &req,
                     warehouse_manager::Robot_Task_Request::Response &res);

  /**
   * @brief Service server to generate a report, it has to be called when all the tasks are done
   * 
   * @param req boolean which has to be set to true for generating report
   * @param res Null
   * @return true If service is completed successfully
   * @return false If service is not completed successfully
   */
  bool all_task_complete(warehouse_manager::Robot_Gen_Report::Request &req,
                     warehouse_manager::Robot_Gen_Report::Response &res);

  /**
   * @brief Subscriber callback method to update the number of collisions in stage
   * 
   * @param msg Integer with the number of collisiosn
   */
  void collisionCallback(const std_msgs::Int32::ConstPtr& msg);

  /**
   * @brief Method called to generate report for individual robot when they finish their task
   * 
   * @param robot_number Name of the robot that wants to register their task reports
   */
  void add_to_report(int robot_number);

  /**
   * @brief Destroy the Environment Master object
   * 
   */
  ~EnvironmentMaster();
};

#endif
