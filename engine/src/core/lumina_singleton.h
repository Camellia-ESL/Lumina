#pragma once

// A class defined with this macro will be used as a singleton, once instanced there will be only 1 possible instance of it
#define LUMINA_SINGLETON_CLASS(class_type) class_type : public singleton_t<class_type>

template<class singleton_class_type>
struct singleton_t
{
public:

	singleton_t() { singleton_instance_ = reinterpret_cast<singleton_class_type*>(this); }

	static singleton_class_type& get_singleton() { return *singleton_instance_; }

private:

	static singleton_class_type* singleton_instance_;

};