
#ifndef H_BZRMUSIC_QIT
#define H_BZRMUSIC_QIT

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * AUX functionality for a simple buzzer.
 * Can play simpel music
 */

#include "pitches.h"
#include "qit_sensor.h"

namespace qit::aux {

// Using a template because generally speaking one only needs one buzzer
// Multiple are OK but they will duplicate the same class
// However, as one probably only uses 1 active buzzer this doesn't matter
template <int T_PIN> class BuzzerMusic : public Sensor {
public:
  // What pin on the board is going to be used?
  const int pin = T_PIN;
  
  // Keep track of which octave is being used and how short or long a note
  // should be.played
  int cur_accord = 3;
  int cur_note_length = 500;

  void initialize() {
    ::pinMode(pin, OUTPUT);
  }

  // Play a tone inline because we don't want an extra JMP
  void tone(int t, int l = 0, bool wait = false) {
    // Global namespace tone
    ::tone(pin, t, l);
    if (wait)
      delay(l);
  }

  inline void untone() {
    ::noTone(pin);
  }

  inline void tone(char w, int l = 0, bool wait = false)
  {
    if (l == 0) l = cur_note_length;
    switch(w)
    {
      // Notes
      case 'A': this->tone(ACORD[cur_accord][NOTE_A], l, wait); break;
      case 'B': this->tone(ACORD[cur_accord][NOTE_B], l, wait); break;
      case 'C': this->tone(ACORD[cur_accord][NOTE_C], l, wait); break;
      case 'D': this->tone(ACORD[cur_accord][NOTE_D], l, wait); break;
      case 'E': this->tone(ACORD[cur_accord][NOTE_E], l, wait); break;
      case 'F': this->tone(ACORD[cur_accord][NOTE_F], l, wait); break;
      case 'G': this->tone(ACORD[cur_accord][NOTE_G], l, wait); break;
      // Silence is important in music
      case ' ': delay(l); break;
      // Play a random note
      case 'R': this->tone(ACORD[cur_accord][rand() % 7], l, wait); break;
      // Change the octave
      case '+': 
        this->cur_accord ++; 
        if (this->cur_accord >= 7) { this->cur_accord = 7; } 
        break;
      case '-': 
        this->cur_accord --; 
        if (this->cur_accord < 0) { this->cur_accord = 0; }
        break;
      // Change the note length (1/8, 1/4, 1/2, 1/1)
      case '0': this->cur_note_length = 1000 / 1; break;
      case '1': this->cur_note_length = 1000 / 2; break;
      case '2': this->cur_note_length = 1000 / 4; break;
      case '4': this->cur_note_length = 1000 / 8; break;
      case 'r': this->cur_note_length = rand() % 1001; break;
      case '_': delay(rand() % 1001); break;
      default: break;
    }
  }

  // Play the song or random sequence
  void play(String what) { // ! one can also use String.c_str() to call
                           // the const char version
    for (int i = 0; i < what.length(); i++)
      this->tone(what[i], 0, true);
  }
  // const char so we dont use costly memory for fixed songs
  void play(const char from[]) {
    size_t length = ::strlen(from);
    for (unsigned int i = 0; i < length; i++)
      this->tone(from[i], 0, true);
  }

};

}

#endif
