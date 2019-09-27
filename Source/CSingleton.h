#pragma once
template <typename T>
class CSingleton
{
private:
	static T* p;
public:
	CSingleton() {}
	virtual ~CSingleton() {}
public:
	static T * GetInstance()
	{
		if (!p) p = new T;
		return p;
	}

	static void ReleaseInstance()
	{
		delete p;
		p = nullptr;
	}
};

template <class T>
T* CSingleton<T>::p = nullptr;