#include <memory>

class MyClass;

// functions with primitive types - basically no change from C++
int f1(int x); 
int f2(int x, int y, int z); 

// functions of objects and functions returning objects - same rules as 
// variables in terms of memory management and mutability
const std::shared_ptr<const MyClass> f3(std::shared_ptr<MyClass> myObj); 
const std::unique_ptr<const MyClass> f4(std::unique_ptr<MyClass> myObj); 