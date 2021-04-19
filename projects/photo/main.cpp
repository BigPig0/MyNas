#include "util.h"
#include "utilc.h"
#include "easylog.h"
#include "uvtools.h"
#include "photo.h"
#include "uv.h"
#if defined(WINDOWS_IMPL)
#include <windows.h>
#endif

using namespace util;

//����ȫ�ֱ���
uvtool_t        *g_uvtools;

/**
 * ɨ��Դ�ļ�Ŀ¼
 */
static uv_timer_t event_timer;
static void OnEventTimer(uv_timer_t* handle) {
    Log::debug("scan timer start");
    uvtool_file_scanpath(g_uvtools, g_photoConfig.srcDir.c_str(), [](uvtool_t *uvtool, fileinfo_linked_list_t *files, void *data){
        for(fileinfo_linked_list_node_t *tmp = files->head; tmp != NULL; tmp = tmp->next) {
            Log::debug("%d %s",tmp->type, util_string_c_str(tmp->name));
            if(tmp->type == UV_DIRENT_FILE) {
                PhotoFileIfo *f = new PhotoFileIfo;
                f->name = util_string_c_str(tmp->name);
                f->modifyTime = tmp->mtime;
                f->size = tmp->size;
                g_photoFileList.push_back(f);
            }
        }
    }, NULL);
    //uv_loop_t *uv = uv_default_loop();
    //uv_fs_t *req = new uv_fs_t;
    //int ret = uv_fs_scandir(uv, req, g_photoConfig.srcDir.c_str(), 0, [](uv_fs_t* req){
    //    g_photoFileList.clear();
    //    uv_dirent_t dent;
    //    while (uv_fs_scandir_next(req, &dent) != UV_EOF) {
    //        Log::debug("scan find:%s", dent.name);
    //        // ���� . �ļ�
    //        if( strcmp(dent.name, ".") == 0 || 0 == strcmp(dent.name, "..") )
    //            continue;

    //        if (dent.type & UV_DIRENT_DIR) {
    //            Log::error("this is a directory: %s", dent.name);
    //        } else if (dent.type & UV_DIRENT_FILE) {
    //            PhotoFileIfo *f = new PhotoFileIfo;
    //            // �ļ�����
    //            f->name = dent.name;
    //            // �ļ�·��
    //            string filePath = g_photoConfig.srcDir + dent.name;
    //            // �ļ�����-�޸�ʱ�䡢�ļ���С
    //            uv_fs_t stareq;
    //            uv_fs_stat(NULL, &stareq, filePath.c_str(), NULL);
    //            uv_stat_t* stat = uv_fs_get_statbuf(&stareq);
    //            f->modifyTime = (time_t)stat->st_mtim.tv_sec;
    //            f->size = stat->st_size;
    //            uv_fs_req_cleanup(&stareq);
    //            // �����ļ�����
    //            // ͼƬ�ļ�����exif
    //            //��ӵ�����
    //            g_photoFileList.push_back(f);
    //        }
    //    } //while
    //    uv_fs_req_cleanup(req);
    //    delete req;
    //});
    //if(ret < 0) {
    //    return;
    //}
}

int main(int argc, char* argv[])
{
    char *conf = "photo";

    /** Dump���� */
    char dmpname[20]={0};
    sprintf(dmpname, "%s.dmp", conf);
    CMiniDump dump(dmpname);

    /** ������־�ļ� */
    char path[MAX_PATH];
    sprintf(path, ".\\log\\%s\\log.txt", conf);
    Log::open(Log::Print::both, uvLogPlus::Level::Debug, path);
    Log::debug("version: %s %s", __DATE__, __TIME__);

    /** ���������ļ� */
    sprintf(path, ".\\%s.conf", conf);
    if (!Settings::loadFromProfile(path)) {
        Log::error("Settings file error");
        return -1;
    }
    g_photoConfig.srcDir = Settings::getValue("Photo", "srcDir", "./");
    g_photoConfig.dstDir = Settings::getValue("Photo", "dstDir", "./");
    Log::debug("Settings::loadFromProfile ok");

    uv_loop_t *uv = uv_default_loop();

    g_uvtools = uvtool_init(uv);

    
    uv_timer_init(uv, &event_timer);
    uv_timer_start(&event_timer, OnEventTimer, 1, 60000);
    uv_run(uv, UV_RUN_DEFAULT);

    Sleep(INFINITE);

    return 0;
}