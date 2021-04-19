#pragma once
#include <string>
#include <list>
#include <stdint.h>

using namespace std;

/** ͼƬ������Ϣ */
struct PhotoConfig {
    string srcDir;      //Դ·������ʱɨ��
    string dstDir;     //Ŀ��·�����洢
};

enum MEDIA_TYPE {
    MEDIA_TYPE_UNKNOWN = 0,
    MEDIA_TYPE_IMAGE,
    MEDIA_TYPE_VIDEO
};

/** �ļ���Ϣ */
struct PhotoFileIfo {
    string name;    //�ļ���
    string type;    //�ļ�����
    MEDIA_TYPE mediaType; //����
    time_t modifyTime; //����޸�ʱ��
    uint64_t size;  //�ļ���С

    time_t exifTime; //ͼƬ����ʱ��
    double latitude; //ͼƬ����ص�
    double longitude;
};

/** �ļ�ǩ�� */
struct FileSignature {
    const char *sinature;
    string type;
    MEDIA_TYPE mediaType;
};

extern PhotoConfig g_photoConfig;
extern list<PhotoFileIfo*> g_photoFileList;
extern FileSignature g_fileSignature[];