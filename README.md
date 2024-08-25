# Robot State Package in ROS 2 Humble with franka_ros2

### Package Contents of `my_robot_state`:

**3 Nodes:**
* **ee_position.cpp**  
   * Subscribes to the Franka Emika Research 3 "franka_robot_state_broadcaster/robot_state" topic and publishes the end effector coordinates to the "end_effector_position" ROS 2 topic.
* **talker.cpp**  
   * Publishes a message as a string to a ROS 2 topic.
* **listener.cpp**  
   * Subscribes to a ROS 2 topic and outputs incoming string messages.