#pragma once
#include <string>
#include <list>
#include <stdint.h>

using namespace std;

/** 图片配置信息 */
struct PhotoConfig {
    string srcDir;      //源路径，定时扫描
    string dstDir;     //目的路径，存储
};

enum MEDIA_TYPE {
    MEDIA_TYPE_UNKNOWN = 0,
    MEDIA_TYPE_IMAGE,
    MEDIA_TYPE_VIDEO
};

/** 文件信息 */
struct PhotoFileIfo {
    string name;    //文件名
    string type;    //文件类型
    MEDIA_TYPE mediaType; //种类
    time_t modifyTime; //最后修改时间
    uint64_t size;  //文件大小

    time_t exifTime; //图片拍摄时间
    double latitude; //图片拍摄地点
    double longitude;
};

/** 文件签名 */
struct FileSignature {
    const char *sinature;
    string type;
    MEDIA_TYPE mediaType;
};

extern PhotoConfig g_photoConfig;
extern list<PhotoFileIfo*> g_photoFileList;
extern FileSignature g_fileSignature[];