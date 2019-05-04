#ifndef COMMON_MALLOC_HELPER_H
#define COMMON_MALLOC_HELPER_H

#ifdef TEENSYDUINO

bool IsHeap(const void* mem) {
  extern unsigned long _ebss;
  extern unsigned long _estack;
  if (mem) return false;
  return (uint32_t)mem >= _ebss && (uint32_t)mem <= _estack;
}

#elif defined(PROFFIE_TEST)
bool IsHeap(const void* mem) {
#ifdef __APPLE__
  return false; // leak
#else
  extern uint32_t end[];
  return (void*)mem >= (void*)&end;
#endif
}

#else

bool IsHeap(const void* mem) {
  extern uint32_t __HeapBase[];
  extern uint32_t __StackLimit[];
  return (uint32_t)mem >= (uint32_t)__HeapBase && (uint32_t)mem <= (uint32_t)__StackLimit;
}
#endif

template<class T>
void LSFreeObject(T *memory) {
//  STDOUT.print("FREE ");
//  STDOUT.println((uint32_t)memory, HEX);
  free((void*)memory);
}

template<class T>
void LSFree(T *memory) {
  if (IsHeap(memory)) LSFreeObject((T*)memory);
}

template<class T>
class LSPtr {
public:
  LSPtr() : ptr_(nullptr) {}
  ~LSPtr() { Free(); }
  void Free() { LSFree(ptr_); }

  void operator=(const T* t) {
    Free();
    ptr_ = t;
  }
  const T* get() { return ptr_; }
private:
  const T* ptr_;
};

#endif
