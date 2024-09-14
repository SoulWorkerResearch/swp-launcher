#include "get_cmdline.hpp"

namespace swp::l
{
	auto get_cmdline(INT argc, TCHAR* argv[]) -> std::wstring
	{
		std::wstring line{};

		// skip 2 arguments
		// [0] this application
		// [1] SoulWorker.exe

		for (const auto x : std::span{ argv, (size_t)argc } | views::drop(2)) {
			line.append(x);
			line.append(TEXT(" "));
		}

		return line;
	}
}