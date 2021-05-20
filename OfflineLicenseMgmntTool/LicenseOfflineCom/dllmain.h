// dllmain.h : Declaration of module class.

class CLicenseOfflineComModule : public ATL::CAtlDllModuleT< CLicenseOfflineComModule >
{
public :
	DECLARE_LIBID(LIBID_LicenseOfflineComLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_LICENSEOFFLINECOM, "{13e26d18-52ce-47db-aa46-4ea9279ffd9f}")
};

extern class CLicenseOfflineComModule _AtlModule;
