//=================================================================================================
// Copyright (c) 2012, Johannes Meyer, TU Darmstadt
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Flight Systems and Automatic Control group,
//       TU Darmstadt, nor the names of its contributors may be used to
//       endorse or promote products derived from this software without
//       specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//=================================================================================================

#ifndef HECTOR_GAZEBO_PLUGINS_QUADROTOR_AERODYNAMICS_H
#define HECTOR_GAZEBO_PLUGINS_QUADROTOR_AERODYNAMICS_H

#include <gazebo/common/Plugin.hh>
#include <gazebo/common/Time.hh>
#include <gazebo/math/Vector3.hh>

#include <ros/callback_queue.h>
#include <ros/ros.h>

#include <geometry_msgs/Vector3.h>

#include <boost/thread.hpp>

namespace gazebo
{

class GazeboQuadrotorAerodynamics : public ModelPlugin
{
public:
  GazeboQuadrotorAerodynamics();
  virtual ~GazeboQuadrotorAerodynamics();

protected:
  virtual void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf);
  virtual void Reset();
  virtual void Update();

private:
  /// \brief The parent World
  physics::WorldPtr world;

  /// \brief The link referred to by this plugin
  physics::LinkPtr link;

  ros::NodeHandle* node_handle_;
  ros::CallbackQueue callback_queue_;
  boost::thread callback_queue_thread_;
  void QueueThread();

  ros::Subscriber wind_subscriber_;

  geometry_msgs::Vector3 wind_;
  void WindCallback(const geometry_msgs::Vector3ConstPtr&);

  math::Vector3 velocity, rate;

  std::string body_name_;
  std::string namespace_;
  std::string param_namespace_;
  double control_rate_;
  std::string wind_topic_;

  class DragModel;
  DragModel *drag_model_;

  common::Time last_time_;

  boost::mutex wind_mutex_;

  // Pointer to the update event connection
  event::ConnectionPtr updateConnection;
};

}

#endif // HECTOR_GAZEBO_PLUGINS_QUADROTOR_AERODYNAMICS_H
