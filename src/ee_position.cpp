#include <functional>
#include <memory>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include <franka_msgs/msg/franka_robot_state.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>

using std::placeholders::_1;

class RobotStatePublisher : public rclcpp::Node
{
public:
  RobotStatePublisher() : Node("robot_state_publisher")
  {
    publisher_EE_position = this->create_publisher<std_msgs::msg::Float64MultiArray>("end_effector_position", 1);
    subscription_robot_state = this->create_subscription<franka_msgs::msg::FrankaRobotState>("franka_robot_state_broadcaster/robot_state", 1, std::bind(&RobotStatePublisher::robot_state_callback, this, _1));
  }

private:
  void robot_state_callback(const franka_msgs::msg::FrankaRobotState::SharedPtr msg)
  {
    // Extract end effector position
    geometry_msgs::msg::PoseStamped end_effector_pose_msg = msg->o_t_ee;
    double x = end_effector_pose_msg.pose.position.x;
    double y = end_effector_pose_msg.pose.position.y;
    double z = end_effector_pose_msg.pose.position.z;

    // Publish end effector position as Float64MultiArray message
    auto position_msg = std_msgs::msg::Float64MultiArray();
    position_msg.data = {x, y, z};
    publisher_EE_position->publish(position_msg);

    RCLCPP_INFO(this->get_logger(), "End effector position: [%f, %f, %f]", x, y, z);
  }

  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_EE_position;
  rclcpp::Subscription<franka_msgs::msg::FrankaRobotState>::SharedPtr subscription_robot_state;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RobotStatePublisher>());
  rclcpp::shutdown();
  return 0;
}
