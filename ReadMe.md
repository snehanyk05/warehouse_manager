This package serves as a warehouse manager, that assignes tasks to the robots when asked for and generate a report to record the method performance for benchmarking.

Following is the folder structure



Current functionality of `EnvironmentMaster` class:

* Hosts a service called `request_available_task` to assign tasks(goals) to the robot requesting for goals which has (request: <string>name of robot (eg. 0, 1, .., n) response: <float> x , <float> y, <bool> task_available)
* Hosts a service called `report_task_complete` to store the time taken and min_distance to goal by robot which has (request: <string>name of robot (eg. 0, 1, .., n) , <float>time, <float>distance)
* Hosts a service called `gen_final_report` to generate a text file which only has total time taken, total distance travelled and number of collisions (request: <bool> generate_report)

To use Environment Master:
- Setup your local planner to request the task using the above service
- Launch stage, global planner and local planner
- Then run `rosrun warehouse_manager warehouse_master`
