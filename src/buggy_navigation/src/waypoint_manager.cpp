#include<rclcpp/rclcpp.hpp>
#include<nav_msgs/msg/path.hpp>

class WayPointManager: public rclcpp::Node{
    public:
        WayPointManager():Node ("waypoint_manager"){
            path_publisher_ = this->create_publisher<nav_msgs::msg::Path>("/planning/path",10);
            
            RCLCPP_INFO(this->get_logger(),"waypoint manager started!");
        } 
    private:
            rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_publisher_;

};

int main(int argc , char* argv[]){
    rclcpp::init(argc,argv);

    auto node = std::make_shared<WayPointManager>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}