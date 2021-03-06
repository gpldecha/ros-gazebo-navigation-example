#ifndef SWEEP_PLANNER_H_
#define SWEEP_PLANNER_H_

#include <ros/ros.h>

#include <ros/ros.h>
#include <costmap_2d/costmap_2d_ros.h>
#include <costmap_2d/costmap_2d.h>
#include <nav_core/base_global_planner.h>
#include <geometry_msgs/PoseStamped.h>
#include <angles/angles.h>
#include <base_local_planner/world_model.h>
#include <base_local_planner/costmap_model.h>
#include <armadillo>

#include "visualise/vis_grid.h"

#include "agent/agent.h"

#include <geometry_msgs/Pose2D.h>

using std::string;


namespace global_planner {

class Sweep : public nav_core::BaseGlobalPlanner{

public:

    Sweep();

    Sweep(std::string name, costmap_2d::Costmap2DROS* costmap_ros);

    /** overridden classes from interface nav_core::BaseGlobalPlanner **/
    void initialize(std::string name, costmap_2d::Costmap2DROS* costmap_ros);

    bool makePlan(const geometry_msgs::PoseStamped& start,
                  const geometry_msgs::PoseStamped& goal,
                  std::vector<geometry_msgs::PoseStamped>& plan
                 );

private:

    void    goal_callback(const geometry_msgs::Pose2D::ConstPtr& msg);

    double  footprintCost(double x_i, double y_i, double theta_i);

private:

    double                                  speed;
    double                                  step_size_, min_dist_from_robot_;
    bool                                    initialized_;
    arma::vec2                              current_pos, next_pos, target_pos;

    costmap_2d::Costmap2DROS*               costmap_ros_;
    costmap_2d::Costmap2D*                  costmap_;
    base_local_planner::WorldModel*         world_model_;
    ros::Publisher                          pub;

    //std::shared_ptr<c2t::CostMap2Topology>  costMap2Top_sptr;

    double                                  x_pos_goal;
    double                                  y_pos_goal;
    bool                                    bReceivedGoal;

    ros::NodeHandle                         nh;
    opti_rviz::Vis_gird*                    vis_grid_ptr;
    ros::Subscriber                         sub;






};


}

#endif
