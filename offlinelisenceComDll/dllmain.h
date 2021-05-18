// dllmain.h : Declaration of module class.

class CofflinelisenceComDllModule : public ATL::CAtlDllModuleT< CofflinelisenceComDllModule >
{
public :
	DECLARE_LIBID(LIBID_offlinelisenceComDllLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_OFFLINELISENCECOMDLL, "{c591d639-8f54-47a9-9fd1-79a72672bcb7}")
};

extern class CofflinelisenceComDllModule _AtlModule;
