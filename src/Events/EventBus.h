#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "../Logger/Logger.h"
#include "Event.h"
#include <memory>
#include <map>
#include <typeindex>
#include <list>
#include <functional>

//TODO: I do not like this, refactor pls
class IEventCallback {
    private:
        virtual void Call(Event& e) = 0;

    public:
      virtual ~IEventCallback() = default;

      void Execute(Event& e) {
        Call(e);
      }
};

template <typename TOwner, typename TEvent>
class EventCallback: public IEventCallback {
    private:
        typedef void (TOwner::*CallbackFunction)(TEvent&);

        TOwner* owner;
        CallbackFunction callbackFunction;

        virtual void Call(Event& e) override {
            std::invoke(callbackFunction, owner, static_cast<TEvent&>(e));
        }
        
    public:
        EventCallback(TOwner* owner, CallbackFunction callbackFunction) {
            this->owner = owner;
            this->callbackFunction = callbackFunction;
        }

        virtual ~EventCallback() override = default;
};

typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

class EventBus {
    private:
        std::shared_ptr<Logger> logger;

        std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

    public:
        EventBus(std::shared_ptr<Logger> l);
        ~EventBus();

        template <typename TEvent, typename TOwner>
        void SubscribeToEvent(TOwner* owner, void (TOwner::*callbackFunction)(TEvent&)) {
            if (!subscribers[typeid(TEvent)].get()) {
                subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
            }

            auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(owner, callbackFunction);
            subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
        }

        template <typename TEvent, typename ...TArgs>
        void EmitEvent(TArgs&& ...args) {
            auto handlers = subscribers[typeid(TEvent)].get();
            if (handlers) {
                for (auto it = handlers->begin(); it != handlers->end(); it++) {
                    auto handler = it->get();
                    TEvent event(std::forward<TArgs>(args)...);
                    handler->Execute(event);
                }
            }
        }

        void Reset();
};

#endif