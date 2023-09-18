#pragma once
#include "../../Types.hpp"

namespace hexen::engine::core::threading
{
	class TaskScheduler;
	struct Task
	{
	private:
	public:
		Task() = default;
		template<class T, typename Ret, typename... Args>
		bool bind(T *object, Ret (T::*method)(Args...), Args... args)
		{
			auto methodDelegate = std::shared_ptr<core::MethodDelegate<T, Ret, Args...>>(new core::MethodDelegate(object, method, args...));
			delegate = std::reinterpret_pointer_cast<BaseDelegate<std::any>>(methodDelegate);

			if (delegate == nullptr)
			{
				return false;
			}

			return true;
		}
		template<typename Ret, typename... Args>
		bool bind(Ret (*callableFunction)(Args...), Args... args)
		{
			auto functionDelegate = std::shared_ptr<core::FunctionDelegate<Ret, Args...>>(new core::FunctionDelegate(callableFunction, args...));
			delegate = std::reinterpret_pointer_cast<BaseDelegate<std::any>>(functionDelegate);

			if (delegate == nullptr)
			{
				return false;
			}

			return true;
		}


		template<class T, typename Ret, typename... Args>
		HEXEN_INLINE bool operator==(Ret (T::*callableMethod)(Args...))
		{
			if (delegate == nullptr)
			{
				return false;
			}

			std::any object = callableMethod;
			return delegate->getId() == object.type().hash_code();
		}

		template<class T, typename Ret, typename... Args>
		HEXEN_INLINE bool operator!=(Ret (T::*callableMethod)(Args...))
		{
			if (delegate == nullptr)
			{
				return false;
			}

			std::any object = callableMethod;
			return delegate->getId() != object.type().hash_code();
		}
		template<typename Ret, typename... Args>
		HEXEN_INLINE bool operator==(Ret (*callableFunction)(Args...))
		{
			if (delegate == nullptr)
			{
				return false;
			}

			std::any object = callableFunction;
			return delegate->getId() == object.type().hash_code();
		}

		template<typename Ret, typename... Args>
		HEXEN_INLINE bool operator!=(Ret (*callableFunction)(Args...))
		{
			if (delegate == nullptr)
			{
				return false;
			}

			std::any object = callableFunction;
			return delegate->getId() != object.type().hash_code();
		}

		template<typename T, typename... Args>
		bool bind(T *object, Args... args)
		{
			auto functorDelegate = std::shared_ptr<core::FunctorDelegate<T, Args...>>(new core::FunctorDelegate(object, args...));
			delegate = std::reinterpret_pointer_cast<BaseDelegate<std::any>>(functorDelegate);

			if (delegate == nullptr)
			{
				return false;
			}

			return true;
		}


		template<typename T, typename... Args>
		HEXEN_INLINE bool operator==(T *functor)
		{
			if (delegate == nullptr)
			{
				return false;
			}

			std::any object = functor;
			return delegate->getId() == object.type().hash_code();
		}

		template<typename T, typename... Args>
		HEXEN_INLINE bool operator!=(T *functor)
		{
			if (delegate == nullptr)
			{
				return false;
			}

			std::any object = functor;
			return delegate->getId() != object.type().hash_code();
		}


		void execute() const
		{
			if (delegate != nullptr)
			{
				delegate->execute();
			}
		}

		std::shared_ptr<BaseDelegate<std::any>> delegate {nullptr};
		vptr ArgumentsData {};
	};

	enum class TaskPriority
	{
		High,
		Normal,
	};
}// namespace hexen::engine::core::threading
