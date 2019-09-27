#pragma once
class CMonsterBase
{
public:
	CMonsterBase();
	~CMonsterBase();

protected:
	float m_fCurHP;
	float m_fMaxHP;

	float m_fAttack;

	float m_fMoveSpeed;

	float m_fAttackDelay;

public:
	float GetCurHP() { return m_fCurHP; }
	void SetCurHP(float _fHP) { m_fCurHP = _fHP; }


	float GetMaxHP() { return m_fMaxHP; }
};


