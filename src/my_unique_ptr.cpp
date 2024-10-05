#include <iostream>
#include <utility>

template <class T>
class UniquePtr {
 public:
  explicit UniquePtr(T* p = nullptr) {
    ptr_ = p;
    std::cout << "explicit constructor" << std::endl;
  }
  ~UniquePtr() {
    delete ptr_;
    std::cout << "deconstructor" << std::endl;
  }
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr(UniquePtr&& rhs) {
    ptr_ = rhs.ptr_;
    rhs.ptr_ = nullptr;
    std::cout << "move constructor" << std::endl;
  }
  UniquePtr& operator=(const UniquePtr&) = delete;
  UniquePtr& operator=(UniquePtr&& rhs) {
    if (this != &rhs) {
      if (ptr_) delete ptr_;
      ptr_ = rhs.ptr_;
      rhs.ptr_ = nullptr;
    }
    std::cout << "move assignment" << std::endl;
    return *this;
  }
  // 解引用
  T& operator*() const { return *ptr_; }
  // ->
  T* operator->() const { return ptr_; }
  // 原始指针
  T* get() const { return ptr_; }
  // returns a pointer to the managed object and releases the ownership
  T* release() {
    T* p = ptr_;
    ptr_ = nullptr;
    return p;
  }
  // 重置指针，管理新的对象
  void reset(T* p) {
    if (ptr_) delete ptr_;
    ptr_ = p;
  }

 private:
  T* ptr_;
};

template <class T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
  return UniquePtr<T>((new T(std::forward<Args>(args)...)));
}

struct Obj {
  int* ptr;
  Obj(int size = 1) { ptr = new int[size]; }
  ~Obj() {
    delete[] ptr;
    // std::cout << "release dynamic memory" << std::endl;
  }
};

int main() {
  UniquePtr<Obj> unique_ptr = make_unique<Obj>();
  // 调用的是移动运算符，make_unique<Obj>(10)返回的是临时对象
  unique_ptr = make_unique<Obj>(10);  
  return 0;
}
