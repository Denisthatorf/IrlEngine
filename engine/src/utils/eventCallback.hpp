#pragma once

#include <functional>
#include <memory>

namespace irl
{
    template <typename>
    class eventCallback;

    template <typename Result, typename... Arguments>
    class eventCallback<Result (Arguments...)>
    {
    public:
        template <typename Functor>
        eventCallback (Functor f)
        {
            if (sizeof (FunctorHolder<Functor, Result, Arguments...>) <= sizeof (stack))
            {
                functorHolderPtr = (decltype (functorHolderPtr)) std::addressof (stack);
                new (functorHolderPtr) FunctorHolder<Functor, Result, Arguments...> (f);
            }
            else
            {
                functorHolderPtr = new FunctorHolder<Functor, Result, Arguments...> (f);
            }
        }

        eventCallback (const eventCallback& other)
        {
            if (other.functorHolderPtr != nullptr)
            {
                if (other.functorHolderPtr == (decltype (other.functorHolderPtr)) std::addressof (other.stack))
                {
                    functorHolderPtr = (decltype (functorHolderPtr)) std::addressof (stack);
                    other.functorHolderPtr->copyInto (functorHolderPtr);
                }
                else
                {
                    functorHolderPtr = other.functorHolderPtr->clone();
                }
            }
        }

        eventCallback& operator= (eventCallback const& other)
        {
            if (functorHolderPtr != nullptr)
            {
                if (functorHolderPtr == (decltype (functorHolderPtr)) std::addressof (stack))
                    functorHolderPtr->~FunctorHolderBase();
                else
                    delete functorHolderPtr;

                functorHolderPtr = nullptr;
            }

            if (other.functorHolderPtr != nullptr)
            {
                if (other.functorHolderPtr == (decltype (other.functorHolderPtr)) std::addressof (other.stack))
                {
                    functorHolderPtr = (decltype (functorHolderPtr)) std::addressof (stack);
                    other.functorHolderPtr->copyInto (functorHolderPtr);
                }
                else
                {
                    functorHolderPtr = other.functorHolderPtr->clone();
                }
            }

            return *this;
        }

        eventCallback() = default;

        ~eventCallback()
        {
            if (functorHolderPtr == (decltype (functorHolderPtr)) std::addressof (stack))
                functorHolderPtr->~FunctorHolderBase();
            else
                delete functorHolderPtr;
        }

        Result operator() (Arguments&&... args) const
        {
            return (*functorHolderPtr) (std::forward<Arguments> (args)...);
        }

    private:
        template <typename ReturnType, typename... Args>
        struct FunctorHolderBase
        {
            virtual ~FunctorHolderBase() {}
            virtual ReturnType operator()(Args&&...) = 0;
            virtual void copyInto (void*) const = 0;
            virtual FunctorHolderBase<Result, Arguments...>* clone() const = 0;
        };

        template <typename Functor, typename ReturnType, typename... Args>
        struct FunctorHolder final : FunctorHolderBase<Result, Arguments...>
        {
            FunctorHolder (Functor func) : f (func) {}

            ReturnType operator()(Args&&... args) override
            {
                return f (std::forward<Arguments> (args)...);
            }

            void copyInto (void* destination) const override
            {
                new (destination) FunctorHolder (f);
            }

            FunctorHolderBase<Result, Arguments...>* clone() const override
            {
                return new FunctorHolder (f);
            }

            Functor f;
        };

        typename std::aligned_storage<32>::type stack;
        FunctorHolderBase<Result, Arguments...>* functorHolderPtr = nullptr;
    };


    template <typename>
    class f_eventCallback;

    template <typename Result, typename... Arguments>
    class f_eventCallback<Result (Arguments...)>
    {
    public:
        template <typename Functor>
        f_eventCallback (Functor f)
            : functionPtr  (f)
        {}

        f_eventCallback() = default;

        Result operator() (Arguments&&... args) const
        {
            return functionPtr (std::forward<Arguments> (args)...);
        }

        Result(*functionPtr)(Arguments...) = nullptr;
    };
    
} // namespace irl