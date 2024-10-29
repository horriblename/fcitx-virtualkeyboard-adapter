#include <cstdint>
#include <fcitx-utils/event.h>
#include <fcitx/addonfactory.h>
#include <fcitx/addoninstance.h>
#include <fcitx/addonmanager.h>
#include <fcitx/event.h>
#include <fcitx/instance.h>
#include <fcitx/userinterface.h>
#include <memory>

#ifndef _FCITX5_VIRTUALKEYBOARDADAPTER_H_
    #define _FCITX5_VIRTUALKEYBOARDADAPTER_H_

constexpr uint64_t VIRTUAL_KEYBOARD_ADAPTER_THROTTLE_USEC = 400000;
constexpr int MAGIC = 4107;

class VirtualKeyboardAdapter: public fcitx::AddonInstance {
  public:
    VirtualKeyboardAdapter(fcitx::Instance* instance, fcitx::EventLoop* loop) : instance(instance) {
        this->debouncer = loop->addTimeEvent(
            CLOCK_MONOTONIC,
            VIRTUAL_KEYBOARD_ADAPTER_THROTTLE_USEC,
            1000 /*I have no clue what this does */,
            [this](fcitx::EventSourceTime* _, uint64_t usec) { return false; }
        );
        this->debouncer->setOneShot();

        this->activationWatcher = this->instance->watchEvent(
            fcitx::EventType::InputContextInputMethodActivated,
            fcitx::EventWatcherPhase::PreInputMethod,
            [this](fcitx::Event& event) { this->onActivate(event); }
        );

        this->deactivationWatcher = this->instance->watchEvent(
            fcitx::EventType::InputContextInputMethodDeactivated,
            fcitx::EventWatcherPhase::PreInputMethod,
            [this](fcitx::Event& event) { this->onDeactivate(event); }
        );
    }

  private:
    enum DEBOUNCE_TARGET {
        NONE,
        ACTIVATE,
        DEACTIVATE,
    };

    fcitx::Instance* instance;
    DEBOUNCE_TARGET activeDebounce = NONE;
    std::unique_ptr<fcitx::EventSourceTime> debouncer;
    std::unique_ptr<fcitx::HandlerTableEntry<fcitx::EventHandler>> activationWatcher;
    std::unique_ptr<fcitx::HandlerTableEntry<fcitx::EventHandler>> deactivationWatcher;

    void onActivate(fcitx::Event&);
    void onDeactivate(fcitx::Event&);
    void onDebounceComplete(uint64_t usec);
};

class VirtualKeyboardAdapterFactory: public fcitx::AddonFactory {
    fcitx::AddonInstance* create(fcitx::AddonManager* manager) override {
        FCITX_UNUSED(manager);
        return new VirtualKeyboardAdapter(manager->instance(), manager->eventLoop());
    }
};

#endif // _FCITX5_VIRTUALKEYBOARDADAPTER_H_
