/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
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
 *****************************************************************************/

#include "modules/drivers/lidar_velodyne/lidar_velodyne.h"

#include "modules/common/util/file.h"
#include "modules/drivers/lidar_velodyne/common/velodyne_gflags.h"

namespace apollo {
namespace drivers {
namespace lidar_velodyne {

using apollo::common::Status;
using apollo::common::ErrorCode;

std::string LidarVelodyne::Name() const { return "LidarVelodyne"; }

Status LidarVelodyne::Init() {
  AINFO << "Lidar velodyne init, starting ...";
  ErrorCode err = ErrorCode::DRIVER_ERROR_VELODYNE;
  if (!common::util::GetProtoFromFile(FLAGS_velodyne_conf_file, &conf_)) {
    std::string msg = "Fail to load velodyne conf: " + FLAGS_velodyne_conf_file;
    AERROR << msg;
    return Status(err, msg);
  }

  return Status::OK();
}

Status LidarVelodyne::Start() {
  // start lidar velodyne here
  return Status::OK();
}

void LidarVelodyne::Stop() { AINFO << "Lidar velodyne Stopping ..."; }

}  // namespace lidar_velodyne
}  // namespace drivers
}  // namespace apollo
