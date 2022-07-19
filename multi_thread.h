#pragma once
#include <thread>
#include <vector>
#include <functional>
#include <utility>

class multi_thread {
public:

	//	thread�z��
	inline static std::vector<std::thread> m_threads;

	//	�ǉ�
	static void AddThread(std::function<void()> task) {
		m_threads.emplace_back([&] {task; });
	}

	//	�ꊇJoin
	static void Join() {
		for (auto& th : m_threads) {
			th.join();
		}
	}
};