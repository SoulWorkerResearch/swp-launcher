#include "dll_directory.hpp"

namespace swp::l
{
	void dll_directory::operator()(handle_type& _value) 
	{
		RemoveDllDirectory(_value);
	}
}