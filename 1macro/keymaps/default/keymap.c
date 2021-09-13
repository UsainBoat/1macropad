/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H


bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
uint8_t encoder_layer_var = 0;
uint8_t rgb_status = 0;
bool oled_boot_status = true;
uint16_t oled_boot_timer = 0;

enum layers {
  _NUMPAD,
  _GREEK,
  _MOUSE,
  _ADJUST
};

enum encoder_names {
  _LEFT,
  _MIDDLE,
  _RIGHT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Numpad
   * ,---------------------------.
   * |   7  |   8  |   9  |  /   |
   * |------+------+------+------|
   * |   4  |   5  |   6  |  -   |
   * |------+------+------+------|
   * |   1  |   2  |   2  |  +   |
   * |------+------+------+------|
   * |   0  |   .  |   *  |Enter |
   * `---------------------------'
   */
    [_NUMPAD] = LAYOUT(
        KC_P7, KC_P8, KC_P9, KC_PSLS,
        KC_P4, KC_P5, KC_P6, KC_PMNS,
        KC_P1, KC_P2, KC_P3, KC_PPLS,
        KC_P0, KC_PDOT, KC_PAST, KC_PENT
    ),
    /* Greek
     * ,---------------------------.
     * |   π  |   ϕ  |   ϱ  |      |
     * |------+------+------+------|
     * |   θ  |   σ  |   Λ  |   Δ  |
     * |------+------+------+------|
     * |   α  |   Β  |      |      |
     * |------+------+------+------|
     * |   °  |      |      |      |
     * `---------------------------'
     */
    [_GREEK] = LAYOUT(
        UC(0x03C0), UC(0x03D5), UC(0x03F1), _______,
        UC(0x03B8), UC(0x03C3), UC(0x039B), UC(0x0394),
        UC(0x03B1), UC(0x0392), _______, _______,
        UC(0x00B0), _______, _______, _______
    ),
    /* Mouse
     * ,---------------------------.
     * |      |      |      |      |
     * |------+------+------+------|
     * |      |      |      |      |
     * |------+------+------+------|
     * |      |MousUp|      |      |
     * |------+------+------+------|
     * |MousLf|MousDn|MousRt|      |
     * `---------------------------'
     */
    [_MOUSE] = LAYOUT(
        RESET  , _______, _______, UC_MOD,
        _______, _______, _______, _______,
        _______, KC_MS_U, _______, _______,
        KC_MS_L, KC_MS_D, KC_MS_R, _______
    ),
    /* Adjust
     * ,---------------------------.
     * | Reset|RGBTog|      |Unicod|
     * |------+------+------+------|
     * |ModeRv|ModeFw|      |      |
     * |------+------+------+------|
     * |      |      |      |      |
     * |------+------+------+------|
     * |      |      |      |      |
     * `---------------------------'
     */
    [_ADJUST] = LAYOUT(
        RESET  , RGB_TOG, _______, UC_MOD,
        RGB_RMOD, RGB_MOD, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______
    ),
};

/* Alt Tab Timer */
void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 750) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

/* Encoder Setup */
void encoder_update_user(uint8_t index, bool clockwise){
  switch (biton32(layer_state)) {
    case _ADJUST:
      if(index == _LEFT) {
          if(clockwise) {
            rgblight_increase_hue();
          } else {
            rgblight_decrease_hue();
          }
      } else if(index == _MIDDLE) {
        if(clockwise) {
          rgblight_increase_sat();
        } else {
          rgblight_decrease_sat();
        }
      } else if(index == _RIGHT) {
        if (clockwise) {
          if(encoder_layer_var < 3) {
            encoder_layer_var++;
          } else {
            encoder_layer_var = 0;
          }
        } else {
          if(encoder_layer_var > 0) {
            encoder_layer_var--;
          } else {
          encoder_layer_var = 3;
          }
        }
        layer_clear();
        layer_on(encoder_layer_var);
      }
      break;
    default:
      if(index == _LEFT) {
        is_alt_tab_active = true;
        alt_tab_timer = timer_read();
        register_code(KC_LALT);
        if(clockwise) {
          tap_code(KC_TAB);
        } else {
          tap_code16(S(KC_TAB));
        }
      } else if(index == _MIDDLE) {
        if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
      } else if(index == _RIGHT) {
        if (clockwise) {
          if(encoder_layer_var < 3) {
            encoder_layer_var++;
          } else {
            encoder_layer_var = 0;
          }
        } else {
          if(encoder_layer_var > 0) {
            encoder_layer_var--;
          } else {
          encoder_layer_var = 3;
          }
        }
        layer_clear();
        layer_on(encoder_layer_var);
      }
      break;
  }
}

