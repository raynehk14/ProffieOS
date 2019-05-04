// This is a configuration file that I use to test proffieboard V1.
// This configuration has:
//   o Proffieboard V1 hardware.
//   o Three buttons
//   o A very weird 3-channel LED configuration. (TODO: Change to neopixels.)
// If you have a proffieboard V1 test rig, you may also want to use this configuration file.

#ifdef CONFIG_TOP

// Proffieboard config
#include "proffieboard_v1_config.h"

// Number of simultaneously connected blades.
// (For interchangeable blades, see the blades[] array.)
#define NUM_BLADES 1

// Number of buttons
#define NUM_BUTTONS 3

// Dual power buttons means that clicking AUX will also turn the saber on.
// If not defined, AUX will go to next preset when off.
#define DUAL_POWER_BUTTONS

// Volume, useful range is about 0-2000.
#define VOLUME 100

// If you have two 144 LED/m strips in your blade, connect
// both of them to bladePin and drive them in parallel.
const unsigned int maxLedsPerStrip = 196;

// This defines how sensitive the clash detection is.
#define CLASH_THRESHOLD_G 1.0

// Feature defines, these let you turn off large blocks of code
// used for debugging.
#define ENABLE_AUDIO
#define ENABLE_MOTION
// #define ENABLE_SNOOZE
#define ENABLE_WS2811
#define ENABLE_SERIAL

// Must be 20 characters or less.
#define BLE_PASSWORD "password"

// FASTLED is experimental and untested right now
// #define ENABLE_FASTLED
// #define ENABLE_WATCHDOG
#define ENABLE_SD
// #define ENABLE_SERIALFLASH
// #define ENABLE_SSD1306

// #define ENABLE_DEBUG

#endif

#ifdef CONFIG_PRESETS

typedef RandomFlicker<Rgb<200,200,200>, Rgb<40,40,40>> OnPulse;
typedef Pulsing<Rgb16<512,512,512>, Rgb16<50,50,50>, 3000> OffPulse;

