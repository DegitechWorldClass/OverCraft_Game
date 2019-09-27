#pragma once

#include "Include.h"
#include "Define.h"
#include "Property.h"
#include "Enum.h"
#include "Math.h"

#include "CollisionData.h"
#include "CBox.h"
#include "CSphere.h"
#include "CRect.h"
#include "CTexture.h"
#include "CObject.h"
#include "CTimer.h"
#include "CModel.h"
#include "CSound.h"
#include "CRay.h"

#include "CRenderer2D.h"
#include "CRenderer3D.h"
#include "CLineRenerer.h"
#include "CText.h"
#include "CTransform.h"
#include "CBoxCollider2D.h"
#include "CRigidBody2D.h"
#include "CRigidBody3D.h"
#include "CAnimation2D.h"
#include "CAnimation3D.h"
#include "CSpriteRenderer.h"
#include "CMeshRenderer.h"
#include "CTerrain.h"

template <typename T>
void Lerp(T* target, const T& start, const T& end, float speed)
{
	*target = start + (end - start) * speed;
}

static float lerp(float a, float b, float t)
{
	return a - (a*t) + (b*t);
}

#include "CImageManager.h"
#include "CSceneManager.h"
#include "CInputManager.h"
#include "CCameraManager.h"
#include "CObjectManager.h"
#include "CTimeManager.h"
#include "CSoundManager.h"
#include "CModelManager.h"



#include "CPhysic.h"

