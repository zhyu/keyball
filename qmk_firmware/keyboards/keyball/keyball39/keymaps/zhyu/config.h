#pragma once

#ifdef RGBLIGHT_ENABLE
// #    define RGBLIGHT_EFFECT_BREATHING
// #    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
// #    define RGBLIGHT_EFFECT_SNAKE
// #    define RGBLIGHT_EFFECT_KNIGHT
// #    define RGBLIGHT_EFFECT_CHRISTMAS
// #    define RGBLIGHT_EFFECT_STATIC_GRADIENT
// #    define RGBLIGHT_EFFECT_RGB_TEST
// #    define RGBLIGHT_EFFECT_ALTERNATING
// #    define RGBLIGHT_EFFECT_TWINKLE

// effect speed: mode 0=1 < 2=3 < 4=5
// hue change direction: 0=2=4 (red -> purple -> blue -> green -> yellow -> red), 1=3=5 (red -> yellow -> green -> blue -> purple -> red)
// ref: https://github.com/qmk/qmk_firmware/blob/46dedfaaa479332159fde74481f74d35215388b5/quantum/rgblight/rgblight.c#L1220-L1243
#    define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_EFFECT_RAINBOW_SWIRL + 4)
#    define RGBLIGHT_SLEEP
#endif

#define TAP_CODE_DELAY 5

#ifdef POINTING_DEVICE_ENABLE
#    define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#endif // POINTING_DEVICE_ENABLE

// double click to lock one shot layers
#define ONESHOT_TAP_TOGGLE 2

#define KEYBALL_CPI_DEFAULT 1000

// enabling SPLIT_USB_DETECT would cause issues with the USB hub.
// It's enabled by default to make the default firmware compatible with different ARM boards,
// ref: https://github.com/Yowkees/keyball/issues/169
#ifdef SPLIT_USB_DETECT
#    undef SPLIT_USB_DETECT
#    ifdef SPLIT_USB_TIMEOUT
#        undef SPLIT_USB_TIMEOUT
#    endif
#endif
