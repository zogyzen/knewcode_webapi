/*
apacheģ�鿪����
#����httpd.conf��apache2.conf

#����
LoadModule dlib_kc_module "D:/mycode/knewcode_project/trunk/debug/kc_apache_mod.dll"
AddHandler dlib_kc_extname .kc
dlib_kc_path "D:/mycode/knewcode_project/trunk/debug/"

#�޸ģ�Linux�£���������ҳĿ¼Ȩ�ޣ���ӡ�www-data���û���Ķ�дȨ�ޣ�
DocumentRoot "C:/KCPage/"
<IfModule dir_module>
    DirectoryIndex index.kc index.html
</IfModule>
<Directory />
	<FilesMatch "\.(dll|so)">
		Order Deny,Allow
		Deny from all
	</FilesMatch>
    Options FollowSymLinks
    AllowOverride None
    Order deny,allow
    Allow from all
</Directory>
*/
/*
Windows��CodeBlocks�ĵ��ԣ�
1������Apache��httpd���̣��ҵ�2��httpd�������߳�������PIDֵ���á�httpd -X������ֻ����1�����̣���
2����CodeBlocks���ߵĲ˵��Debug -> Attach to process...��������������PIDֵ��
3��������kc_apache_mod�����̣���ʼ���ԡ�
*/

#include "std.h"
#include "apache_work.h"

extern "C"
{
    string g_strKCFullPath = "KCϵͳ·��";
    string g_strPageRootFullPath = "��ҳ·��";

    // ʵ�ʵĴ�����
    int dlib_kc_handler(request_rec *r)
    {
        // �ж��Ƿ�ģ����Ҫ����
        if (nullptr == r->handler || strcmp("dlib_kc_extname", r->handler) != 0)
            return DECLINED;
        // ���غ��Ĵ�����
        static CAPACHEWork g_work(g_strKCFullPath, g_strPageRootFullPath);
        g_work.Work(*r);
        // ����
        return OK;
    }

    // ���Ӻ���������ע�ᴦ����
    void dlib_kc_register_hooks(apr_pool_t *p)
    {
        cout << "begin" << endl;
        ap_hook_handler(dlib_kc_handler, NULL, NULL, APR_HOOK_MIDDLE);
    }

    // ��ȡ���õ�KCϵͳ·��
    const char *get_mod_kc_path(cmd_parms *cmd, void *mconfig, const char *name)
    {
        //char *szSrvRootPath = ap_server_root_relative(cmd->pool, "");     // apache�İ�װ·��
        g_strKCFullPath = name;    // �������ж�ȡKCϵͳ·��
        // ��ʽ��·���ַ���
        g_strKCFullPath = CUtilFunc::FormatPath(g_strKCFullPath);
        return NULL;
    }

    // ��ȡ���õ���ҳĿ¼
    const char *get_mod_rt_path(cmd_parms *cmd, void *mconfig, const char *name)
    {
        g_strPageRootFullPath = name;    // �������ж�ȡ��ҳĿ¼
        // ��ʽ��·���ַ���
        g_strPageRootFullPath = CUtilFunc::FormatPath(g_strPageRootFullPath);
        return NULL;
    }

    //�����ļ�http.conf�е�������Ķ�ȡ������
    static const command_rec authn_jira_cmds[] =
    {
        AP_INIT_TAKE1("dlib_kc_path", (cmd_func)get_mod_kc_path, NULL, OR_FILEINFO, "dlib_kc_path"),
        AP_INIT_TAKE1("DocumentRoot", (cmd_func)get_mod_rt_path, NULL, OR_FILEINFO, "DocumentRoot"),
        { NULL }
    };

    // ע�ṳ�Ӻ����Ľṹ
    module AP_MODULE_DECLARE_DATA dlib_kc_module = {
        STANDARD20_MODULE_STUFF,
        NULL,                   /* create per-dir    config structures */
        NULL,                   /* merge  per-dir    config structures */
        NULL,                   /* create per-server config structures */
        NULL,                   /* merge  per-server config structures */
        authn_jira_cmds,        /* table of config file commands       */
        dlib_kc_register_hooks  /* register hooks                      */
    };
}
