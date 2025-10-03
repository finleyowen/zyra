#include <memory>

// we'll use this class declaration to demonstrate some syntactic sugars
class MyClass;

// =================
// memory management
// =================

// objects are stored as shared pointers by default
std::shared_ptr<MyClass> myObj1; 

// primitive types are *not* stored as pointers by default
int myInt1; 

// smart pointer syntax
std::shared_ptr<MyClass> myObj2; // 'shr' is optional here since it is the default
std::unique_ptr<MyClass> myObj3; 
std::weak_ptr<MyClass> myObj4; 

// can also make smart pointers of primitive types - just not by default
std::shared_ptr<int> myInt2; 

// manual memory management syntax
MyClass myObj5; // not a pointer
MyClass * myObj6; 
MyClass *const myObj7; 
MyClass **const*const**const myObj8; 

// ==========
// mutability
// ==========

// Zyra has two keywords for managing mutability, 'const' and 'immut'.
// immut refers to the object's mutability, const refers to the pointer's
// mutability.
// the 'immut' keyword cannot be used with the 'mnl' keyword.
const std::shared_ptr<MyClass> myObj9; // constant pointer to a mutable object
std::shared_ptr<const MyClass> myObj10; // mutable pointer to a constant object
const std::shared_ptr<const MyClass> myObj11; // constant pointer to a constant object
