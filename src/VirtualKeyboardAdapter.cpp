#include "VirtualKeyboardAdapter.hpp"

#include <cstdint>
#include <fcitx/addoninstance.h>
#include <fcitx/event.h>

FCITX_ADDON_FACTORY(VirtualKeyboardAdapterFactory);

void VirtualKeyboardAdapter::onActivate(fcitx::Event& event) {
    switch (this->activeDebounce) {
    case NONE:
        this->debouncer->setEnabled(true);
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
    switch (this->activeDebounce) {
    case NONE:
        system("notify-send 'debounce ended with NONE'");
        break;
    case ACTIVATE:
        system("notify-send 'activate'");
        break;
    case DEACTIVATE:
        system("notify-send 'deactivate'");
        break;
    }
}
