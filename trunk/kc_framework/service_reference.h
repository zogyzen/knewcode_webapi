#pragma once

namespace KC
{
    class CBundleContext;
    class CServiceReference : public IServiceReferenceEx
    {
    public:
        CServiceReference(string symbolic, long ID, IService* srv, CBundleContext& ct);
        virtual CALL_TYPE ~CServiceReference();

        // 得到引用编号
        long CALL_TYPE getID(void) const override;
        // 得到服务特征码
        const char* CALL_TYPE getGUID(void) const override;
        // 得到服务名（类名）
        const char* CALL_TYPE getName(void) const override;
        // 服务是否已失效（模块卸载、服务注销等）
        bool CALL_TYPE disable(void) const override;
        // 获取服务接口
        IService& CALL_TYPE getService(void) const override;
        // 获取模块接口
        const IBundle& CALL_TYPE getBundle(void) const override;
        // 写日志
        bool CALL_TYPE WriteLog(TLogInfo) const override;
    public:
        // 设置服务
        void setService(IService* srv);

    private:
        // 唯一特征码
        string m_symbolic;
        // 名称
        mutable string m_name;
        // 编号
        const long m_ID;
        // 服务接口
        IService* m_service = nullptr;
        // 框架
        CBundleContext& m_Context;
    };
}
