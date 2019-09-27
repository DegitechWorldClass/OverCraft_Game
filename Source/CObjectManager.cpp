#include "DXUT.h"
#include "CObjectManager.h"

CObjectManager::CObjectManager()
{
	for (INT i = ObjectTag::Start; i < ObjectTag::End; i++)
	{
		set<ObjectTag> list; 

		for (INT j = ObjectTag::Start; j < ObjectTag::End; j++)
		{
			list.insert((ObjectTag)j);
		}
		m_mapCollisionDetectlist[(ObjectTag)i] = list;
	}
}


CObjectManager::~CObjectManager()
{
	for (auto& iter : m_Objects)
	{
		iter->Release();
		SAFE_DELETE(iter);
	}
	m_Objects.clear();
}



void CObjectManager::RegisterRenderer2D(CRenderer2D * _pRenderer2D)
{
	m_SortedRenderer2DList[_pRenderer2D->m_SortingLayer].push_back(_pRenderer2D);

	for (auto iter : m_SortedRenderer2DList)
	{
		iter.second.sort([&](CRenderer2D *  pPrev, CRenderer2D *  pNext)->bool { return pPrev->m_iOrderInLayer < pNext->m_iOrderInLayer; });
	}
}

void CObjectManager::UnRegisterRenderer2D(CRenderer2D * _pRenderer2D)
{
	m_SortedRenderer2DList[_pRenderer2D->m_SortingLayer].remove(_pRenderer2D);
}

void CObjectManager::RegisterRenderer3D(CRenderer3D * _pRenderer3D)
{
	m_listRender3D.push_back(_pRenderer3D);
}

void CObjectManager::UnRegisterRenderer3D(CRenderer3D * _pRenderer3D)
{
	m_listRender3D.remove(_pRenderer3D);
}

void CObjectManager::ClearAllObjects()
{
	for (auto& iter : m_Objects)
	{
		if(iter->GetIsStatic())
		{
			for (auto iter2 : iter->m_listChild)
			{
				iter2->SetIsStatic(true);
			}
		}

	}


	
	for (auto& iter : m_Objects)
	{
		if (!iter->GetIsStatic())
		{
			iter->Destroy();
		}
	}
}

void CObjectManager::DeleteCollisionDetect(ObjectTag Tag1, ObjectTag Tag2)
{
	auto find1 = m_mapCollisionDetectlist[Tag1].find(Tag2);
		
	if(find1 != m_mapCollisionDetectlist[Tag1].end())
		m_mapCollisionDetectlist[Tag1].erase(find1);
	
	auto find2 = m_mapCollisionDetectlist[Tag2].find(Tag1);

	if (find2 != m_mapCollisionDetectlist[Tag2].end())
		m_mapCollisionDetectlist[Tag2].erase(find2);
}

CObject * CObjectManager::FindObjectWithName(CRString _Name)
{
	for (auto& iter : m_Objects)
	{
		if (iter->GetName() == _Name)
		{
			return iter;
		}
	}
	return nullptr;
}

list<CObject*> CObjectManager::FindObjectsWithName(CRString _Name)
{
	list<CObject*> listFind;

	for (auto& iter : m_Objects)
	{
		if (iter->GetName() == _Name)
		{
			listFind.push_back(iter);
		}
	}
	return listFind;
}

CObject * CObjectManager::FindObjectWithTag(ObjectTag _Tag)
{
	for (auto& iter : m_Objects)
	{
		if (iter->GetObjectTag() == _Tag)
		{
			return iter;
		}
	}
	return nullptr;
}

list<CObject*> CObjectManager::FindObjectsWithTags(ObjectTag _Tag)
{
	list<CObject*> listFind;

	for (auto& iter : m_Objects)
	{
		if (iter->GetObjectTag() == _Tag)
		{
			listFind.push_back(iter);
		}
	}
	return listFind;
}


