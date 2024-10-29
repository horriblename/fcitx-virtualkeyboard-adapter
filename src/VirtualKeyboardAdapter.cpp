#include "VirtualKeyboardAdapter.hpp"

#include <cstdint>
#include <fcitx/addoninstance.h>
#include <fcitx/event.h>

FCITX_ADDON_FACTORY(VirtualKeyboardAdapterFactory);

void VirtualKeyboardAdapter::onActivate(fcitx::Event& event) {
    switch (this->activeDebounce) {
    case NONE:
        this->debouncer->setEnabled(true);
        this->debouncer->setOneShot();
        this->debouncer->setNextInterval(VIRTUAL_KEYBOARD_ADAPTER_THROTTLE_USEC);
        this->activeDebounce = ACTIVATE;
        break;
    case ACTIVATE:
        break;
    case DEACTIVATE:
        this->debouncer->setEnabled(false);
        this->activeDebounce = NONE;
        break;
    }
}

void VirtualKeyboardAdapter::onDeactivate(fcitx::Event& event) {
    switch (this->activeDebounce) {
    case NONE:
        this->debouncer->setEnabled(true);
        this->debouncer->setOneShot();
        this->debouncer->setNextInterval(VIRTUAL_KEYBOARD_ADAPTER_THROTTLE_USEC);
        this->activeDebounce = DEACTIVATE;
        break;
    case ACTIVATE:
        this->debouncer->setEnabled(false);
        this->activeDebounce = NONE;
        break;
    case DEACTIVATE:
        break;
    }
}

void VirtualKeyboardAdapter::onDebounceComplete(uint64_t) {
    int _;
    switch (this->activeDebounce) {
    case NONE:
        _ = system("notify-send 'debounce ended with NONE'");
        break;
    case ACTIVATE:
        _ = system(this->config.activateCmd.value().c_str());
        break;
    case DEACTIVATE:
        _ = system(this->config.deactivateCmd.value().c_str());
        break;
    }
    this->activeDebounce = NONE;
}
