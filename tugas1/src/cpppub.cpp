#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class MathPublisher : public rclcpp::Node {
public:
    MathPublisher() : Node("math_publisher") {
        publisher_ = create_publisher<std_msgs::msg::String>("math_problem", 10);
        timer_ = create_wall_timer(std::chrono::seconds(1), std::bind(&MathPublisher::publishMathProblem, this));
    }

private:
    void publishMathProblem() {
        int num1 = rand() % 10001; // karena 0 - 10000
        int num2 = rand() % 10001;
        int num3 = rand() % 10001;
        char operators[] = {'+', '-', '*', '/', '%'};
        char opr1 = operators[rand() % 5];
        char opr2 = operators[rand() % 5];

        std::string mathProblem = std::to_string(num1) + " " + opr1 + " " + std::to_string(num2) + " " + opr2 + " " + std::to_string(num3);

        auto message = std_msgs::msg::String();
        message.data = mathProblem;
        RCLCPP_INFO(this->get_logger(), "Publishing: %s", message.data.c_str());
        publisher_->publish(message);
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MathPublisher>());
    rclcpp::shutdown();
    return 0;
}
