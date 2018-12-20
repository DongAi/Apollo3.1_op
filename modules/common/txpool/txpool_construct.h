#ifdef __aarch64__

template <typename T0>
ElemPtr_ Construct(T0& t0) {  
  CheckConstruct();

  const int index = elem_ref_.front();
  elem_ref_.pop_front();
 
  if (elem_cont_[index].second == IDLE)
    elem_cont_[index].first->ElemType_::~ElemType_();
    
  new(elem_cont_[index].first.get()) ElemType_(t0);
  elem_cont_[index].second = USED;

  ElemPtr_ elem_ptr = elem_cont_[index].first;
  return elem_ptr;
}

template <typename T0, typename T1>
ElemPtr_ Construct(T0& t0, T1& t1) {  
  CheckConstruct();

  const int index = elem_ref_.front();
  elem_ref_.pop_front();
 
  if (elem_cont_[index].second == IDLE)
    elem_cont_[index].first->ElemType_::~ElemType_();
    
  new(elem_cont_[index].first.get()) ElemType_(t0, t1);
  elem_cont_[index].second = USED;

  ElemPtr_ elem_ptr = elem_cont_[index].first;
  return elem_ptr;
}

template <typename T0, typename T1, typename T2>
ElemPtr_ Construct(T0& t0, T1& t1, T2& t2) {  
  CheckConstruct();

  const int index = elem_ref_.front();
  elem_ref_.pop_front();
 
  if (elem_cont_[index].second == IDLE)
    elem_cont_[index].first->ElemType_::~ElemType_();
    
  new(elem_cont_[index].first.get()) ElemType_(t0, t1, t2);
  elem_cont_[index].second = USED;

  ElemPtr_ elem_ptr = elem_cont_[index].first;
  return elem_ptr;
}

template <typename T0, typename T1, typename T2, typename T3>
ElemPtr_ Construct(T0& t0, T1& t1, T2& t2, T3& t3) {  
  CheckConstruct();

  const int index = elem_ref_.front();
  elem_ref_.pop_front();
 
  if (elem_cont_[index].second == IDLE)
    elem_cont_[index].first->ElemType_::~ElemType_();
    
  new(elem_cont_[index].first.get()) ElemType_(t0, t1, t2, t3);
  elem_cont_[index].second = USED;

  ElemPtr_ elem_ptr = elem_cont_[index].first;
  return elem_ptr;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4>
ElemPtr_ Construct(T0& t0, T1& t1, T2& t2, T3& t3, T4 t4) {  
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

#endif // __aarch64__