void CObjectManager::Update()
{
	for (auto& iter = m_Objects.begin(); iter != m_Objects.end();)
	{
		CObject * pObj = (*iter);

		pObj->Update();

		for (auto& iter : pObj->GetComponents())
		{
			if (iter->GetIsEnable())
			{
				iter->Update();
			}
		}

		//auto RigidBody = (*iter)->GetComponent<CRigidBody>();

		//if (RigidBody != NULL)
		//{
		//	if (RigidBody->GetIsEnable())
		//	{
		//		if (bIsCollide == FALSE)
		//		{
		//			(*iter)->Transform->Translation(RigidBody->GetMovePos());
		//			//RigidBody->SetMovePos(Vector2(0.f, -10.f));
		//		}
		//		else
		//		{
		//			//(*iter)->Transform->Translation(-RigidBody->GetMovePos()*1.f);
		//		}
		//	}
		//}


		auto BoxCollider01 = (*iter)->GetComponent<CBoxCollider2D>();
		bool bIsCollide = FALSE;
		if (BoxCollider01 != NULL && BoxCollider01->GetIsEnable() != false)
		{
			for (auto& iter2 = std::next(iter, 1); iter2 != m_Objects.end(); iter2++)
			{
				if (m_mapCollisionDetectlist[(*iter)->GetObjectTag()].find((*iter2)->GetObjectTag()) == m_mapCollisionDetectlist[(*iter)->GetObjectTag()].end())
				{
					continue;
				}
				auto BoxCollider02 = (*iter2)->GetComponent<CBoxCollider2D>();

				if (BoxCollider02 == NULL) continue;

				if (BoxCollider02->GetIsEnable() == false) continue;

				 bIsCollide = false;

				float Length = GetLength(Vector2((*iter)->Transform->m_vPosition), Vector2((*iter2)->Transform->m_vPosition));

				float w1 = BoxCollider01->GetSize().x;
				float h1 = BoxCollider01->GetSize().y;
				float long1 = w1 > h1 ? w1 : h1;


				float w2 = BoxCollider02->GetSize().x;
				float h2 = BoxCollider02->GetSize().y;
				float long2 = w2 > h2 ? w2 : h2;



				if (Length < (w1+h1) + (w2+h2))
				{
					bIsCollide = (Physic.CheckCollision(
						BoxCollider01->m_reCollisionRect,
						(*iter)->Transform->m_vRotation.z,
						BoxCollider02->m_reCollisionRect,
						(*iter2)->Transform->m_vRotation.z));
	/*				if ((*iter)->Transform->m_fRotation != 0.f && (*iter2)->Transform->m_fRotation != 0.f)
					{
						bIsCollide = (Physic.CheckCollision(
							BoxCollider01->m_reCollisionRect,
							(*iter)->Transform->m_fRotation,
							BoxCollider02->m_reCollisionRect,
							(*iter2)->Transform->m_fRotation));
					}
					else

					{
						bIsCollide = (Physic.CheckCollision(BoxCollider02->m_reCollisionRect, BoxCollider01->m_reCollisionRect));
					}*/
				}
				else continue;
				//bool bIsCollide = Math::CheckCollision(iter->GetComponent<CBoxCollider>()->m_reCollisionRect, _pObj->GetComponent<CBoxCollider>()->m_reCollisionRect);
				auto& Collisionlist = (*iter)->GetComponent<CBoxCollider2D>()->m_listCollision;

				auto& find = Collisionlist.find((*iter2));

				if (find == Collisionlist.end())
				{
					if (bIsCollide == true)
					{
						Collisionlist.insert(*iter2);
						for (auto iter : (*iter)->GetComponents())
						{
							iter->OnCollisionEnter(*iter2);
						}
						for (auto iter2 : (*iter2)->GetComponents())
						{
							iter2->OnCollisionEnter(*iter);
						}
					}
				}
				if (find != Collisionlist.end())
				{
					if (bIsCollide == true)
					{
						for (auto iter : (*iter)->GetComponents())
						{
							iter->OnCollisionStay(*iter2);
						}
						for (auto iter2 : (*iter2)->GetComponents())
						{
							iter2->OnCollisionStay(*iter);
						}
					}
					if (bIsCollide == false)
					{
						for (auto iter : (*iter)->GetComponents())
						{
							iter->OnCollisionExit(*iter2);
						}
						for (auto iter2 : (*iter2)->GetComponents())
						{
							iter2->OnCollisionExit(*iter);
						}						
						Collisionlist.erase(find);
					}
				}
			}
		}






		//BoxCollider 컴포넌트를 사용하는 오브젝트들은 충돌 검사를 진행하게 됩니다.
		//CollisionProcessing(*iter);
		// 오브젝트가 파괴되었다면
		if (TRUE == (*iter)->m_bDestroy)
		{
			
			for (auto iter : (*iter)->m_listChild)
			{
				iter->m_bDestroy = true;
			}
			(*iter)->m_listChild.clear();

			for (auto iter2 : m_Objects)
			{
				auto Collider = iter2->GetComponent<CBoxCollider2D>();
				if (Collider)
				{
					auto find = Collider->m_listCollision.find(*iter);
					if (Collider->m_listCollision.end() != find)
						Collider->m_listCollision.erase(find);
				}
			}
			DEBUG_LOG("Object Destroyed : %s", (*iter)->GetName().c_str());
			(*iter)->Release();
			SAFE_DELETE((*iter));
			iter = m_Objects.erase(iter);

		}
		else iter++;
	}


}

void CObjectManager::Render()
{
	for (auto iter : m_listRender3D)
	{
		iter->Render();
	}
	IMAGE.End();

	bool InterfaceRenderer = false;
	IMAGE.Begin(false);
	for (auto iter : m_SortedRenderer2DList)
	{
	
		
		for (auto iter2 : iter.second)
		{
			if (iter2->GetIsInterFace() != InterfaceRenderer)
			{
				InterfaceRenderer = !InterfaceRenderer;
				IMAGE.ReBegin(InterfaceRenderer);
			}
			iter2->Render();
		}
	}
	IMAGE.End();
	IMAGE.Begin(false);

}

