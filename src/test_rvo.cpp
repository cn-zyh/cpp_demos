#include <iostream>
#include <vector>

struct Obj {
  int a_, b_;
  std::vector<int> data;
  Obj(int a = 0, int b = 0) : a_(a), b_(b) {
    std::cout << "default" << std::endl;
  }
  Obj(Obj& obj) {
    a_ = obj.a_;
    b_ = obj.b_;
    std::cout << "copy" << std::endl;
  }
  Obj(Obj&& obj) {
    a_ = obj.a_;
    b_ = obj.b_;
    std::cout << "move" << std::endl;
  }
  Obj& operator=(Obj& obj) {
    std::cout << "assign" << std::endl;
    return *this;
  }
  Obj& operator=(Obj&& obj) {
    std::cout << "move assign" << std::endl;
    return *this;
  }
};

Obj get() { return Obj(1, 2); }

int main() {
  // case1
  // Obj obj = get();  // 编译器启用了返回值优化(RVO)
  // 只打印一次default

  // case2
  Obj obj; // default
  obj = get(); // get(): default, "=": move assign
  
  return 0;
}
