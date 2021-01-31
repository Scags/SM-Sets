#include "natives.h"
#include "extension.h"
#include <unordered_set>
#include <string>

#define GET_SMSET(set, htype)                                                                      \
	do                                                                                             \
	{                                                                                              \
		Handle_t hndl = (Handle_t)params[1];                                                       \
		HandleError err;                                                                           \
		HandleSecurity sec(pContext->GetIdentity(), myself->GetIdentity());                        \
		if ((err = handlesys->ReadHandle(hndl, htype, &sec, (void **)&set)) != HandleError_None)   \
		{                                                                                          \
			return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);          \
		}                                                                                          \
	} while (0)

static cell_t Native_CellSet(IPluginContext *pContext, const cell_t *params)
{
	std::unordered_set< cell_t > *set = new std::unordered_set< cell_t >();

	Handle_t hndl = handlesys->CreateHandle(g_CellSet, set, pContext->GetIdentity(), myself->GetIdentity(), NULL);

	if (!hndl)
	{
		delete set;
		return pContext->ThrowNativeError("Failed to create set");
	}

	return hndl;
}

static cell_t Native_CellSet_Insert(IPluginContext *pContext, const cell_t *params)
{
	std::unordered_set< cell_t > *set;
	GET_SMSET(set, g_CellSet);
	set->insert(params[2]);
	return 0;
}

static cell_t Native_CellSet_Erase(IPluginContext *pContext, const cell_t *params)
{
	std::unordered_set< cell_t > *set;
	GET_SMSET(set, g_CellSet);
	set->erase(params[2]);
	return 0;
}

static cell_t Native_CellSet_Find(IPluginContext *pContext, const cell_t *params)
{
	std::unordered_set< cell_t > *set;
	GET_SMSET(set, g_CellSet);
	return set->find(params[2]) != set->end();
}

//static cell_t Native_CellSet_IterGet(IPluginContext *pContext, const cell_t *params)
//{
//	std::unordered_set< cell_t > *set;
//	GET_SMSET(set, g_CellSet);
//	auto iter = *reinterpret_cast< std::unordered_set< cell_t >::iterator * >(params[2]);
//	return *iter;
//}
//
//static cell_t Native_CellSet_IterNext(IPluginContext *pContext, const cell_t *params)
//{
//	std::unordered_set< cell_t > *set;
//	GET_SMSET(set, g_CellSet);
//	auto iter = *reinterpret_cast< std::unordered_set< cell_t >::iterator * >(params[2]);
//	iter++;
//	return (cell_t)&iter;
//}

static cell_t Native_CellSet_Size(IPluginContext *pContext, const cell_t *params)
{
	std::unordered_set< cell_t > *set;
	GET_SMSET(set, g_CellSet);
	return (cell_t)set->size();
}

static cell_t Native_CellSet_Empty(IPluginContext *pContext, const cell_t *params)
{
	std::unordered_set< cell_t > *set;
	GET_SMSET(set, g_CellSet);
	return (cell_t)set->empty();
}

