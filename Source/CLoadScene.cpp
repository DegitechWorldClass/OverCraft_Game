#include "DXUT.h"
#include "CLoadScene.h"


CLoadScene::CLoadScene()
{
}


CLoadScene::~CLoadScene()
{
}

void CLoadScene::Init()
{
	MODEL.AddShader("TOON", "./Shader/ToonShader.fx");

	LoadMesh("PLAYER_IDLE", "Player/Idle/Idle","Player/Map/",111);
	LoadMesh("PLAYER_RUN", "Player/Run/Run", "Player/Map/", 26);
	LoadMesh("PLAYER_SWINGA", "Player/Attack/SwingA", "Player/Map/", 22);
	LoadMesh("PLAYER_SWINGB", "Player/Attack/SwingB", "Player/Map/", 22);
	LoadMesh("PLAYER_SWINGC", "Player/Attack/SwingC", "Player/Map/", 22);
	LoadMesh("PLAYER_STING", "Player/Attack/Sting", "Player/Map/", 46);
	LoadMesh("PLAYER_TURNSWING", "Player/Attack/TURNSWING", "Player/Map/", 29);
	LoadMesh("PLAYER_DASH", "Player/Dash/Dash", "Player/Map/", 24);


	LoadMesh("MOB_001_ATTACK","Mob/001/Attack/Attack","Mob/001/",53);
	LoadMesh("MOB_001_IDLE", "Mob/001/Idle/Idle", "Mob/001/",41);
	LoadMesh("MOB_001_RUN", "Mob/001/Run/Run", "Mob/001/",31);
	LoadMesh("MOB_001_HIT", "Mob/001/Hit/Hit", "Mob/001/",16);
	LoadMesh("MOB_001_DEATH", "Mob/001/Death/Death", "Mob/001/",88);


	m_LoadMax = m_vecMeshLoad.size() + m_vecSoundLoad.size() + m_vecImageLoad.size();
	m_LoadSize = 0;
	DEBUG_LOG("Now Loading Resources...");
}

void CLoadScene::Update()
{
	if (m_LoadSize >= m_LoadMax - 1)
		SCENE.ChangeScene("S_MAIN"); 
	
	for (int i = 0; i <8; i++)
	{
		m_MeshLoadThread[i] = thread(&CLoadScene::LoadMeshFirst, m_vecMeshLoad[m_LoadSize++]);
		m_MeshLoadThread[i].join();
		if (m_LoadSize >= m_LoadMax - 1) return;
		DEBUG_LOG("Loading Status %d / %d (%.1f%%)", m_LoadSize, m_LoadMax, 100.f *  (float)m_LoadSize / (float)m_LoadMax);

		LoadMeshFirst(m_vecMeshLoad[m_LoadSize++]);
		if (m_LoadSize >= m_LoadMax - 1) return;
		DEBUG_LOG("Loading Status %d / %d (%.1f%%)", m_LoadSize, m_LoadMax, 100.f *  (float)m_LoadSize / (float)m_LoadMax);
	}
	//m_MeshLoadThread[1] = thread(&CLoadScene::LoadMeshFirst, m_vecMeshLoad[m_LoadSize++]);
	//m_MeshLoadThread[1].join(); 
	//if (m_LoadSize >= m_LoadMax - 1) return;
	//DEBUG_LOG("Loading Status %d / %d (%.1f%%)", m_LoadSize, m_LoadMax, 100.f *  (float)m_LoadSize / (float)m_LoadMax);

	//LoadMeshFirst(m_vecMeshLoad[m_LoadSize++]);
	//if (m_LoadSize >= m_LoadMax - 1) return;

	//DEBUG_LOG("Loading Status %d / %d (%.1f%%)", m_LoadSize, m_LoadMax, 100.f *  (float)m_LoadSize / (float)m_LoadMax);



	/*if (ImageLoadList.empty() == FALSE)
	{
		auto Handle = ImageLoadList.front();
		m_ImageLoadThread = thread([&]()->void {IMAGE.AddTexture(Handle.m_Key, Handle.m_Path); 	m_LoadSize++;		ImageLoadList.pop_front();	});
		m_ImageLoadThread.join();

		DEBUG_LOG("Loading Status %d / %d (%.1f%%)", m_LoadSize, m_LoadMax, 100.f *  (float)m_LoadSize / (float)m_LoadMax);
	}

	if (SoundLoadList.empty() == FALSE)
	{
		auto Handle = SoundLoadList.front();
		m_SoundLoadThread = thread([&]()->void {SOUND.AddSound(Handle.m_Key, Handle.m_Path,SoundType::ST_BACKGROUND); 	m_LoadSize++; 	SoundLoadList.pop_front();});
		m_SoundLoadThread.join();

		DEBUG_LOG("Loading Status %d / %d (%.1f%%)", m_LoadSize, m_LoadMax, 100.f *  (float)m_LoadSize / (float)m_LoadMax);
	}
	*/





}

void CLoadScene::Render()
{
}

void CLoadScene::Release()
{
}

void CLoadScene::LoadSprite(CRString _Key, CRString _Path, int _iSize)
{
	if (_iSize == 1)
	{
		char Path[100];
		sprintf(Path, "./resource/%s.png", _Path.c_str());
		m_vecImageLoad.push_back(ImageLoadData(_Key, Path));
	}
	else
	{
		for (int i = 1; i <= _iSize; i++)
		{
			char Path[100];
			char Key[100];
			sprintf(Path, "./resource/%s (%d).png", _Path.c_str(), i);
			sprintf(Key, "%s (%d)", _Key.c_str(), i);

			m_vecImageLoad.push_back(ImageLoadData(Key, Path));
		}
	}
}

void CLoadScene::LoadMesh(CRString _Key, CRString _Path, CRString _MapPath, int _iSize)
{
	if (_iSize == 1)
	{
		char Path[100];
		sprintf(Path, "./resource/%s.obj", _Path.c_str());
	
		char MapPath[100];
		sprintf(Path, "./resource/%s", _MapPath.c_str());

		
		m_vecMeshLoad.push_back(MeshLoadData(_Key, Path, MapPath));
	}
	else
	{
		for (int i = 1; i <= _iSize; i++)
		{
			char Key[100];
			sprintf(Key, "%s (%d)", _Key.c_str(), i);

			char Path[100];
			sprintf(Path, "./resource/%s (%d).obj", _Path.c_str(), i);

			char MapPath[100];
			sprintf(MapPath, "./resource/%s", _MapPath.c_str());


			m_vecMeshLoad.push_back(MeshLoadData(Key, Path, MapPath));
		}
	}
}

void CLoadScene::LoadSound(CRString _Key, CRString _Path, int _iSize)
{
	if (_iSize == 1)
	{
		char Path[100];
		sprintf(Path, "./resource/%s.mp3", _Path.c_str());
		m_vecSoundLoad.push_back(SoundLoadData(_Key, Path));
	}
	else
	{
		for (int i = 1; i <= _iSize; i++)
		{
			char Path[100];
			char Key[100];
			sprintf(Path, "./resource/%s (%d).mp3", _Path.c_str(), i);
			sprintf(Key, "%s (%d)", _Key.c_str(), i);
			m_vecSoundLoad.push_back(SoundLoadData(Key, Path));
		}
	}
}

void CLoadScene::LoadMeshFirst(MeshLoadData& _Handle)
{	
	std::this_thread::sleep_for(Second(1) / 1000);
	MODEL.AddModel(_Handle.m_Key, _Handle.m_Path, _Handle.m_MapPath);

}

