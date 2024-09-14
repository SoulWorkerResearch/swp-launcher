#pragma once 

using namespace std::ranges;

namespace swp::l
{
	auto get_cmdline(INT argc, TCHAR* argv[]) -> std::wstring;
}
