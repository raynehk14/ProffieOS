#ifndef FUNCTIONS_TRIGGER_H
#define FUNCTIONS_TRIGGER_H

// Usage: Trigger<EFFECT, FADE_IN_MILLIS, SUSTAIN_MILLIS, FADE_OUT_MILLIS>
// Normally returns 0, but when EFFECT occurs, it ramps up to 32768,
// stays there for SUSTAIN_MILLIS, then fades down to zero again.
// EFFECT: BladeEffectType
// FADE_IN_MILLIS: INTEGER
// SUSTAIN_MILLIS: INTEGER
// FADE_OUT_MILLIS: INTEGER
// return value: INTEGER
template<
  BladeEffectType EFFECT,
  class FADE_IN_MILLIS,
  class SUSTAIN_MILLIS,
  class FADE_OUT_MILLIS>
class Trigger {
  enum TriggerState {
    TRIGGER_ATTACK,
    TRIGGER_SUSTAIN,
    TRIGGER_RELEASE,
    TRIGGER_OFF
  };
 public:
  void run(BladeBase* blade) {
    fade_in_millis_.run(blade);
    sustain_millis_.run(blade);
    fade_out_millis_.run(blade);

    if (effect_.detect(blade)) {
      start_time_ = micros();
      state_ = TRIGGER_ATTACK;
    }
    if (state_ == TRIGGER_OFF) {
      value_ = 0;
      return;
    }
    uint32_t t = micros() - start_time_;

    while (true) {
      uint32_t micros_for_state = get_millis_for_state() * 1000;
      if (t < micros_for_state) {
	switch (state_) {
	case TRIGGER_ATTACK:
	  value_ = t * 32768.0 / micros_for_state;
	  return;
	case TRIGGER_SUSTAIN:
	  value_ = 32768;
	  return;
	case TRIGGER_RELEASE:
	  value_ = 32768 - t * 32768.0 / micros_for_state;
	  return;
	case TRIGGER_OFF:
	  value_ = 0;
	  return;
	}
      }
      state_++;
      t -= micros_for_state;
      start_time_ += micros_for_state;
    }
  }
  uint32_t get_millis_for_state() {
    switch (state_) {
    case TRIGGER_OFF: return 1000000;
    case TRIGGER_ATTACK: return fade_in_millis_.getInteger(0);
    case TRIGGER_SUSTAIN: return sustain_millis_.getInteger(0);
    case TRIGGER_RELEASE: return fade_out_millis_.getInteger(0);
    }
  }
  int getInteger(int led) const { return value_; }
 private:
  FADE_IN_MILLIS fade_in_millis_;
  SUSTAIN_MILLIS sustain_millis_;
  FADE_OUT_MILLIS fade_out_millis_;
  int value_;
  TriggerState state_;
  uint32_t start_time_;
  OneshotEffectDetector<EFFECT> effect_;
};

#endif
