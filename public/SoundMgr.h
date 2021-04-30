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
		// �÷��̾�
		DEAD,
		JUMP,

		// õ���� �뷡
		ALLOW_START,
		ALLOW_LOOP,
		ALLOW_END,

		//�Ͽ︵ ����
		HOWLINGGAIL_START,
		HOWLINGGAIL_LOOP,
		HOWLINGGAIL_END,
		HOWLINGGAIL_HIT,
		// ����������
		SHARPEYES,

		// ������ ���
		MAPLEWARRIOR,
		MONSTER,
		// ����
		MONSTER_ATTACK,
		MONSTER_DEAD,
		MONSTER_HIT,
		EFFECT,
		UI,
		PORTAL,
		// ��
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
	// ���� ���ҽ� ������ ���� ��ü 
	map<TCHAR*, FMOD_SOUND*> m_mapSound;
	// FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];
	// ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
	FMOD_SYSTEM* m_pSystem;

};

