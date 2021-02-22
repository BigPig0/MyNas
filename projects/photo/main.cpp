#include "util.h"
#include "utilc.h"
#include "easylog.h"
#if defined(WINDOWS_IMPL)
#include <windows.h>
#endif

using namespace util;

int main(int argc, char* argv[])
{
    char *conf = "photo";

    /** Dump设置 */
    char dmpname[20]={0};
    sprintf(dmpname, "%s.dmp", conf);
    CMiniDump dump(dmpname);

    /** 创建日志文件 */
    char path[MAX_PATH];
    sprintf(path, ".\\log\\%s\\log.txt", conf);
    Log::open(Log::Print::both, uvLogPlus::Level::Debug, path);
    Log::debug("version: %s %s", __DATE__, __TIME__);

    /** 加载配置文件 */
    sprintf(path, ".\\%s.conf", conf);
    if (!Settings::loadFromProfile(path)) {
        Log::error("Settings file error");
        return -1;
    }
    Log::debug("Settings::loadFromProfile ok");

    Sleep(INFINITE);

    return 0;
}