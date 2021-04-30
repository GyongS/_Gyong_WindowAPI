#pragma once
class CSoundMgr
{
public:
	static CSoundMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSoundMgr;

		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
public:
	enum CHANNELID {
		BGM,
		// 플레이어
		DEAD,
		JUMP,

		// 천공의 노래
		ALLOW_START,
		ALLOW_LOOP,
		ALLOW_END,

		//하울링 게일
		HOWLINGGAIL_START,
		HOWLINGGAIL_LOOP,
		HOWLINGGAIL_END,
		HOWLINGGAIL_HIT,
		// 샤프아이즈
		SHARPEYES,

		// 메이플 용사
		MAPLEWARRIOR,
		MONSTER,
		// 몬스터
		MONSTER_ATTACK,
		MONSTER_DEAD,
		MONSTER_HIT,
		EFFECT,
		UI,
		PORTAL,
		// 윌
		SPYDERLEG,
		BEHOLDERBALL,
		MONITORBREAK,
		WHITEREDEYE,

		MAXCHANNEL


	};
private:
	CSoundMgr();
	~CSoundMgr();

public:
	void Initialize();

	void Release();
public:
	void PlaySound(const TCHAR* pSoundKey, CHANNELID eID);
	void PlayBGM(const TCHAR* pSoundKey);
	void StopSound(CHANNELID eID);
	void StopBGM();
	void StopAll();

private:
	void LoadSoundFile();

private:
	static CSoundMgr* m_pInstance;
	// 사운드 리소스 정보를 갖는 객체 
	map<TCHAR*, FMOD_SOUND*> m_mapSound;
	// FMOD_CHANNEL : 재생하고 있는 사운드를 관리할 객체 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];
	// 사운드 ,채널 객체 및 장치를 관리하는 객체 
	FMOD_SYSTEM* m_pSystem;

};

