#pragma once

#include <fbxsdk.h>
#include <MoCommon.h>
#include <MoMath.h>
#include <MoFeatureResource.h>

//============================================================
/// @define ��������
#ifdef _MO_FBX_EXPORTS
#define MO_FBX_DECLARE MO_EXPORT
#else
#define MO_FBX_DECLARE MO_IMPORT
#endif

//============================================================
MO_NAMESPACE_USING(FBXSDK_NAMESPACE);
