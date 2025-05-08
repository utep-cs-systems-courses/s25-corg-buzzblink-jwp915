#ifndef BUZZER_INCLUDED
#define BUZZER_INCLUDED

// === Musical Note Frequencies (in Timer Cycles for Buzzer) ===
#define F_3   0x2CB5  // 175 Hz
#define DB_4  0x1C25  // 277 Hz
#define D_4   0x1A95  // 294 Hz
#define EB_4  0x1914  // 311 Hz
#define E_4   0x17AC  // 330 Hz
#define F_4   0x1685  // 349 Hz

// === Buzzer Setup and Control ===
void buzzer_init();                         // Initialize buzzer hardware
void buzzer_set_period(short cycles);       // Set buzzer pitch

// === Tune Control and State Machines ===
void carry_State(unsigned char measure_, unsigned char notes_, unsigned char notes_play_);
void full_Tune(unsigned int notes_);

// === Predefined Measure Functions ===
void measure_1(unsigned int notes_);
void measure_2(unsigned int notes_);
void measure_3(unsigned int notes_);

// === Note Adjustment ===
void change_Notes_(short value);

#endif // BUZZER_INCLUDED