Preset testing_presets[] = {
  { "TeensySF", "tracks/mars.wav", StyleNormalPtr<Stripes<1000, 1000, RED, GREEN, BLUE, CYAN, YELLOW, MAGENTA>, WHITE, 300, 800>(), "BLUE" },
  { "TeensySF", "tracks/mars.wav", StyleNormalPtr<RandomBlink<1000, RED, GREEN>, WHITE, 300, 800>(), "BLUE" },
  { "TeensySF", "tracks/mars.wav", StylePtr<FromFileStyle<>>(), "BLUE" },
#if 1
  { "TeensySF", "tracks/cantina.wav", StylePtr<InOutHelper<SimpleClash<
    Lockup<Blast<Blue,White>,
           AudioFlicker<Blue,White>,
           AudioFlicker<Green,White>
    >,White>, 300, 800>>(), "DEFAULT" },
  { "TeensySF", "tracks/cantina.wav", StyleNormalPtr<BLUE, WHITE, 300, 800>(), "BLUE" },
  { "TeensySF", "tracks/cantina.wav",
    StylePtr<InOutHelper<LocalizedClash<
      Lockup<
        BlastFadeout<
          OnSpark<
            HumpFlicker<Black,Blue,5>,
          White,
          250>,
        White>,
      AudioFlicker<OnSpark<Blue,White,200>,Black>>,White,40>,300,800,Black>> (),
    "ONOFF" },
  { "TeensySF", "tracks/cantina.wav",
    StylePtr<InOutHelper<SimpleClash<Lockup<Blast<OnSpark<HumpFlicker<Black,Blue,5>,White,250>,White>,AudioFlicker<OnSpark<Blue,White,200>,Black>>,White,40>,300,800,Black>> (),
    "ONOFF" },
  { "TeensySF", "tracks/cantina.wav", StyleNormalPtr<Sparkle<BLUE>, WHITE, 300, 800>(), "BLUE" },
  { "TeensySF", "tracks/cantina.wav", StyleNormalPtr<RED, WHITE, 300, 800>(), "RED" },
  { "TeensySF", "tracks/cantina.wav", StyleNormalPtr<GREEN, WHITE, 300, 800>(), "GREEN" },

  { "savant", "tracks/mars.wav",
    StyleNormalPtr<HumpFlicker<Yellow, Red ,50>, WHITE, 300, 800, RED>(), "HumpFlicker"},
  
  { "TeensySF", "tracks/cantina.wav",
    StyleNormalPtr<CYAN, WHITE, 3000, 8000>(),
    "ONOFF" },
  { "font02", "tracks/cantina.wav",
    StylePtr<InOutHelper<SimpleClash<Lockup<Blast<OnSpark<HumpFlicker<BLACK, BLUE, 5>, WHITE, 250>, YELLOW>, AudioFlicker<OnSpark<BLUE, WHITE, 200>, YELLOW>>, AudioFlicker<BLUE, YELLOW>, 200>, 400, 800>>(),
    "ONOFF" },
#endif
  { "font02", "tracks/cantina.wav", StyleRainbowPtr<300, 800>(),
    "=RainboW++\n++BladE++" },
  { "graflex4", "tracks/title.wav", StyleNormalPtr<CYAN, WHITE, 300, 800>(), "cyan" },
  { "graflex4", "tracks/cantina.wav", StyleNormalPtr<BLUE, RED, 300, 800>(), "blue" },
  { "caliban", "tracks/duel.wav", StyleFirePtr<RED, YELLOW>(), "red fire" },
  { "igniter/font2", "tracks/vader.wav", StyleNormalPtr<RED, WHITE, 300, 800>(), "red" },
  { "graflex5", "tracks/title.wav", StyleFirePtr<BLUE, CYAN>(), "blue fire" },
  { "igniter/font4", "tracks/duel.wav", StyleNormalPtr<GREEN, WHITE, 300, 800>(), "green" },
  { "graflex4", "tracks/duel.wav", StyleNormalPtr<WHITE, RED, 300, 800>(), "white" },
  { "graflex4", "tracks/walls.wav", StyleNormalPtr<YELLOW, BLUE, 300, 800>(), "yellow" },
  { "graflex4", "tracks/title.wav", StyleNormalPtr<MAGENTA, WHITE, 300, 800>(), "magenta" },
  { "graflex5", "tracks/cantina.wav", StyleStrobePtr<WHITE, RED, 15, 300, 800>(), "white" },
//  { "graflex5", "tracks/cantina.wav", &style_pov },

  { "charging", "tracks/duel.wav", &style_charging, "charging" },
};

BladeConfig blades[] = {
  // Testing configuration.
//  { 130000, StringBladePtr<Blue3mmLED>(), CONFIGARRAY(testing_presets) }
  { 130000, WS2811BladePtr<97, WS2811_800kHz, blade2Pin, PowerPINS<bladePowerPin1>>(), CONFIGARRAY(testing_presets) }
//  { 130000, WS281XBladePtr<131, blade2Pin, Color8::RGBw>(), CONFIGARRAY(testing_presets) },
};

#endif

#ifdef CONFIG_BUTTONS
// There are currently three available button classes:
// Button (standard momentary button)
// TouchButton (similar to momentary button, but reacts to touch).
// LatchingButton (on/off button, always controls ignition)

//LatchingButton PowerButton(BUTTON_POWER, powerButtonPin, "pow");
Button PowerButton(BUTTON_POWER, powerButtonPin, "pow");
Button AuxButton(BUTTON_AUX, auxPin, "aux");
Button Aux2Button(BUTTON_AUX2, aux2Pin, "aux2");
//TouchButton Aux2Button(BUTTON_AUX2, aux2Pin, 1700, "aux2");
#endif
