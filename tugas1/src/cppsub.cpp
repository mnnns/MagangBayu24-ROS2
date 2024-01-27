#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class MathSubscriber : public rclcpp::Node {
public:
    MathSubscriber() : Node("math_subscriber") {
        subscription_ = create_subscription<std_msgs::msg::String>("math_problem", 10, std::bind(&MathSubscriber::solveMathProblem, this, std::placeholders::_1));
    }

private:
    void solveMathProblem(const std_msgs::msg::String::SharedPtr msg) {
        std::string mathProblem = msg->data;

        double result = evaluateMathProblem(mathProblem);

        RCLCPP_INFO(this->get_logger(), "%s = %.2lf", mathProblem.c_str(), result);
    }

    double evaluateMathProblem(const std::string &mathProblem) {
        double num1, num2, num3;
        char opr1, opr2;
        sscanf(mathProblem.c_str(), "%lf %c %lf %c %lf", &num1, &opr1, &num2, &opr2, &num3);

        switch (opr1) {
            case '+': return num1 + num2;
            case '-': return num1 - num2;
            case '*': return num1 * num2;
            case '/': return num1 / num2;
            case '%': return fmod(num1, num2);
            default: return 0.0;
        }
    }

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MathSubscriber>());
    rclcpp::shutdown();
    return 0;
}