static cell_t Native_CellSet_Swap(IPluginContext *pContext, const cell_t *params)
{
	std::unordered_set< cell_t > *set;
	GET_SMSET(set, g_CellSet);

	std::unordered_set< cell_t > *set2;
	HandleError err;
	HandleSecurity sec(pContext->GetIdentity(), myself->GetIdentity());

	if ((err = handlesys->ReadHandle(params[2], g_CellSet, &sec, (void **)&set2)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle 2 %x (error: %d)", params[2], err);
	}

	set->swap(*set2);
	return 0;
}

static cell_t Native_CellSet_Equals(IPluginContext *pContext, const cell_t *params)
{
	std::unordered_set< cell_t > *set;
	GET_SMSET(set, g_CellSet);

	std::unordered_set< cell_t > *set2;
	HandleError err;
	HandleSecurity sec(pContext->GetIdentity(), myself->GetIdentity());

	if ((err = handlesys->ReadHandle(params[2], g_CellSet, &sec, (void **)&set2)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle 2 %x (error: %d)", params[2], err);
	}

	return *set == *set2;
}

static cell_t Native_CellSet_Clear(IPluginContext *pContext, const cell_t *params)
{
	std::unordered_set< cell_t > *set;
	GET_SMSET(set, g_CellSet);
	set->clear();
	return 0;
}

//static cell_t Native_CellSet_Begin(IPluginContext *pContext, const cell_t *params)
//{
//	std::unordered_set< cell_t > *set;
//	GET_SMSET(set, g_CellSet);
//	return (cell_t)&set->begin();
//}
//
//static cell_t Native_CellSet_End(IPluginContext *pContext, const cell_t *params)
//{
//	std::unordered_set< cell_t > *set;
//	GET_SMSET(set, g_CellSet);
//	return (cell_t)&set->end();
//}

static cell_t Native_StringSet(IPluginContext *pContext, const cell_t *params)
{
	std::unordered_set< std::string > *set = new std::unordered_set< std::string >();

	Handle_t hndl = handlesys->CreateHandle(g_StringSet, set, pContext->GetIdentity(), myself->GetIdentity(), NULL);

	if (!hndl)
	{
		delete set;
		return pContext->ThrowNativeError("Failed to create set");
	}

	return hndl;
}

static cell_t Native_StringSet_Insert(IPluginContext *pContext, const cell_t *params)
{
	std::unordered_set< std::string > *set;
	GET_SMSET(set, g_StringSet);
	char *str;
	pContext->LocalToString(params[2], &str);
	set->insert(std::string(str));
	return 0;
}

static cell_t Native_StringSet_Find(IPluginContext *pContext, const cell_t *params)
{
	std::unordered_set< std::string > *set;
	GET_SMSET(set, g_StringSet);
	char *str;
	pContext->LocalToString(params[2], &str);
	return set->find(std::string(str)) != set->end();
}

static cell_t Native_StringSet_Erase(IPluginContext *pContext, const cell_t *params)
{
	std::unordered_set< std::string > *set;
	GET_SMSET(set, g_StringSet);
	char *str;
	pContext->LocalToString(params[2], &str);
	set->erase(std::string(str));
	return 0;
}

//static cell_t Native_StringSet_IterGet(IPluginContext *pContext, const cell_t *params)
//{
//	std::unordered_set< std::string > *set;
//	GET_SMSET(set, g_StringSet);
//	auto iter = *reinterpret_cast< std::unordered_set< std::string >::iterator * >(params[2]);
//	return pContext->StringToLocal(params[3], params[4], iter->c_str());
//}
//
//static cell_t Native_StringSet_IterNext(IPluginContext *pContext, const cell_t *params)
//{
//	std::unordered_set< std::string > *set;
//	GET_SMSET(set, g_StringSet);
//	auto iter = *reinterpret_cast< std::unordered_set< std::string >::iterator * >(params[2]);
//	iter++;
//	return (cell_t)&iter;
//}

static cell_t Native_StringSet_Size(IPluginContext *pContext, const cell_t *params)
{
	std::unordered_set< std::string > *set;
	GET_SMSET(set, g_StringSet);
	return (cell_t)set->size();
}

static cell_t Native_StringSet_Empty(IPluginContext *pContext, const cell_t *params)
{
	std::unordered_set< std::string > *set;
	GET_SMSET(set, g_StringSet);
	return (cell_t)set->empty();
}

static cell_t Native_StringSet_Swap(IPluginContext *pContext, const cell_t *params)
{
	std::unordered_set< std::string > *set;
	GET_SMSET(set, g_StringSet);

	std::unordered_set< std::string > *set2;
	HandleError err;
	HandleSecurity sec(pContext->GetIdentity(), myself->GetIdentity());

	if ((err = handlesys->ReadHandle(params[2], g_StringSet, &sec, (void **)&set2)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle 2 %x (error: %d)", params[2], err);
	}

	set->swap(*set2);
	return 0;
}

static cell_t Native_StringSet_Equals(IPluginContext *pContext, const cell_t *params)
{
	std::unordered_set< std::string > *set;
	GET_SMSET(set, g_StringSet);

	std::unordered_set< std::string > *set2;
	HandleError err;
	HandleSecurity sec(pContext->GetIdentity(), myself->GetIdentity());

	if ((err = handlesys->ReadHandle(params[2], g_StringSet, &sec, (void **)&set2)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle 2 %x (error: %d)", params[2], err);
	}

	return *set == *set2;
}

static cell_t Native_StringSet_Clear(IPluginContext *pContext, const cell_t *params)
{
	std::unordered_set< std::string > *set;
	GET_SMSET(set, g_StringSet);
	set->clear();
	return 0;
}

//static cell_t Native_StringSet_Begin(IPluginContext *pContext, const cell_t *params)
//{
//	std::unordered_set< std::string > *set;
//	GET_SMSET(set, g_StringSet);
//	return (cell_t)set->begin();
//}
//
//static cell_t Native_StringSet_End(IPluginContext *pContext, const cell_t *params)
//{
//	std::unordered_set< std::string > *set;
//	GET_SMSET(set, g_StringSet);
//	return (cell_t)set->end();
//}

sp_nativeinfo_t g_Natives[] = {
	{"CellSet.CellSet", 			Native_CellSet},
	{"CellSet.Insert", 				Native_CellSet_Insert},
	{"CellSet.Erase", 				Native_CellSet_Erase},
	{"CellSet.Find", 				Native_CellSet_Find},
//	{"CellSet.IterGet", 			Native_CellSet_IterGet},
//	{"CellSet.IterNext", 			Native_CellSet_IterNext},
	{"CellSet.Size.get", 			Native_CellSet_Size},
	{"CellSet.Empty.get", 			Native_CellSet_Empty},
	{"CellSet.Swap", 				Native_CellSet_Swap},
	{"CellSet.Equals", 			Native_CellSet_Equals},
	{"CellSet.Clear", 				Native_CellSet_Clear},
//	{"CellSet.Begin", 				Native_CellSet_Begin},
//	{"CellSet.End", 				Native_CellSet_End},

	{"StringSet.StringSet", 		Native_StringSet},
	{"StringSet.Insert", 			Native_StringSet_Insert},
	{"StringSet.Find", 				Native_StringSet_Find},
	{"StringSet.Erase", 			Native_StringSet_Erase},
//	{"StringSet.IterGet", 			Native_StringSet_IterGet},
//	{"StringSet.IterNext", 			Native_StringSet_IterNext},
	{"StringSet.Size.get", 			Native_StringSet_Size},
	{"StringSet.Empty.get", 		Native_StringSet_Empty},
	{"StringSet.Swap", 				Native_StringSet_Swap},
	{"StringSet.Equals", 			Native_StringSet_Equals},
	{"StringSet.Clear", 			Native_StringSet_Clear},
//	{"StringSet.Begin", 			Native_StringSet_Begin},
//	{"StringSet.End", 				Native_StringSet_End},
	{NULL, NULL}
};