#include QMK_KEYBOARD_H
#include <eeconfig.h>
#include "twpair_on_jis.h"
#include "satt.h"
#include "keymap_japanese.h"
#include "os_detection.h"


// JIS & ANSI swap functions
user_config_t user_config = {};

void load_persistent(void) {
    user_config.raw = eeconfig_read_user();
}

void save_persistent(void) {
    eeconfig_update_user(user_config.raw);
}

void eeconfig_init_user(void) {
    save_persistent();
}

void keyboard_post_init_user(void) {
    if (is_keyboard_master()) {
        load_persistent();
    }
}

void set_keyboard_lang_to_jis(bool set_jis){
    if ( user_config.jis == set_jis){ return; }
    if (set_jis){
        user_config.jis = 1;
    } else {
        user_config.jis = 0;
    }
    save_persistent();
}


__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // JIS & ANSI swap
    case CK_EnJIS:
      if (record->event.pressed) {
        set_keyboard_lang_to_jis(true);
      }
      return false;
    case CK_EnUS:
      if (record->event.pressed) {
        set_keyboard_lang_to_jis(false);
      }
      return false;
    // Swap input
    case ZKHK:
      if (record->event.pressed) {
        switch (detected_host_os()) {
          case OS_MACOS:
          case OS_IOS:
            if (get_mods() & MOD_MASK_CTRL) {
              tap_code(KC_SPC);
            } else {
              register_mods(MOD_MASK_CTRL);
              tap_code(KC_SPC);
              unregister_mods(MOD_MASK_CTRL);
            }
            break;
          default:
            if (user_config.jis){
              tap_code(JP_ZKHK);
            } else {
              if (get_mods() & MOD_MASK_ALT) {
                tap_code(KC_GRV);
              } else {
                register_mods(MOD_MASK_ALT);
                tap_code(KC_GRV);
                unregister_mods(MOD_MASK_ALT);
              }
            }
        }
      }
      return false;
    default:
      if (user_config.jis){
        return twpair_on_jis(keycode, record);
      } else {
        return process_record_keymap(keycode, record);
      }
  }
}
