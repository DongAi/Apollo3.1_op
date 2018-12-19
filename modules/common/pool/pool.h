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

  ElemPtr_ New();

  void PreAllocate() {//todo}

private:
  void Allocate();
  void Recycle();


private:
  ElemCont_ elem_cont_;
  ElemRef_ elem_ref_;
  int alloc_interval_;

};

#define POOLDEF_INST(POOLTYPE) \
  g##POOLTYPE##POOL
#define POOLDEF_DECL(POOLTYPE) \
  extern Pool<POOLTYPE> POOLDEF_INST(POOLTYPE); 
  typedef Pool<POOLTYPE>::ElemPtr_ POOLTYPE##Ptr;
#define POOLDEF_IMPL(POOLTYPE) \
  Pool<POOLTYPE> POOLDEF_INST(POOLTYPE)()
#define POOLDEF_NEW(POOLTYPE) \
  POOLDEF_INST(POOLTYPE).New()

}  // namespace pool
}  // namespace common
}  // namespace apollo

#endif