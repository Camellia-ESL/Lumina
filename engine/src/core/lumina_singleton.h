#pragma once

// A class defined with this macro will be used as a singleton, once instanced there will be only 1 possible instance of it.
// Usage: Define a class passing the class name as follow (es: class LUMINA_SINGLETON_CLASS(class_name) {};)
// go to the cpp file of the class and assign the reference to the holding instance variable of the singleton
// (es: lumina::my_singleton_class_name* lumina::my_singleton_class_name::singleton_instance_ = nullptr;
// then instance the singleton somewhere in the application. You can the access it doing my_class::get_singleton() 
#define LUMINA_SINGLETON_CLASS(class_type) class_type : public lumina_singleton_t<class_type>

template<class singleton_class_type>
struct lumina_singleton_t
{
public:

	lumina_singleton_t() { singleton_instance_ = reinterpret_cast<singleton_class_type*>(this); }

	static singleton_class_type& get_singleton() { return *singleton_instance_; }

private:

	static singleton_class_type* singleton_instance_;

};