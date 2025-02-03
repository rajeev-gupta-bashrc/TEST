#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

class CommandPublisher : public rclcpp::Node
{
public:
    CommandPublisher() : Node("command_publisher"), count_(0.0)
    {
        publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/joint_position_controller/commands", 10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(500), 
            std::bind(&CommandPublisher::publish_command, this));
    }

private:
    void publish_command()
    {
        auto message = std_msgs::msg::Float64MultiArray();
        message.data = {count_}; // Sending a single float value in an array
        RCLCPP_INFO(this->get_logger(), "Publishing: [%f]", count_);
        publisher_->publish(message);
        count_ += 1.0; // Incrementing for demonstration purposes
    }

    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    double count_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CommandPublisher>());
    rclcpp::shutdown();
    return 0;
}
