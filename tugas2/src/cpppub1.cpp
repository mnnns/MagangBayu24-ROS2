#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"

class Publisher1 : public rclcpp::Node {
public:
    Publisher1() : Node("publisher_1"), count_(0) {
        publisher_ = create_publisher<std_msgs::msg::Bool>("topic_1", 10);
        timer_ = create_wall_timer(std::chrono::seconds(2), std::bind(&Publisher1::publishMessage, this));
    }

private:
    void publishMessage() {
        auto message = std_msgs::msg::Bool();
        message.data = (count_ % 2 == 0);
        RCLCPP_INFO(this->get_logger(), "publisher - 1 - (%d sec) → %s", 2, message.data ? "true" : "false");
        publisher_->publish(message);
        ++count_;
    }

    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    int count_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Publisher1>());
    rclcpp::shutdown();
    return 0;
}
