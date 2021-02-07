#include "natives.h"
#include "extension.h"
#include "iterator_container.h"
#include <unordered_set>
#include <string>

#define GET_HNDL(h, htype)                                                                         \
	do                                                                                             \
	{                                                                                              \
		Handle_t hndl = (Handle_t)params[1];                                                       \
		HandleError err;                                                                           \
		HandleSecurity sec(pContext->GetIdentity(), myself->GetIdentity());                        \
		if ((err = handlesys->ReadHandle(hndl, htype, &sec, (void **)&h)) != HandleError_None)     \
		{                                                                                          \
			return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);          \
		}                                                                                          \
	} while (0)

// Lol no
typedef std::unordered_set< cell_t > cellset;
typedef std::unordered_set< std::string > stringset;

typedef IteratorContainer< cellset > celliter;
typedef IteratorContainer< stringset > stringiter;

static cell_t Native_CellSet(IPluginContext *pContext, const cell_t *params)
{
	cellset *set = new cellset();

	Handle_t hndl = handlesys->CreateHandle(g_CellSet, set, pContext->GetIdentity(), myself->GetIdentity(), NULL);

	if (!hndl)
	{
		delete set;
		return pContext->ThrowNativeError("Failed to create set");
	}

	for (int i = 1; i <= params[0]; ++i)
	{
		cell_t *out;
		pContext->LocalToPhysAddr(params[i], &out);
		set->insert(*out);
	}

	return hndl;
}

static cell_t Native_CellSet_Insert(IPluginContext *pContext, const cell_t *params)
{
	cellset *set;
	GET_HNDL(set, g_CellSet);
	for (int i = 2; i <= params[0]; ++i)
	{
		cell_t *out;
		pContext->LocalToPhysAddr(params[i], &out);
		set->insert(*out);
	}
	return 0;
}

static cell_t Native_CellSet_Erase(IPluginContext *pContext, const cell_t *params)
{
	cellset *set;
	GET_HNDL(set, g_CellSet);
	for (int i = 2; i <= params[0]; ++i)
	{
		cell_t *out;
		pContext->LocalToPhysAddr(params[i], &out);
		set->erase(*out);
	}
	return 0;
}

static cell_t Native_CellSet_Find(IPluginContext *pContext, const cell_t *params)
{
	cellset *set;
	GET_HNDL(set, g_CellSet);
	return set->find(params[2]) != set->end();
}

static cell_t Native_CellSet_Size(IPluginContext *pContext, const cell_t *params)
{
	cellset *set;
	GET_HNDL(set, g_CellSet);
	return (cell_t)set->size();
}

static cell_t Native_CellSet_Empty(IPluginContext *pContext, const cell_t *params)
{
	cellset *set;
	GET_HNDL(set, g_CellSet);
	return (cell_t)set->empty();
}

static cell_t Native_CellSet_Swap(IPluginContext *pContext, const cell_t *params)
{
	cellset *set;
	GET_HNDL(set, g_CellSet);

	cellset *set2;
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
	cellset *set;
	GET_HNDL(set, g_CellSet);

	cellset *set2;
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
	cellset *set;
	GET_HNDL(set, g_CellSet);
	set->clear();
	return 0;
}

static cell_t Native_CellSet_Iter(IPluginContext *pContext, const cell_t *params)
{
	cellset *set;
	GET_HNDL(set, g_CellSet);
	
	celliter *it = new celliter(set, set->begin(), set->end());
	Handle_t hndl = handlesys->CreateHandle(g_CellIterator, it, pContext->GetIdentity(), myself->GetIdentity(), NULL);

	if (!hndl)
	{
		delete it;
		return pContext->ThrowNativeError("Failed to create set iterator");
	}

	return hndl;
}


static cell_t Native_StringSet(IPluginContext *pContext, const cell_t *params)
{
	stringset *set = new stringset();

	Handle_t hndl = handlesys->CreateHandle(g_StringSet, set, pContext->GetIdentity(), myself->GetIdentity(), NULL);

	if (!hndl)
	{
		delete set;
		return pContext->ThrowNativeError("Failed to create set");
	}

	for (int i = 1; i <= params[0]; ++i)
	{
		char *str;
		pContext->LocalToString(params[i], &str);
		set->insert(std::string(str));
	}

	return hndl;
}

static cell_t Native_StringSet_Insert(IPluginContext *pContext, const cell_t *params)
{
	stringset *set;
	GET_HNDL(set, g_StringSet);
	for (int i = 2; i <= params[0]; ++i)
	{
		char *str;
		pContext->LocalToString(params[i], &str);
		set->insert(std::string(str));
	}
	return 0;
}

