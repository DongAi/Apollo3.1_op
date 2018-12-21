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

#ifndef MODULES_COMMON_POOL_POOL_H
#define MODULES_COMMON_POOL_POOL_H

#include <memory>
#include <vector>
#include <list>
#include <mutex>

namespace apollo {
namespace common {
namespace txpool {

template <typename ElemType_,
            bool PreAllocate_ = true,
            int AllocCount_ = 8>
class TXPool {
public:
  typedef std::shared_ptr<ElemType_> ElemPtr_;
  typedef std::pair<ElemPtr_, int> ElemUnit_;

private:
  typedef std::vector<ElemUnit_> ElemCont_;
  typedef std::list<int> ElemIdle_Cont_;

public:
  enum {
    UNINITALIZED = -1,
    IDLE = 0,
    OCCUPIED = 1,
  };

public:
  TXPool() {
    alloc_count_ = AllocCount_;
    pre_allocate_ = PreAllocate_;
    if (pre_allocate_) {
      PreAllocate();
    }
  }
  ~TXPool() {}

  ElemPtr_ Construct() {
    std::lock_guard<std::mutex> lock(mutex_);
    CheckConstruct();

    const int index = elem_idle_cont_.front();
    elem_idle_cont_.pop_front();
  
    if (elem_cont_[index].second == IDLE)
      elem_cont_[index].first->ElemType_::~ElemType_();
    
    new(elem_cont_[index].first.get()) ElemType_();
    elem_cont_[index].second = OCCUPIED;

    ElemPtr_ elem_ptr = elem_cont_[index].first;
    return elem_ptr;
  }

  #include "txpool_construct.h"

private:
  void PreAllocate() {
    Allocate();
  }

  void CheckConstruct() {
    if (elem_idle_cont_.empty()) {
      Recycle();
    }

    if (elem_idle_cont_.empty()) {
      Allocate();
    }
  }

  void Allocate() {
    for (int i = 0; i < alloc_count_; ++i) {
      ElemPtr_ elem_ptr((ElemType_*)malloc(sizeof(ElemType_)));
      elem_cont_.push_back(std::make_pair(elem_ptr, UNINITALIZED));
      elem_idle_cont_.push_back((int)elem_cont_.size() - 1); 
    }

    size_ = (int)elem_cont_.size();
  }

  void Recycle() {
    for (int i = 0; i < size_; ++i) {
      if (elem_cont_[i].first.unique()) {
      
        elem_idle_cont_.push_back(i);
        elem_cont_[i].second = IDLE;
      }
    }
  }


private:
  ElemCont_ elem_cont_;
  ElemIdle_Cont_ elem_idle_cont_;
  bool pre_allocate_;
  int size_;
  int alloc_count_;
  std::mutex mutex_;
};

#define TXPOOL_INST(TYPE) \
  tx##TYPE##POOL
#define TXPOOL_ALLOC(TYPE) \
  TXPOOL_INST(TYPE).Construct()
#define TXPOOL_DECL(TYPE) \
  extern apollo::common::txpool::TXPool<TYPE> TXPOOL_INST(TYPE); \
  typedef apollo::common::txpool::TXPool<TYPE>::ElemPtr_ TYPE##Ptr;
#define TXPOOL_IMPL(TYPE) \
  apollo::common::txpool::TXPool<TYPE> TXPOOL_INST(TYPE);

}  // namespace pool
}  // namespace common
}  // namespace apollo

#endif // MODULES_COMMON_POOL_POOL_H
#endif // __aarch64__