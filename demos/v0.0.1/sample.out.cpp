#include <memory>

// we'll use this class declaration to demonstrate some syntactic sugars
class MyClass;

// =================
// memory management
// =================

// objects are stored as shared pointers by default
std::shared_ptr<MyClass> myObj; 

// primitive types are *not* stored as pointers by default
int myInt; 

// smart pointer syntax
std::shared_ptr<MyClass> myObj; // 'shr' is optional here since it is the default
std::unique_ptr<MyClass> myObj; 
std::weak_ptr<MyClass> myObj; 

// can also make smart pointers of primitive types - but it is not the default
std::shared_ptr<int> myInt; 

// manual memory management syntax
MyClass myObj; // not a pointer
MyClass * myObj; 
MyClass *const  myObj; 
MyClass **const *const **const  myObj; 

// ==========
// mutability
// ==========

// Zyra has two keywords for managing mutability, 'const' and 'immut'.
// immut refers to the object's mutability, const refers to the pointer's
// mutability.
// the 'immut' keyword cannot be used with the 'mnl' keyword.
const std::shared_ptr<MyClass> myObj; // constant pointer to a mutable object
std::shared_ptr<const MyClass> myObj; // mutable pointer to a constant object
const std::shared_ptr<const MyClass> myObj; // constant pointer to a constant object
