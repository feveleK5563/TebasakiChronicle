#pragma once

namespace Define
{
	//ÉXÉNÉäÅ[Éì
	static const int ScreenWidth = 1280;
	static const int ScreenHeight = 720;
};

namespace Memory
{
	template<class T> void SafeDelete(T& t)
	{
		if (t != nullptr)
		{
			delete t;
			t = nullptr;
		}
	}

	template<class T> void SafeDeleteArr(T& t)
	{
		if (t != nullptr)
		{
			delete[] t;
			t = nullptr;
		}
	}
};