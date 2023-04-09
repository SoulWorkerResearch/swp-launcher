// main.cpp : Defines the entry point for the application.
//

using namespace std;
using namespace std::ranges;
using namespace std::filesystem;
using namespace spdlog;

auto get_cmdline(INT argc, TCHAR* argv[]) -> decltype(auto)
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

INT _tmain(INT argc, TCHAR* argv[])
{
	STARTUPINFOW si{};
	si.cb = sizeof(si);

	PROCESS_INFORMATION pi{};

	auto cmdline{ get_cmdline(argc, argv) };

	if (not DetourCreateProcessWithDll(argv[1], cmdline.data(), NULL, NULL, TRUE, CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi, "SWPLoader.dll", NULL)) {
		if (ERROR_INVALID_HANDLE == GetLastError()) {
			critical("mismatch architecture");
			return EXIT_FAILURE;
		}

		critical("error: {} / {}", GetLastError(), std::system_category().message(GetLastError()));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
