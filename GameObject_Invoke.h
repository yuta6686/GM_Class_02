#pragma once
#include "gameObject.h"
struct INVOKE {
	int m_DelayCountMax = 0;
	int m_DelayCounter = 0;
	bool m_IsInvoke = false;
};
template <class T>
class GameObject_Invoke :
    public GameObject
{
protected:
	static std::vector<INVOKE> m_Invokes;


	typedef void(T::* MAMBER_FUNC)();
	static std::vector<MAMBER_FUNC> m_FuncList;


	//	m_DelayCount ,m_DelayCounter‚ðqueue‚É‚µ‚ÄŽg‚¤B
	static void InvokeUpdate() {

		if (m_FuncList.empty() ||
			m_Invokes.empty())return;

		//	Œã‚ë‚©‚ç‰ñ‚·
		for (int i = m_Invokes.size() - 1; i >= 0; i--) {
			if (!m_Invokes[i].m_IsInvoke)continue;
			if (m_Invokes[i].m_DelayCounter < m_Invokes[i].m_DelayCountMax) {
				m_Invokes[i].m_DelayCounter++;
			}
			else {
				m_Invokes[i].m_DelayCounter = 0;
				m_Invokes[i].m_IsInvoke = false;
				(this->*m_FuncList[i])();

				m_Invokes.erase(m_Invokes.begin() + i);
				m_FuncList.erase(m_FuncList.begin() + i);

			}
		}
	}
public:
	static void Init() {};
	static void Uninit() {};
	static void Update() { InvokeUpdate(); };
	static void Draw() {};


	template <class V>
	static void Invoke(V(T::* func)(), int delay) {
		m_FuncList.push_back(func);
		m_Invokes.push_back({ delay,0,true });
	}
};


