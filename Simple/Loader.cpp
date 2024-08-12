#include "Loader.h"

INITIALIZE_EASYLOGGINGPP
SlimUtils::SlimMem mem;
const SlimUtils::SlimModule* gameModule;
bool Loader::isRunning = true;

#pragma comment(lib, "../Memory/libMinHook.x86.lib")
#pragma comment(lib, "opengl32.lib")

std::streambuf* mConsoleOutBackup;
FILE* mConsoleOut;

inline void OpenConsole() {
	

	if (AllocConsole()) {
		mConsoleOutBackup = std::cout.rdbuf();
		freopen_s(&mConsoleOut, "CONOUT$", "w", stdout);
		char nt[100];
		sprintf_s(nt, "日志[%s]-%lld-%d", "Console-Wind", GetTickCount64(), GetCurrentProcessId());
		SetConsoleTitleA(nt);
		Sleep(100);
		HWND find = FindWindowA(NULL, nt);
		if (find) {
			HMENU menu = GetSystemMenu(find, FALSE);
			if (menu) {
					if (RemoveMenu(menu, 0xF060, 0)) {
						sprintf_s(nt, "日志[%s]-%lld-%d-已屏蔽关闭按钮", "Console-Wind", GetTickCount64(), GetCurrentProcessId());
						SetConsoleTitleA(nt);
					}
			}
		}
	}
	std::wcout.imbue(std::locale("", LC_CTYPE));

}

inline void CloseConsole() {
		if (mConsoleOut != NULL && mConsoleOutBackup != NULL) {
			cout.rdbuf(mConsoleOutBackup);
			fclose(mConsoleOut);
		}
		FreeConsole();
}

DWORD WINAPI ejectThread(LPVOID lpParam) {
	while (Loader::isRunning) {
		if ((GameData::isKeyDown(VK_CONTROL) && GameData::isKeyDown('L'))) {
			Loader::isRunning = false;  // Uninject
			break;
		}
		Sleep(20);
	}
	LOG(INFO) << "Stopping Threads...";
	Sleep(50);
	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), 1);
}

DWORD WINAPI start(LPVOID lpParam) {
	{
		FreeConsole();
		OpenConsole();

		el::Configurations conf;
		conf.setToDefault();
		conf.set(el::Level::Info, el::ConfigurationType::Filename, "logs.log");
		conf.set(el::Level::Warning, el::ConfigurationType::Filename, "logs.log");
#ifdef _DEBUG
		conf.set(el::Level::Debug, el::ConfigurationType::Filename, "logs.log");
		conf.set(el::Level::Error, el::ConfigurationType::Filename, "logs.log");
#else
		conf.set(el::Level::Debug, el::ConfigurationType::Enabled, "false");
		conf.set(el::Level::Error, el::ConfigurationType::Enabled, "false");
#endif // _DEBUG
		el::Loggers::reconfigureAllLoggers(conf);
	}

	LOG(INFO) << "Starting up...";
	init();
	DWORD procId = GetCurrentProcessId();
	if (!mem.Open(procId, SlimUtils::ProcessAccess::Full)) {
		LOG(FATAL) << "Failed to open process, error-code: " << GetLastError();
		return 1;
	}
	gameModule = mem.GetModule(L"Minecraft.Windows.exe");
	MH_Initialize();

	GameData::initGameData(gameModule, &mem, (HMODULE)lpParam);
	Target::init(Game.getPtrLocalPlayer());

	Utils::DownloadFile("https://fs-im-kefu.7moor-fs1.com/ly/4d2c3f00-7d4c-11e5-af15-41bf63ae4ea0/1717987481307/fusion-pixel-10px-monospaced-zh_hant.ttf"
		, "Downloaded/fusion-pixel-10px-monospaced-zh_hant.ttf");
	Utils::DownloadFile("https://fs-im-kefu.7moor-fs1.com/ly/4d2c3f00-7d4c-11e5-af15-41bf63ae4ea0/1718024505474/hacker.jpg"
		, "Downloaded/hacker.jpg");
	Utils::DownloadFile("https://fs-im-kefu.7moor-fs1.com/ly/4d2c3f00-7d4c-11e5-af15-41bf63ae4ea0/1719141324942/obj_w5rDlsOJwrLDjj7CmsOj_31598684973_143e_133b_3e2e_65c7ac409cdbbca8795ad15ef29831df.m4a"
		, "Downloaded/弃子pt.2.m4a");
	Utils::DownloadFile("https://fs-im-kefu.7moor-fs1.com/ly/4d2c3f00-7d4c-11e5-af15-41bf63ae4ea0/1719142802568/obj_w5rDlsOJwrLDjj7CmsOj_35013079457_54da_45af_8773_9f224a0abd9b0c7177f0a7f6f5ee28be.m4a"
		, "Downloaded/渐行渐远\\Drift Away.m4a");
	Hooks::Init();

	DWORD ejectThreadId;
	CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)ejectThread, lpParam, NULL, &ejectThreadId);  // Checking Keypresses
	LOG(INFO) << "EjectThread:" << ejectThreadId;

	cmdMgr->initCommands();
	LOG(INFO) << "Initialized command manager (1/3)";
	moduleMgr->initModules();
	LOG(INFO) << "Initialized module manager (2/3)";
	configMgr->init();
	LOG(INFO) << "Initialized config manager (3/3)";
	Hooks::Enable();

	std::thread countThread([] {
		while (Loader::isRunning) {
			Sleep(1000);
		}
		});
	countThread.detach();

	LOG(INFO)<<"Count thread started";

	ExitThread(0);
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)start, hModule, NULL, NULL);
		DisableThreadLibraryCalls(hModule);
		break;
	case DLL_PROCESS_DETACH:
		Loader::isRunning = false;

		configMgr->saveConfig();

		moduleMgr->disable();

		cmdMgr->disable();	

		Hooks::Restore();

		delete cmdMgr;
		delete configMgr;
		delete moduleMgr;


		MH_Uninitialize();
		if (Game.getLocalPlayer() != nullptr) {
			GuiData* guiData = Game.getClientInstance()->getGuiData();
			if (guiData != nullptr)
				guiData->displayClientMessageF("%sEjected!", RED);
		}
		break;
		LOG(INFO) << "Ejected!";
		break;
	}
	return TRUE;
}
////////////////////////////////////////////////////////////////////
//                          _ooOoo_                               //
//                         o8888888o                              //
//                         88" . "88                              //
//                         (| ^_^ |)                              //
//                         O\  =  /O                              //
//                      ____/`---'\____                           //
//                    .'  \\|     |//  `.                         //
//                   /  \\|||  :  |||//  \                        //
//                  /  _||||| -:- |||||-  \                       //
//                  |   | \\\  -  /// |   |                       //
//                  | \_|  ''\---/''  |   |                       //
//                  \  .-\__  `-`  ___/-. /                       //
//                ___`. .'  /--.--\  `. . ___                     //
//              ."" '<  `.___\_<|>_/___.'  >'"".                  //
//            | | :  `- \`.;`\ _ /`;.`/ - ` : | |                 //
//            \  \ `-.   \_ __\ /__ _/   .-` /  /                 //
//      ========`-.____`-.___\_____/___.-`____.-'========         //
//                           `=---='                              //
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^        //
//         佛祖保佑       永无BUG     永不断言                    //
////////////////////////////////////////////////////////////////////