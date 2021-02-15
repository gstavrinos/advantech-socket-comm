#include <ros/ros.h>
#include <advantech_comm.hpp>
#include <roboskel_msgs/StringAndBool.h>

advantech_comm::AdvantechComm *adv_comm;

bool onSrv(roboskel_msgs::StringAndBool::Request& req, const roboskel_msgs::StringAndBool::Response& res) {
    if (req.trigger) {
        // TODO write, read and fill response
    }
    else {
        // TODO write, read and fill response
    }
    return true;
}

bool statusSrv(roboskel_msgs::StringAndBool::Request& req, const roboskel_msgs::StringAndBool::Response& res) {

    // TODO read and fill response
    return true;
}

int main(int argc, char** argv){

    ros::init(argc, argv, "advantech_ros_comm");
    ros::NodeHandle nh;

    std::string devdesc, profpath;
    int output_port, input_port;

    nh.param("advantech_ros_comm/input_port", input_port, 0);
    nh.param("advantech_ros_comm/output_port", output_port, 1);
    nh.param("advantech_ros_comm/device_description", devdesc, std::string("DemoDevice,BID#0"));
    nh.param("advantech_ros_comm/profile_path", profpath, std::string("../../profile/DemoDevice.xml"));
    
    adv_comm = new advantech_comm::AdvantechComm(std::wstring(devdesc.begin(), devdesc.end()).c_str(), std::wstring(profpath.begin(), profpath.end()).c_str(), input_port, output_port);

    ros::ServiceServer srv = nh.advertiseService("advantech_ros_comm/on", onSrv);
    ros::ServiceServer srv2 = nh.advertiseService("advantech_ros_comm/status", statusSrv);

    ros::spin();

    delete adv_comm;

    return 0;
}
