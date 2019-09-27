#pragma once

class CRect : public CollisionData
{
public:
	FLOAT Left;
	FLOAT Top;
	FLOAT Right;
	FLOAT Bottom;
public:
	CRect();
	~CRect();
	CRect(FLOAT _fLeft, FLOAT _fTop, FLOAT _fRight, FLOAT _fBottom);
	CRect(Vector2 _vPos, FLOAT _fWidth, FLOAT _fHeight);
	CRect(RECT _reRect);
	CRect(Vector2 _vVertex[4]);
	void operator *=(float _fScala)
	{
		this->Bottom *= _fScala;
		this->Left *= _fScala;
		this->Top *= _fScala;
		this->Right *= _fScala;
	}	
	CRect operator *(float _fScala)
	{
		CRect re = *this;
		re.Bottom *= _fScala;
		re.Left *= _fScala;
		re.Top *= _fScala;
		re.Right *= _fScala;
		return re;
	}
	operator RECT() const
	{
		return
		{
			(LONG)Left,
			(LONG)Top,
			(LONG)Right,
			(LONG)Bottom
		};
	}
	float	GetWidth() { return fabsf(Right - Left); }
	float	GetHeight() { return fabsf(Bottom - Top); }
	Vector2 GetLT() { return Vector2(Left, Top); }
	Vector2 GetRT() { return Vector2(Right, Top); }
	Vector2 GetLB() { return Vector2(Left, Bottom); }
	Vector2 GetRB() { return Vector2(Right, Bottom); }
	Vector2 GetCenter() { return Vector2(Left + (Right - Left) / 2, Top + (Bottom - Top) / 2); }
};