static cell_t Native_StringSet_Find(IPluginContext *pContext, const cell_t *params)
{
	stringset *set;
	GET_HNDL(set, g_StringSet);
	char *str;
	pContext->LocalToString(params[2], &str);
	return set->find(std::string(str)) != set->end();
}

static cell_t Native_StringSet_Erase(IPluginContext *pContext, const cell_t *params)
{
	stringset *set;
	GET_HNDL(set, g_StringSet);
	for (int i = 2; i <= params[0]; ++i)
	{
		char *str;
		pContext->LocalToString(params[i], &str);
		set->erase(std::string(str));
	}
	return 0;
}

static cell_t Native_StringSet_Size(IPluginContext *pContext, const cell_t *params)
{
	stringset *set;
	GET_HNDL(set, g_StringSet);
	return (cell_t)set->size();
}

static cell_t Native_StringSet_Empty(IPluginContext *pContext, const cell_t *params)
{
	stringset *set;
	GET_HNDL(set, g_StringSet);
	return (cell_t)set->empty();
}

static cell_t Native_StringSet_Swap(IPluginContext *pContext, const cell_t *params)
{
	stringset *set;
	GET_HNDL(set, g_StringSet);

	stringset *set2;
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
	stringset *set;
	GET_HNDL(set, g_StringSet);

	stringset *set2;
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
	stringset *set;
	GET_HNDL(set, g_StringSet);
	set->clear();
	return 0;
}

static cell_t Native_StringSet_Iter(IPluginContext *pContext, const cell_t *params)
{
	stringset *set;
	GET_HNDL(set, g_StringSet);
	stringiter *it = new stringiter(set, set->begin(), set->end());
	Handle_t hndl = handlesys->CreateHandle(g_StringIterator, it, pContext->GetIdentity(), myself->GetIdentity(), NULL);

	if (!hndl)
	{
		delete it;
		return pContext->ThrowNativeError("Failed to create set iterator");
	}

	return hndl;
}

static cell_t Native_CIter_Next(IPluginContext *pContext, const cell_t *params)
{
	celliter *it;
	GET_HNDL(it, g_CellIterator);
	return it->Next();
}

static cell_t Native_CIter_Get(IPluginContext *pContext, const cell_t *params)
{
	celliter *it;
	GET_HNDL(it, g_CellIterator);
	return *it->Current();
}

static cell_t Native_SIter_Next(IPluginContext *pContext, const cell_t *params)
{
	stringiter *it;
	GET_HNDL(it, g_StringIterator);
	return it->Next();
}

static cell_t Native_SIter_Get(IPluginContext *pContext, const cell_t *params)
{
	stringiter *it;
	GET_HNDL(it, g_StringIterator);
	std::string s = *it->Current();
	pContext->StringToLocal(params[2], params[3], s.c_str());
	return 0;
}


sp_nativeinfo_t g_Natives[] = {
	{"CellSet.CellSet", 			Native_CellSet},
	{"CellSet.Insert", 				Native_CellSet_Insert},
	{"CellSet.Erase", 				Native_CellSet_Erase},
	{"CellSet.Find", 				Native_CellSet_Find},
	{"CellSet.Size.get", 			Native_CellSet_Size},
	{"CellSet.Empty.get", 			Native_CellSet_Empty},
	{"CellSet.Swap", 				Native_CellSet_Swap},
	{"CellSet.Equals",				Native_CellSet_Equals},
	{"CellSet.Clear", 				Native_CellSet_Clear},
	{"CellSet.Iterator", 			Native_CellSet_Iter},

	{"StringSet.StringSet", 		Native_StringSet},
	{"StringSet.Insert", 			Native_StringSet_Insert},
	{"StringSet.Find", 				Native_StringSet_Find},
	{"StringSet.Erase", 			Native_StringSet_Erase},
	{"StringSet.Size.get", 			Native_StringSet_Size},
	{"StringSet.Empty.get", 		Native_StringSet_Empty},
	{"StringSet.Swap", 				Native_StringSet_Swap},
	{"StringSet.Equals", 			Native_StringSet_Equals},
	{"StringSet.Clear", 			Native_StringSet_Clear},
	{"StringSet.Iterator", 			Native_StringSet_Iter},

	{"CellSetIterator.Next", 		Native_CIter_Next},
	{"CellSetIterator.Get", 		Native_CIter_Get},

	{"StringSetIterator.Next", 		Native_SIter_Next},
	{"StringSetIterator.Get", 		Native_SIter_Get},
	{NULL, NULL}
};