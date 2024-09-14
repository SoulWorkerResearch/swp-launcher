#pragma once 

#include "dll_directory.hpp"

namespace swp::l
{
	template<class T>
	struct handle_scope final {
	private:
		typename T::handle_type m_ptr{};

	public:
		handle_scope(typename T::handle_type&& _ptr) : m_ptr{ std::move(_ptr) } {}

		~handle_scope(void) {
			std::invoke(&dll_directory::operator(), dll_directory{}, m_ptr);
		}
	};
}
