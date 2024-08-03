#ifndef __INPUT_EVENT_USB_HID__
#define __INPUT_EVENT_USB_HID__

#include <cstdint>
#include <linux/input-event-codes.h>
#include <unordered_map>
#include <usb_hid_keys.h>
static std::unordered_map<std::uint8_t, std::uint8_t> input_event_usb_hid_map =
    {
        {KEY_A, usb_hid_keys::_KEY_A}, {KEY_B, usb_hid_keys::_KEY_B},
        {KEY_C, usb_hid_keys::_KEY_C}, {KEY_D, usb_hid_keys::_KEY_D},
        {KEY_E, usb_hid_keys::_KEY_E}, {KEY_F, usb_hid_keys::_KEY_F},
        {KEY_G, usb_hid_keys::_KEY_G}, {KEY_H, usb_hid_keys::_KEY_H},
        {KEY_I, usb_hid_keys::_KEY_I}, {KEY_J, usb_hid_keys::_KEY_J},
        {KEY_K, usb_hid_keys::_KEY_K}, {KEY_L, usb_hid_keys::_KEY_L},
        {KEY_M, usb_hid_keys::_KEY_M}, {KEY_N, usb_hid_keys::_KEY_N},
        {KEY_O, usb_hid_keys::_KEY_O}, {KEY_P, usb_hid_keys::_KEY_P},
        {KEY_Q, usb_hid_keys::_KEY_Q}, {KEY_R, usb_hid_keys::_KEY_R},
        {KEY_S, usb_hid_keys::_KEY_S}, {KEY_T, usb_hid_keys::_KEY_T},
        {KEY_U, usb_hid_keys::_KEY_U}, {KEY_V, usb_hid_keys::_KEY_V},
        {KEY_W, usb_hid_keys::_KEY_W}, {KEY_X, usb_hid_keys::_KEY_X},
        {KEY_Y, usb_hid_keys::_KEY_Y}, {KEY_Z, usb_hid_keys::_KEY_Z},

};

#endif
