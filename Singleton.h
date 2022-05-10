#pragma once
#include <cassert>
#include <mutex>

class Singleton_static
{
private:
	Singleton_static() = default;
	~Singleton_static() = default;
public:
	Singleton_static(const Singleton_static&) = delete;
	Singleton_static& operator = (const Singleton_static&) = delete;
	Singleton_static(Singleton_static&&) = delete;
	Singleton_static& operator=(Singleton_static&&) = delete;

	static Singleton_static& get_instance() {
		static Singleton_static instance;
		return instance;
	}
};

class SingletonFinalizer {
public:
    using FinalizerFunc = void(*)();
    static void addFinalizer(FinalizerFunc func);
    static void finalize();
};

template <typename T>
class Singleton final {
public:
    static T& get_instance() {
        std::call_once(initFlag, create);
        assert(instance);
        return *instance;
    }

private:
    static void create() {
        instance = new T;
        SingletonFinalizer::addFinalizer(&Singleton<T>::destroy);
    }

    static void destroy() {
        delete instance;
        instance = nullptr;
    }

    static std::once_flag initFlag;
    static T* instance;
};

template <typename T> std::once_flag Singleton<T>::initFlag;
template <typename T> T* Singleton<T>::instance = nullptr;

