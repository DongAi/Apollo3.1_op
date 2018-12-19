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

private:
  int size_;
  int alloc_count_;
};

template <typename ElemType_,
            int AllocInterval_ = 8>
class Pool : public Ipool {
public:
  typedef std::shared_ptr<ElemType_> ElemPtr_;
  typedef std::pair<ElemPtr_, bool> ElemUnit_;

private:
  typedef std::vector<ElemUnit_> ElemCont_;
  typedef std::list<int> ElemRef_;

public:
  Pool();
  ~Pool();

  template <typename T0, typename T1, typename T2, typename T3, typename T4>
  ElemPtr_ New(T0& t0, T1& t1, T2& t2, T3& t3, T4& t4) {
    if (elem_ref_.empty()) {
      Recycle();
    }

    if (elem_ref_.empty()) {
      Allocate();
    }
  
    const int index = elem_ref_.front();
    elem_ref_.pop_front();
    elem_cont_[index].second = false;

    elem_cont_[index].first->ElemType_::~ElemType_();
    new(elem_cont_[index].first.get()) ElemType_(t0, t1, t2, t3, t4);

    ElemPtr_ elem_ptr = elem_cont_[index].first;
    return elem_ptr;
  }

  void PreAllocate() {
    //todo
  }

private:
  void Allocate() {
    for (int i = 0; i < alloc_interval_; ++i) {
      ElemPtr_ elem_ptr(new ElemType_());
      elem_cont_.push_back(std::make_pair(elem_ptr, true));
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
        elem_cont_[i].second = true;
      }
    }
  }


private:
  ElemCont_ elem_cont_;
  ElemRef_ elem_ref_;
  int alloc_interval_;

};

#define POOLDEF_INST(POOLTYPE) \
  g##POOLTYPE##POOL
#define POOLDEF_DECL(POOLTYPE) \
  extern Pool<POOLTYPE> POOLDEF_INST(POOLTYPE); \
  typedef Pool<POOLTYPE>::ElemPtr_ POOLTYPE##Ptr;
#define POOLDEF_IMPL(POOLTYPE) \
  Pool<POOLTYPE> POOLDEF_INST(POOLTYPE)()
#define POOLDEF_NEW(POOLTYPE) \
  POOLDEF_INST(POOLTYPE).New()

}  // namespace pool
}  // namespace common
}  // namespace apollo

#endif