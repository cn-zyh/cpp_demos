
template <class T>
class SharedPtr {
 public:
  // 含参构造函数，编译器不会生成默认构造函数
  explicit SharedPtr(T* p = nullptr) {
    ptr_ = p;
    if (p == nullptr)
      ref_cnt_ = nullptr;
    else
      ref_cnt_ = new int(1);
  }
  // 析构函数
  ~SharedPtr() {
    if (ref_cnt_ && --(*ref_cnt_) == 0) {
      delete ptr_;
      delete ref_cnt_;
    }
  }
  // 拷贝构造函数
  SharedPtr(const SharedPtr& rhs) {
    ptr_ = rhs.ptr_;
    ref_cnt_ = rhs.ref_cnt_;
    if (ref_cnt_) ++(*ref_cnt_);
  }
  // 移动拷贝构造函数
  SharedPtr(SharedPtr&& rhs) {
    ptr_ = rhs.ptr_;
    ref_cnt_ = rhs.ref_cnt_;
    rhs.ptr_ = nullptr;
    rhs.ref_cnt_ = nullptr;
  }
  // 拷贝赋值运算符
  SharedPtr& operator=(const SharedPtr& rhs) {
    if (this != &rhs) {
      if (ref_cnt_ && --(*ref_cnt_) == 0) {
        delete ptr_;
        delete ref_cnt_;
      }
      ptr_ = rhs.ptr_;
      ref_cnt_ = rhs.ref_cnt_;
      if (ref_cnt_) ++(*ref_cnt_);
    }
    return *this;
  }
  // 移动赋值运算符
  SharedPtr& operator=(SharedPtr&& rhs) {
    if (this != &rhs) {
      if (ref_cnt_ && --(*ref_cnt_) == 0) {
        delete ptr_;
        delete ref_cnt_;
      }
      ptr_ = rhs.ptr_;
      ref_cnt_ = rhs.ref_cnt_;
      rhs.ptr_ = nullptr;
      rhs.ref_cnt_ = nullptr;
    }
    return *this;
  }
  // replaces the managed object
  void reset(T* p = nullptr) {
    if (ref_cnt_ && --(*ref_cnt_) == 0) {
      delete ptr_;
      delete ref_cnt_;
    }
    ptr_ = p;
    ref_cnt_ = (p ? new int(1) : nullptr);
  }

 private:
  T* ptr_;
  int* ref_cnt_;
};

int main() { return 0; }
