/*
 * Software License Agreement (Apache License)
 *
 * Copyright (c) 2016, Southwest Research Institute
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 *  parameterization.h
 *
 *  Created on: March 28, 2016
 *  Author: Jonathan Meyer
 */

#ifndef DESCARTES_PARAMETERIZATION_H
#define DESCARTES_PARAMETERIZATION_H

#include <trajectory_msgs/JointTrajectory.h>
#include "descartes_utilities/spline_interpolator.h"

namespace descartes_utilities
{

/**
 * @brief Given an input trajectory with positions and time_from_start specified,
 *        generates a set of cubic splines that describe the behavior of each 
 *        joint.
 *        
 * @param traj Input trajectory with positions and times specified.  
 * @param splines If successful, this field will be populated with splines for each
 *                joint.
 * @return True on success, false otherwise
 */
bool toCubicSplines(const std::vector<trajectory_msgs::JointTrajectoryPoint>& traj,
                    std::vector<SplineInterpolator>& splines);

/**
 * Calculates velocity and acceleration values for a joint trajectory based on natural cubic splines
 * fit to the input trajectory. This function assumes that the 'positions' field of the trajectory
 * has been filled out for each point and that the degrees of freedom does not change.
 * @param  traj The input trajectory on which to act; assumed to have 'positions' & 'time_from_start'
 *              fields filled out. This function will populate 'velocities' and 'accelerations'.
 * @return      True if the operation succeeded. False otherwise.
 */ 
bool setDerivatesFromSplines(std::vector<trajectory_msgs::JointTrajectoryPoint>& traj);

/**
 * Calculates velocity and acceleration values for a joint trajectory based on natural cubic splines
 * provided by the caller. This function assumes that the 'positions' field of the trajectory
 * has been filled out for each point and that the degrees of freedom does not change.
 * @param  splines Set of splines describing the behaviour of each joint as it moves through the
 *                 input trajectory.
 * @param  traj The input trajectory on which to act; assumed to have 'positions' & 'time_from_start'
 *              fields filled out. This function will populate 'velocities' and 'accelerations'.
 * @return      True if the operation succeeded. False otherwise.
 */
bool setDerivatesFromSplines(const std::vector<SplineInterpolator>& splines,
                             std::vector<trajectory_msgs::JointTrajectoryPoint>& traj);
/**
 * Given a set of splines describing the motion of each joint as it moves through a trajectory,
 * sample this spline at regular intervals to generate a new trajectory.
 * @param  splines  Sequence of splines describing the motion of each joint; 
 *                  perhaps calculated by 'toCubicSplines'
 * @param  start_tm The time value of the trajectory at which to start sampling
 * @param  end_tm   The time value of the trajectory at which to end sampling
 * @param  tm_step  The interval at which to sample times between start & end
 * @param  traj     The new, resampled, output trajectory
 * @return          True on success; If false, 'traj' is untouched.
 */
bool resampleTrajectory(const std::vector<SplineInterpolator>& splines,
                        double start_tm, double end_tm, double tm_step,
                        std::vector<trajectory_msgs::JointTrajectoryPoint>& traj);

}

#endif
