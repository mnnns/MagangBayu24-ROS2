#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"

class Subscriber : public rclcpp::Node {
public:
    Subscriber() : Node("subscriber") {
        subscription_1 = create_subscription<std_msgs::msg::Bool>("topic_1", 10, std::bind(&Subscriber::processMessage1, this, std::placeholders::_1));
        subscription_2 = create_subscription<std_msgs::msg::Bool>("topic_2", 10, std::bind(&Subscriber::processMessage2, this, std::placeholders::_1));
    }

private:
    void processMessage1(const std_msgs::msg::Bool::SharedPtr msg) {
        pub1_value_ = msg->data;
        checkAndPrintResult();
    }

    void processMessage2(const std_msgs::msg::Bool::SharedPtr msg) {
        pub2_value_ = msg->data;
        checkAndPrintResult();
    }

    void checkAndPrintResult() {
        RCLCPP_INFO(this->get_logger(), "pub1 - %s | pub2 - %s → %s",
                    pub1_value_ ? "true" : "false",
                    pub2_value_ ? "true" : "false",
                    (pub1_value_ && pub2_value_) ? "sudah siap nih, gass min!" : "tunggu dulu, kami belum ready!");
    }

    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr subscription_1;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr subscription_2;
    bool pub1_value_;
    bool pub2_value_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Subscriber>());
    rclcpp::shutdown();
    return 0;
}
