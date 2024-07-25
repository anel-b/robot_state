# Robot state package in ROS 2 Humble with libfranka library

### Containment of "my_robot_state" package:

**3 Nodes:**
- ee_position.cpp<br>(reads robot state and publishes end effector coordinates)
- talker.cpp<br>(publishes a message as string)
- listener.cpp<br>(subscribes to a message as string)