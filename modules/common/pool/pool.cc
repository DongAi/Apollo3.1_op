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

#include "pool.h"

namespace apollo {
namespace common {
namespace pool {

template <typename ElemType_, int AllocInterval_>
Pool<ElemType_, AllocInterval_>::Pool() : 
  alloc_interval_(AllocInterval_) {}

template <typename ElemType_, int AllocInterval_>
Pool<ElemType_, AllocInterval_>::~Pool() {}

template <typename ElemType_, int AllocInterval>
void Pool<ElemType_, AllocInterval>::Allocate() {
  for (int i = 0; i < alloc_interval_; ++i) {
    ElemPtr_ elem_ptr(new ElemType_());
    elem_cont_.push_back(std::make_pair(elem_ptr, true));
    elem_ref_.push_back((int)elem_cont_.size() - 1); 
  }

  size_ = (int)elem_cont_.size();
}

template <typename ElemType_, int AllocInterval>
void Pool<ElemType_,AllocInterval>::Recycle() {
  for (int i = 0; i < size_; ++i) {
    if (elem_cont_[i].first.unique()) {
      //elem_cont_[i].first->ElemType_::~ElemType_();
      //new(elem_cont_[i].first.get()) ElemType_();
      
      elem_ref_.push_back(i);
      elem_cont_[i].second = true;
    }
  }
}

}  //namespace pool
}  //namespace common
}  //namespace pool