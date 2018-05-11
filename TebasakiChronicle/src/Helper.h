#pragma once

namespace Memory
{
	template<class T>void SafeDelete(T& t)
	{
		if (t != nullptr)
		{
			delete t;
			t = nullptr;
		}
	}


}