#pragma once 

#include "eventCallback.hpp"

#include <vector>

namespace irl
{
	template<typename T>
	class event;

	template <typename Result, typename... Args>
	class event<Result(Args...)>
	{
	public:
		std::vector<eventCallback<Result(Args...)>> callbacks;

		event() = default;

		void invoke(Args&&... args)
		{
			for(auto& callback : callbacks)
				callback(std::forward<Args>(args)...);
		}	
		void subscribe(eventCallback<Result(Args...)> callback)
		{
			callbacks.push_back(callback);
		}
		void clearListeners()
		{
			callbacks.clear();
		}

		void operator+= (eventCallback<Result(Args...)> callback)
		{
			callbacks.push_back(callback);
		}

	};

	template<typename T>
	class f_event;

	template <typename Result, typename... Args>
	class f_event<Result(Args...)>
	{
	public:
		std::vector<f_eventCallback<Result(Args...)>> callbacks;

		f_event() = default;

		void invoke(Args&... args)
		{
			for(auto& callback : callbacks)
				callback(std::forward<Args>(args)...);
		}	
		void subscribe(f_eventCallback<Result(Args...)> callback)
		{
			callbacks.push_back(callback);
		}
		void clearListeners()
		{
			callbacks.clear();
		}

		void operator+= (f_eventCallback<Result(Args...)> callback)
		{
			callbacks.push_back(callback);
		}

	};
} //namespace irl