#pragma once

#include "framework_ex/service_ex_i.h"
#include "framework_ex/framework_exception.h"
#include "kc_web/web_struct.h"

namespace KC
{
    // KCϵͳ�ӿ�
    class IKCWebApiWork : public IServiceEx
    {
    public:
        // չ��һ����ҳ�������������Ӧ��ӿ�
        virtual void RenderPage(IWebRequestRespond&) = 0;

    protected:
        virtual CALL_TYPE ~IKCWebApiWork() = default;
    };

    constexpr const char c_KCWebApiWorkSrvGUID[] = "IKCWebWork_B5E289BB-ADB8-92F8-CF31-BD411D2F52BF";

    class TKCWebApiWorkException : public TFWSrvException
	{
	public:
                TKCWebApiWorkException(int id, std::string place, std::string msg, std::string name)
                                : TFWSrvException(id, place, msg, name, c_KCWebApiWorkSrvGUID) {}
                TKCWebApiWorkException(int id, std::string place, std::string msg, IKCWebApiWork& srv)
				: TFWSrvException(id, place, msg, srv) {}
	};
}

