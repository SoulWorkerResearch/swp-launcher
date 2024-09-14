#include <get_cmdline.hpp>
#include <dll_directory.hpp>
#include <handle_scope.hpp>

using namespace std;
using namespace std::ranges;
using namespace std::filesystem;
using namespace spdlog;
using namespace swp::l;

INT _tmain(INT argc, TCHAR* argv[])
{
	STARTUPINFOW si{ .cb {sizeof(si)} };

	PROCESS_INFORMATION pi{};

	auto cmdline{ get_cmdline(argc, argv) };

	const auto application{ std::filesystem::path{ argv[1] } };
	const auto directory{ application.parent_path() };

	const auto loader{ directory / "swp" / "core" / "SWPLoader.dll" };

	const handle_scope<dll_directory> cookie{ AddDllDirectory(loader.parent_path().generic_wstring().c_str()) };

	if (not DetourCreateProcessWithDll(application.generic_wstring().data(), cmdline.data(), NULL, NULL, FALSE, CREATE_DEFAULT_ERROR_MODE, NULL, directory.generic_wstring().data(), &si, &pi, loader.generic_string().data(), NULL)) {
		if (ERROR_INVALID_HANDLE == GetLastError()) {
			critical("mismatch architecture");
			return EXIT_FAILURE;
		}

		critical("error: {} / {}", GetLastError(), std::system_category().message(GetLastError()));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
