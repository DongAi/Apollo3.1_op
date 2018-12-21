/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
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

#ifdef __aarch64__
using namespace apollo::common::math;
using namespace apollo::common::txpool;
using namespace apollo::hdmap;
TXPool<AABoxKDTree2dNode<ObjectWithAABox<LaneInfo, LineSegment2d>>, true, 64> AABoxKDTree2dPool<ObjectWithAABox<LaneInfo, LineSegment2d>>::AABoxKDTree2dNodePool;

TXPool<AABoxKDTree2dNode<ObjectWithAABox<JunctionInfo, Polygon2d>>, true, 64> AABoxKDTree2dPool<ObjectWithAABox<JunctionInfo, Polygon2d>>::AABoxKDTree2dNodePool;

TXPool<AABoxKDTree2dNode<ObjectWithAABox<SignalInfo, LineSegment2d>>, true, 64> AABoxKDTree2dPool<ObjectWithAABox<SignalInfo, LineSegment2d>>::AABoxKDTree2dNodePool;

TXPool<AABoxKDTree2dNode<ObjectWithAABox<CrosswalkInfo, Polygon2d>>, true, 64> AABoxKDTree2dPool<ObjectWithAABox<CrosswalkInfo, Polygon2d>>::AABoxKDTree2dNodePool;

TXPool<AABoxKDTree2dNode<ObjectWithAABox<StopSignInfo, LineSegment2d>>, true, 64> AABoxKDTree2dPool<ObjectWithAABox<StopSignInfo, LineSegment2d>>::AABoxKDTree2dNodePool;

TXPool<AABoxKDTree2dNode<ObjectWithAABox<YieldSignInfo, LineSegment2d>>, true, 64> AABoxKDTree2dPool<ObjectWithAABox<YieldSignInfo, LineSegment2d>>::AABoxKDTree2dNodePool;

TXPool<AABoxKDTree2dNode<ObjectWithAABox<ClearAreaInfo, Polygon2d>>, true, 64> AABoxKDTree2dPool<ObjectWithAABox<ClearAreaInfo, Polygon2d>>::AABoxKDTree2dNodePool;

TXPool<AABoxKDTree2dNode<ObjectWithAABox<SpeedBumpInfo, LineSegment2d>>, true, 64> AABoxKDTree2dPool<ObjectWithAABox<SpeedBumpInfo, LineSegment2d>>::AABoxKDTree2dNodePool;

TXPool<AABoxKDTree2dNode<ObjectWithAABox<ParkingSpaceInfo, Polygon2d>>, true, 64> AABoxKDTree2dPool<ObjectWithAABox<ParkingSpaceInfo, Polygon2d>>::AABoxKDTree2dNodePool;

#endif
