#pragma once 

namespace swp::l
{
	struct dll_directory
	{
		using handle_type = DLL_DIRECTORY_COOKIE;

		void operator()(handle_type& _value);
	};
}