/* RGB Backlight setting */
// Backlight array for default numpad layer
// const rgblight_segment_t PROGMEM numpad_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {0, 1, HSV_RED}       // Light all LEDs red
// );
// // Backlight array for greek layer
// const rgblight_segment_t PROGMEM greek_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {0, 1, HSV_GREEN}       // Light all LEDs green
// );
// // Backlight array for mouse layer
// const rgblight_segment_t PROGMEM mouse_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {0, 1, HSV_ORANGE}       // Light all LEDs blue
// );
// // Backlight array for adjust layer
// const rgblight_segment_t PROGMEM adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {0, 1, HSV_BLUE}       // Light all LEDs blue
// );

// Array of layers for RGB backlight control. Later layers take precedence
// const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
//     adjust_layer,
//     mouse_layer,
//     greek_layer,
//     numpad_layer
// );
// Enable the LED layers
// void keyboard_post_init_user(void) {
//     rgblight_layers = my_rgb_layers;
// }
// // Set backlight colors to change based on layer
// layer_state_t layer_state_set_user(layer_state_t state) {
//   if (!rgblight_is_enabled()) {
//     rgblight_enable();
//   } else {
//     rgblight_set_layer_state(0, layer_state_cmp(state, 3));
//     rgblight_set_layer_state(1, layer_state_cmp(state, 2));
//     rgblight_set_layer_state(2, layer_state_cmp(state, 1));
//     rgblight_set_layer_state(3, layer_state_cmp(state, 0));
//   }
//   return state;
// }

// OLED Settings
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(PSTR("\n\n"), false);
    oled_write_P(qmk_logo, false);
}

void oled_task_user(void) {
    if(oled_boot_status){
      render_logo();
      if (timer_elapsed(oled_boot_timer) > 5000) {
        oled_boot_status = false;
      }
    } else {
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _NUMPAD:
            oled_write_P(PSTR("Numpad\n\n"), false);
            oled_write_P(PSTR("  AltTab  Vol  Layer\n"), false);
            oled_write_ln_P(PSTR("| 7  | 8  | 9  | /  |"), false);
            oled_write_ln_P(PSTR("| 4  | 5  | 6  | -  |"), false);
            oled_write_ln_P(PSTR("| 1  | 2  | 3  | +  |"), false);
            oled_write_ln_P(PSTR("| 0  | .  | *  |Ent |"), false);
            break;
        case _GREEK:
            oled_write_P(PSTR("Greek Letters\n\n"), false);
            oled_write_P(PSTR("  AltTab  Vol  Layer\n"), false);
            oled_write_ln_P(PSTR("| Pi | Phi| Rho|    |"), false);
            oled_write_ln_P(PSTR("|Thet| Sig| Lam| Del|"), false);
            oled_write_ln_P(PSTR("| Alp|Beta|    |    |"), false);
            oled_write_ln_P(PSTR("| Deg|    |    |    |"), false);
            break;
        case _MOUSE:
            oled_write_P(PSTR("Mouse Keys\n\n"), false);
            oled_write_P(PSTR("  AltTab  Vol  Layer\n"), false);
            oled_write_ln_P(PSTR("|    |    |    |    |"), false);
            oled_write_ln_P(PSTR("|    |    |    |    |"), false);
            oled_write_ln_P(PSTR("|    |M_Up|    |    |"), false);
            oled_write_ln_P(PSTR("|M_Lf|M_Dn|M_Rt|    |"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n\n"), false);
            oled_write_P(PSTR("  AltTab  Vol  Layer\n"), false);
            oled_write_ln_P(PSTR("|Rst |RGB |    |UniM|"), false);
            oled_write_ln_P(PSTR("|RGBR|RGBF|    |    |"), false);
            oled_write_ln_P(PSTR("|    |    |    |    |"), false);
            oled_write_ln_P(PSTR("|    |    |    |    |"), false);
            break;
        default:
            render_logo();
    }
  }

    //oled_write_P(PSTR("1\n2\n3\n4\n5\n6"), false);
}
