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

namespace apollo {
namespace common {
namespace pool {

class Ipool {
public:
  Ipool() {}
  ~Ipool() {}

  virtual void Recycle() = 0;

protected:
  int size_;
  int alloc_count_;
};

template <typename ElemType_,
            int AllocInterval_ = 8>
class TXPool : public Ipool {
public:
  typedef std::shared_ptr<ElemType_> ElemPtr_;
  typedef std::pair<ElemPtr_, int> ElemUnit_;

private:
  typedef std::vector<ElemUnit_> ElemCont_;
  typedef std::list<int> ElemRef_;

public:
  enum {
    UNINITALIZED = -1,
    IDLE = 0,
    USED = 1,
  };

public:
  Pool() {
    alloc_count_ = AllocInterval_;
  }
  ~Pool() {}

  ElemPtr_ Construct() {
    CheckConstruct();

    const int index = elem_ref_.front();
    elem_ref_.pop_front();
  
    if (elem_cont_[index].second == IDLE)
      elem_cont_[index].first->ElemType_::~ElemType_();
    
    new(elem_cont_[index].first.get()) ElemType_(t0, t1, t2, t3, t4);
    elem_cont_[index].second = USED;

    ElemPtr_ elem_ptr = elem_cont_[index].first;
    return elem_ptr;
  }

  #include "txpool_construct.h"

  void PreAllocate() {
    //todo
  }

private:
  void CheckConstruct() {
    if (elem_ref_.empty()) {
      Recycle();
    }

    if (elem_ref_.empty()) {
      Allocate();
    }
  }

  void Allocate() {
    for (int i = 0; i < alloc_count_; ++i) {
      //ElemPtr_ elem_ptr(new ElemType_());
      ElemPtr_ elem_ptr((ElemType_*)malloc(sizeof(ElemType_)));
      elem_cont_.push_back(std::make_pair(elem_ptr, UNINITALIZED));
      elem_ref_.push_back((int)elem_cont_.size() - 1); 
    }

    size_ = (int)elem_cont_.size();
  }

  void Recycle() {
    for (int i = 0; i < size_; ++i) {
      if (elem_cont_[i].first.unique()) {
        //elem_cont_[i].first->ElemType_::~ElemType_();
        //new(elem_cont_[i].first.get()) ElemType_();
      
        elem_ref_.push_back(i);
        elem_cont_[i].second = IDLE;
      }
    }
  }


private:
  ElemCont_ elem_cont_;
  ElemRef_ elem_ref_;
};

#define POOLDEF_INST(POOLTYPE) \
  g##POOLTYPE##POOL
#define POOLDEF_DECL(POOLTYPE) \
  extern apollo::common::txpool::TXPool<POOLTYPE> POOLDEF_INST(POOLTYPE); \
  typedef apollo::common::txpool::TXPool<POOLTYPE>::ElemPtr_ POOLTYPE##Ptr;
#define POOLDEF_IMPL(POOLTYPE) \
  apollo::common::txpool::TXPool<POOLTYPE> POOLDEF_INST(POOLTYPE);
#define POOLDEF_NEW(POOLTYPE) \
  POOLDEF_INST(POOLTYPE).Construct()

}  // namespace pool
}  // namespace common
}  // namespace apollo

#endif // MODULES_COMMON_POOL_POOL_H
#endif // __aarch64__