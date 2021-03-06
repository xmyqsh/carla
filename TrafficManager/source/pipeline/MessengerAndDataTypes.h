#pragma once

#include <memory>
#include <vector>

#include "carla/client/Actor.h"
#include "carla/Memory.h"
#include "carla/rpc/ActorId.h"

#include "Messenger.h"
#include "SimpleWaypoint.h"

namespace traffic_manager {

namespace cc = carla::client;

  /// Convenience typing.

  /// Alias for waypoint buffer used in the localization stage.
  using Buffer = std::deque<std::shared_ptr<SimpleWaypoint>>;
  /// Alias used for the list of buffers in the localization stage.
  using BufferList = std::vector<Buffer>;

  /// Data types.

  /// Type of data sent by the localization stage to the motion planner stage.
  struct LocalizationToPlannerData {
    carla::SharedPtr<cc::Actor> actor;
    float deviation;
    bool approaching_true_junction;
  };

  /// Type of data sent by the motion planner stage to the batch control stage.
  struct PlannerToControlData {
    carla::ActorId actor_id;
    float throttle;
    float brake;
    float steer;
  };

  /// Type of data sent by the localization stage to the collision stage.
  struct LocalizationToCollisionData {
    carla::SharedPtr<cc::Actor> actor;
    Buffer *buffer;
  };

  /// Type of data sent by the collision stage to the motion planner stage.
  struct CollisionToPlannerData {
    bool hazard;
  };

  /// Type of data sent by the localization stage to the traffic light stage.
  struct LocalizationToTrafficLightData {
    carla::SharedPtr<cc::Actor> actor;
    std::shared_ptr<SimpleWaypoint> closest_waypoint;
    std::shared_ptr<SimpleWaypoint> junction_look_ahead_waypoint;
  };

  /// Type of data sent by the traffic light stage to the motion planner stage.
  struct TrafficLightToPlannerData {
    bool traffic_light_hazard;
  };

  /// Data frame types.

  /// Array types of data flowing between stages.

  using LocalizationToPlannerFrame = std::vector<LocalizationToPlannerData>;
  using PlannerToControlFrame = std::vector<PlannerToControlData>;
  using LocalizationToCollisionFrame = std::vector<LocalizationToCollisionData>;
  using LocalizationToTrafficLightFrame = std::vector<LocalizationToTrafficLightData>;
  using CollisionToPlannerFrame = std::vector<CollisionToPlannerData>;
  using TrafficLightToPlannerFrame = std::vector<TrafficLightToPlannerData>;

  /// Messenger types

  using LocalizationToPlannerMessenger = Messenger<std::shared_ptr<LocalizationToPlannerFrame>>;
  using PlannerToControlMessenger = Messenger<std::shared_ptr<PlannerToControlFrame>>;
  using LocalizationToCollisionMessenger = Messenger<std::shared_ptr<LocalizationToCollisionFrame>>;
  using LocalizationToTrafficLightMessenger = Messenger<std::shared_ptr<LocalizationToTrafficLightFrame>>;
  using CollisionToPlannerMessenger = Messenger<std::shared_ptr<CollisionToPlannerFrame>>;
  using TrafficLightToPlannerMessenger = Messenger<std::shared_ptr<TrafficLightToPlannerFrame>>;
}
