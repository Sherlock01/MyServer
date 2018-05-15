#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <cstdio>

//���߳� 
template <typename T>
class Singleton
{
protected:
	Singleton() {}
	virtual ~Singleton() {}

public:
	static T* Instance()
	{
		if (NULL == m_instance)
		{
			CreateInstance();
		}
		return m_instance;
	}

	static void CreateInstance()
	{
		if (NULL == m_instance)
		{
			m_instance = new T();
		}
	}

	static void DestroyInstance()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = NULL;
		}
	}

protected:
	static T* m_instance;
};

template <typename T> T* Singleton<T>::m_instance = NULL;
	
#endif

