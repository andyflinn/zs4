#ifndef TAB_MUSIC_THEORY_H
#define TAB_MUSIC_THEORY_H

#include "tab_filebuf.h" 

#define NUMBER_OF_KEYS 12
#define MAX_NOTES_PER_CHORD 12
#define DESCENDING_SCALE_NOTE (1)
#define ASCENDING_SCALE_NOTE (1<<1)
#define SCALE_NOTE (DESCENDING_SCALE_NOTE|ASCENDING_SCALE_NOTE)
#define MAX_NAMES_PER_NOTE 8
#define DEFAULT_BEATS_PER_CYCLE 4

#define TYPE_NOTE "note"
#define TYPE_CHORD "chord"

class tab_music_theory : public tab_object
{
public:
	typedef enum {
		C,
		Cs,
		D,
		Ef,
		E,
		F,
		Fs,
		G,
		Af,
		A,
		Bf,
		B,
	SEMI_TONES_PER_OCTAVE} twelve_step; 

	typedef struct {
		twelve_step key;
		const char * name;
		const char * minor;
		const char * solfege;
		const char * solflow;
		const char * alt[MAX_NAMES_PER_NOTE];
	} twelve_tone;

	typedef struct {
		const char * name;
		const int semitone_range;
		const int * flags;
	} scale_definition;

	typedef struct {
		const char * description;
		const char * name;
		const int noteCount;
		const int note[MAX_NOTES_PER_CHORD];
	} chord_definition;

public:
	tab_music_theory();
	virtual ~tab_music_theory();

	static const strint third[];
	static const strint fourth[];
	static const strint fifth[];
	static const strint seventh[];

	static const strint majorscale[];
	static const strint majorsolfege[];

	// note/key stuff
	static const twelve_tone twelve[];
	static twelve_step getTone(const char * name);
	static twelve_step getTone(int val);
	
	static int midiNoteName(int note, tab_filebuf * name);
	static int midiNoteFitInRange(int note, int min=MIDI_NOTE_MIN, int max=MIDI_NOTE_MAX);
	static bool midiNoteBlackKey(int note);

	// scale stuff
	static const int pentaton_scale[];
	static const int western_major_scale[];
	static const int minor_harmonic_scale[];
	static const int minor_melodic_scale[];

	static const scale_definition scale[];
	static const scale_definition * scaleExists(const char * name); 

	// chord stuff
	static const chord_definition chord[];
	static int chordTypeOffset(const char * chord);
	static int chordTranspose(const char * chord, int by, tab_filebuf * trans, tab_filebuf * note, tab_filebuf * type, tab_filebuf * bass);
	static int chordChangeRoot(const char * chord, const char * new_root, tab_filebuf *new_chord, tab_filebuf * root, tab_filebuf * type, tab_filebuf * bass);
	static int chordChangeType(const char * chord, const char * new_type, tab_filebuf *new_chord, tab_filebuf * root, tab_filebuf * type, tab_filebuf * bass);
	static int chordChangeBass(const char * chord, const char * new_bass, tab_filebuf *new_chord, tab_filebuf * root, tab_filebuf * type, tab_filebuf * bass);
	static int chordRootTypeBass(const char * chord, tab_filebuf * note = NULL, tab_filebuf * type = NULL, tab_filebuf * bass = NULL);
	static twelve_step chordRootTone(const char * chord);
	static const chord_definition * chordExists(const char * chord);

	//static const int key_count;
	//static const char * key[];
	//static const int sharps[];

	static const char *MINOR;
	static const char *MAJOR;
	static const char *AUGMENTED;
	static const char *DIMINISHED;
	static const char *PERFECT;

	static const char *TONIC;
	static const char *SUPERTONIC;
	static const char *MEDIANT;
	static const char *SUBDOMINANT;
	static const char *DOMINANT;
	static const char *SUBMEDIANT;
	static const char *LEADINGTONE;

	static const double A4_FREQUENCY;
	static const int A4_MIDINOTE;
	static const int MIDDLE_C;
	static const double SEMITONE_UP;

	static const int MIDI_NOTE_MIN;
	static const int MIDI_NOTE_MAX;

	// instantiated stuff;


	// private stuff;
private:

};

#endif