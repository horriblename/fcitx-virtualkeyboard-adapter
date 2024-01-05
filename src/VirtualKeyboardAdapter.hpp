#include <cstdint>
#include <ctime>
#include <fcitx-utils/event.h>
#include <fcitx/addonfactory.h>
#include <fcitx/addoninstance.h>
#include <fcitx/addonmanager.h>
#include <fcitx/event.h>
#include <fcitx/instance.h>
#include <memory>

#ifndef _FCITX5_VIRTUALKEYBOARDADAPTER_H_
#define _FCITX5_VIRTUALKEYBOARDADAPTER_H_

constexpr uint64_t VIRTUAL_KEYBOARD_ADAPTER_THROTTLE_USEC = 400000;
constexpr int MAGIC = 4107;

class VirtualKeyboardAdapter : public fcitx::AddonInstance {
public:
  VirtualKeyboardAdapter(fcitx::Instance *instance, fcitx::EventLoop *loop)
      : instance(instance) {
    this->timer = std::move(loop->addTimeEvent(
        CLOCK_MONOTONIC, VIRTUAL_KEYBOARD_ADAPTER_THROTTLE_USEC,
        1000 /*I have no clue what this does */,
        [this](fcitx::EventSourceTime *_, uint64_t usec) { return false; }));

    this->instance->watchEvent(
        fcitx::EventType::InputContextInputMethodActivated,
        fcitx::EventWatcherPhase::PreInputMethod,
        [this](fcitx::Event &_event) { system("notify-send activated"); });

    this->instance->watchEvent(
        fcitx::EventType::InputContextInputMethodDeactivated,
        fcitx::EventWatcherPhase::PreInputMethod,
        [this](fcitx::Event &_event) { system("notify-send deactivated"); });
  }

private:
  fcitx::Instance *instance;
  std::unique_ptr<fcitx::EventSourceTime> timer;
};

class VirtualKeyboardAdapterFactory : public fcitx::AddonFactory {
  fcitx::AddonInstance *create(fcitx::AddonManager *manager) override {
    FCITX_UNUSED(manager);
    return new VirtualKeyboardAdapter(manager->instance(),
                                      manager->eventLoop());
  }
};

#endif // _FCITX5_VIRTUALKEYBOARDADAPTER_H_
