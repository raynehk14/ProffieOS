#ifndef STYLES_SEQUENCE_H
#define STYLES_SEQUENCE_H

// usage: Sequence<COLOR1, COLOR2, int millis_per_bits, int bits, 0b0000000000000000, ....>
// COLOR1: COLOR
// COLOR2: COLOR
// millis_per_bit: millseconds spent on each bit
// bits: number of bits before we loop around to the beginning
// 0b0000000000000000: 16-bit binary numbers containing the actual sequence.
//
// Shows COLOR1 if the current bit in the sequence is 1, COLOR2 otherwise.
// The number of 16-bit binary numbers should be at least |bits| / 16, rounded up.
// Note that if not all bits are used within the 16-bit number.
// Example, a red SOS pattern:
// Sequence<RED, BLACK, 100, 37, 0b0001010100011100, 0b0111000111000101, 0b0100000000000000>

template<class COLOR1, class COLOR2, int millis_per_bit, int bits, int ... sequence >
class Sequence {
public:
  void run(BladeBase* blade) {
    static uint16_t sequence_[] = { sequence... };
    c1_.run(blade);
    c2_.run(blade);

    uint32_t now = millis();
    uint32_t bit = (now / millis_per_bit) % std::min<size_t>(bits, sizeof...(sequence) * 16);
    on_ = !!((sequence_[bit >> 4] >> ((~bit) & 0xf)) & 1);
  }
  OverDriveColor getColor(int led) {
    return on_ ? c1_.getColor(led) : c2_.getColor(led);
  }
  
private:
  COLOR1 c1_;
  COLOR2 c2_;
  bool on_;
};

#endif
