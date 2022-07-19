#pragma once
#include <thread>
#include <vector>
#include <functional>
#include <utility>

class multi_thread {
public:

	//	thread”z—ñ
	inline static std::vector<std::thread> m_threads;

	//	’Ç‰Á
	static void AddThread(std::function<void()> task) {
		m_threads.emplace_back([&] {task; });
	}

	//	ˆêŠ‡Join
	static void Join() {
		for (auto& th : m_threads) {
			th.join();
		}
	}
};