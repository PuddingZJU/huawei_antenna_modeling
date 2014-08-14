//File discription:定义了一个单件类
//By：ant（http://www.cppblog.com/ant/）

#ifndef SINGLETON_H
#define SINGLETON_H

//#define NOMINMAX
#include <windows.h>

namespace Ant
{

#define CLASS_UNCOPYABLE(classname) \
private: \
	classname(const classname&); \
	classname& operator=(const classname&);

class Mutex {
	CLASS_UNCOPYABLE(Mutex)
public:
	Mutex() :_cs() { InitializeCriticalSection(&_cs); }
	~Mutex() { DeleteCriticalSection(&_cs); }
	void lock() { EnterCriticalSection(&_cs); }
	void unlock() { LeaveCriticalSection(&_cs); }
private:
	CRITICAL_SECTION _cs;
};

class Lock {
	CLASS_UNCOPYABLE(Lock)
public:
	explicit Lock(Mutex& cs) :_cs(cs) { _cs.lock(); }
	~Lock() { _cs.unlock(); }
private:
	Mutex& _cs;
};



template<class T>
class Singleton {
	CLASS_UNCOPYABLE(Singleton)

public:
	static T& Instance() { // Unique point of access
		if (0 == _instance) {
			Lock lock(_mutex);
			if (0 == _instance) {
				_instance = new T();
				atexit(Destroy);
			}
		}
		return *_instance;
	}

protected:
	Singleton(){}
	~Singleton(){}

protected:
	static void Destroy() { // Destroy the only instance
		if ( _instance != 0 ) {
			delete _instance;
			_instance = 0;
		}
	}
	static Mutex _mutex;
	static T * volatile _instance; // The one and only instance
};

template<class T>
Mutex Singleton<T>::_mutex;

template<class T>
T * volatile Singleton<T>::_instance = 0;

}

#endif SINGLETON_H