#include "tab_music_theory.h"
#include <math.h>

//const int tab_music_theory::key_count = 12;

/*
const char * tab_music_theory::key[] = {
"C", "C",
"C#", "Db",
"D", "D",
"Eb", "D#",
"E", "E",
"F", "F",
"F#", "F#",
"G", "G",
"Ab", "G#",
"A", "A",
"Bb", "A#",
"B", "B",
NULL};
*/

/*
const int tab_music_theory::sharps[] = {
	0,
	-5,
	2,
	-3,
	4,
	-1,
	6,
	1,
	-4,
	3,
	-2,
	5,
0}; 
*/

const strint tab_music_theory::third[] = {{MAJOR,4},{MINOR,3},{NULL,0}};
const strint tab_music_theory::fourth[] = {{PERFECT,5},{DIMINISHED,4},{AUGMENTED,6},{NULL,0}};
const strint tab_music_theory::fifth[] = {{PERFECT,7},{DIMINISHED,6},{AUGMENTED,8},{NULL,0}};
const strint tab_music_theory::seventh[] = {{MAJOR,11},{MINOR,10},{DIMINISHED,9},{NULL,0}};

const strint tab_music_theory::majorscale[] = {{TONIC,0},{SUPERTONIC,2},{MEDIANT,4},{SUBDOMINANT,5},{DOMINANT,7},{SUBMEDIANT,9},{LEADINGTONE,11},{NULL,0}};
const strint tab_music_theory::majorsolfege[] = {{"do",0},{"re",2},{"mi",4},{"fa",5},{"so",7},{"la",9},{"ti",11},{NULL,0}};

// note tone stuff
const tab_music_theory::twelve_tone tab_music_theory::twelve[] = 
{
	{ C, "C", "C", "do","do",{ "B#", NULL } },
	{ Cs, "C#", "Db", "di","ra",{ NULL } },
	{ D, "D", "D", "re","re",{ NULL } },
	{ Ef, "Eb", "D#", "ri","ma",{ NULL } },

	{ E, "E", "E", "mi","mi",{ "Fb", NULL } },
	{ F, "F", "F", "fa","fa",{ "E#", NULL } },
	{ Fs, "F#", "Gb", "fi","se",{ NULL } },
	{ G, "G", "G", "so","so",{ NULL } },

	{ Af, "Ab", "G#", "si","le",{ NULL } },
	{ A, "A", "A", "la","la",{ NULL } },
	{ Bf, "Bb", "A#", "li","te",{ NULL } },
	{ B, "B", "B", "ti","ti",{ "Cb", NULL } },

{C,NULL,NULL,NULL,NULL,{NULL}}};

tab_music_theory::twelve_step tab_music_theory::getTone(const char * name)
{
	if	( name == NULL || name[0] == 0 )
		return C;

	for ( int i = 0 ; i < SEMI_TONES_PER_OCTAVE ; i++ )
	{
		if	(!StringCompareInsensitive(name,twelve[i].name) )
			return twelve[i].key;

		if	(!StringCompareInsensitive(name,twelve[i].minor) )
			return twelve[i].key;

		if	(!StringCompareInsensitive(name,twelve[i].solfege) )
			return twelve[i].key;

		if	(!StringCompareInsensitive(name,twelve[i].solflow) )
			return twelve[i].key;
		
	}

	return C;
}

tab_music_theory::twelve_step tab_music_theory::getTone(int val)
{
	if	( val < 0 )
	{
		int w = -val;
		w += SEMI_TONES_PER_OCTAVE;
		w += SEMI_TONES_PER_OCTAVE;
		w /= SEMI_TONES_PER_OCTAVE;
		w *= SEMI_TONES_PER_OCTAVE;
		val += w;
	}

	return (twelve_step) (val % SEMI_TONES_PER_OCTAVE);
}

int tab_music_theory::midiNoteName(int note, tab_filebuf * name)
{
	note = midiNoteFitInRange(note);
	name->Set(twelve[note % SEMI_TONES_PER_OCTAVE].name);
	if	( int octave = ( note - MIDI_NOTE_MIN ) / SEMI_TONES_PER_OCTAVE )
		name->Write(octave);
	return note;
}

bool tab_music_theory::midiNoteBlackKey(int note)
{
	note = midiNoteFitInRange(note);
	int rem = note % SEMI_TONES_PER_OCTAVE;
	if	(	( rem == 1 )
		||	( rem == 3 )
		||	( rem == 6 )
		||	( rem == 8 )
		||	( rem == 10 )
		)
		return true;

	return false;
}

int tab_music_theory::midiNoteFitInRange(int note, int min, int max )
{
	if	( min < MIDI_NOTE_MIN )
		min = MIDI_NOTE_MIN;
	if	( max > MIDI_NOTE_MAX )
		max = MIDI_NOTE_MAX;
	if	( min >= max )
	{
		min = MIDI_NOTE_MIN;
		max = MIDI_NOTE_MAX;
	}

	if	( note >= min && note <= max )
		return note;

	while ( note < min )
		note += SEMI_TONES_PER_OCTAVE;

	while ( note > max )
		note -= SEMI_TONES_PER_OCTAVE;

	if	( note < min || note > max )
		return 0;

	return note;
}

// scale stuff

const int tab_music_theory::pentaton_scale[] = {SCALE_NOTE,0,SCALE_NOTE,0,SCALE_NOTE,0,0,SCALE_NOTE,0,SCALE_NOTE,0,0,SCALE_NOTE,0,SCALE_NOTE,0,SCALE_NOTE,0,0,SCALE_NOTE,0,SCALE_NOTE,0,0};
const int tab_music_theory::western_major_scale[] = {SCALE_NOTE,0,SCALE_NOTE,0,SCALE_NOTE,SCALE_NOTE,0,SCALE_NOTE,0,SCALE_NOTE,0,SCALE_NOTE,SCALE_NOTE,0,SCALE_NOTE,0,SCALE_NOTE,SCALE_NOTE,0,SCALE_NOTE,0,SCALE_NOTE,0,SCALE_NOTE};
const int tab_music_theory::minor_harmonic_scale[] = {SCALE_NOTE,0,SCALE_NOTE,SCALE_NOTE,0,SCALE_NOTE,0,SCALE_NOTE,SCALE_NOTE,0,SCALE_NOTE,0,0,SCALE_NOTE,SCALE_NOTE,SCALE_NOTE,0,SCALE_NOTE,0,SCALE_NOTE,SCALE_NOTE,0,0,SCALE_NOTE};
const int tab_music_theory::minor_melodic_scale[] = {SCALE_NOTE,0,SCALE_NOTE,SCALE_NOTE,0,SCALE_NOTE,0,SCALE_NOTE,DESCENDING_SCALE_NOTE,ASCENDING_SCALE_NOTE,DESCENDING_SCALE_NOTE,ASCENDING_SCALE_NOTE,SCALE_NOTE,0,SCALE_NOTE,SCALE_NOTE,0,SCALE_NOTE,0,SCALE_NOTE,DESCENDING_SCALE_NOTE,ASCENDING_SCALE_NOTE,DESCENDING_SCALE_NOTE,ASCENDING_SCALE_NOTE};

const tab_music_theory::scale_definition tab_music_theory::scale[] = {

	{	"major",			12,	&tab_music_theory::western_major_scale[0] },
	{	"minor",			12,	&tab_music_theory::western_major_scale[9] },
	{	"minor-harmonic",	12,	&tab_music_theory::minor_harmonic_scale[0] },
	{	"minor-melodic",	12,	&tab_music_theory::minor_melodic_scale[0] },
	{	"pentaton-major",	12,	&tab_music_theory::pentaton_scale[0] },
	{	"pentaton-minor",	12,	&tab_music_theory::pentaton_scale[9] },

	{	"modern-ionian",			12,	&tab_music_theory::western_major_scale[0] },
	{	"modern-dorian",			12,	&tab_music_theory::western_major_scale[2] },
	{	"modern-phrygian",			12,	&tab_music_theory::western_major_scale[4] },
	{	"modern-lydian",			12,	&tab_music_theory::western_major_scale[5] },
	{	"modern-mixolydian",		12,	&tab_music_theory::western_major_scale[7] },
	{	"modern-aeolian",			12,	&tab_music_theory::western_major_scale[9] },
	{	"modern-locrian",			12,	&tab_music_theory::western_major_scale[11] },

	{	NULL,0,NULL}
	};

const tab_music_theory::scale_definition * tab_music_theory::scaleExists(const char * name)
{
	if	( name == NULL || name[0] == 0 )
		return NULL;

	for ( int i = 0 ; scale[i].name != NULL && scale[i].semitone_range != 0 ; i++ )
	{
		if	(!StringCompareInsensitive(name,scale[i].name))
			return &scale[i];
	}

	return NULL;
}


// chord stuff
const tab_music_theory::chord_definition tab_music_theory::chord[] = {

	{	tab_music_theory::MAJOR,			"", 3, {0,4,7} },
	{	tab_music_theory::MINOR,			"-", 3, {0,3,7} },
	{	tab_music_theory::DIMINISHED,		"o", 3, {0,3,6} },
	{	tab_music_theory::AUGMENTED,		"+", 3, {0,4,8} },

	{	"sus 4",							"s4", 3, {0,5,7} },

	{	"major 7",							"M7", 4, {0,4,7,11} },
	{	"minor 7",							"-7", 4, {0,3,7,10} },
	{	"diminished 7",						"o7", 4, {0,3,6,9} },
	{	"augmented 7",						"+7", 4, {0,4,8,10} },

	{	"dominant 7",						"7", 4, {0,4,7,10} },
	{	"minor 7 (5b)",						"-7b5", 4, {0,3,6,10} },
	{	"half diminished",					"h7", 4, {0,3,6,10} },
	{	"major 6",							"6", 4, {0,4,7,9} },
	{	"minor 6",							"-6", 4, {0,3,7,9} },
	{	"major 9",							"9", 4, {0,4,7,14} },
	{	"minor 9",							"-9", 4, {0,3,7,14} },

	{	"major 69",							"69", 5, {0,4,7,9,14} },
	{	"minor 69",							"-69", 5, {0,3,7,9,14} },

	//{	"",							"", 4, {0,3,7,10} },

{NULL,NULL,0,{}}};

int tab_music_theory::chordTypeOffset(const char * ch)
{
	if	(ch == NULL)
		return 0;

	if	(	( ch[0] >= 'A' && ch[0] <= 'G' )
		||	( ch[0] >= 'a' && ch[0] <= 'g' )
		)
	{
		if	( ch[1] == '#' || ch[1] == 'b' || ch[1] == 'B' )
			return 2;

		return 1;
	}

	return 0;
}

int tab_music_theory::chordRootTypeBass(const char * ch, tab_filebuf * note, tab_filebuf * type, tab_filebuf * bass)
{
	int retval = chordTypeOffset(ch);
	if	( retval == 0 )
		return retval;

	if	( note )
	{
		note->Clear();
		note->WriteBlockInt(ch,retval);
		note->WriteChar(tab_object::EMPTY_STRING);
		*note->str = tab_object::CharMakeUpper(*note->str);
	}

	if ( type )
	{
		type->Clear();
		for ( int i = retval ; ch[i] != '/' && ch[i] != 0 ; i++ )
		{
			type->WriteChar(&ch[i]);
		}
		type->WriteChar(EMPTY_STRING);
	}

	if ( bass )
	{
		int i = 0;
		bass->Clear();

		for ( i = retval ; ch[i] != '/' && ch[i] != 0 ; i++ ){} 

		if	( ch[i] == '/' )
		{
			bass->Set(&ch[i+1]);
		}
	}

	return retval;
}

int tab_music_theory::chordTranspose(const char * chord, int by, tab_filebuf *trans, tab_filebuf * note, tab_filebuf * type, tab_filebuf * bass)
{
	trans->Set(chord);

	if	(!chordRootTypeBass(chord,note,type,bass) )
		return 0;

	bool root_transposed = false;
	bool bass_transposed = false;
	for ( int i = 0 ; i < SEMI_TONES_PER_OCTAVE ; i++ )
	{
		if	(	(!root_transposed)
			&&	(	(!StringCompareInsensitive(note->str,twelve[i].name))
				||	(!StringCompareInsensitive(note->str,twelve[i].minor))
				)
			)
		{
			int new_value = ((i+SEMI_TONES_PER_OCTAVE+SEMI_TONES_PER_OCTAVE+by)%SEMI_TONES_PER_OCTAVE);
			note->Set(twelve[new_value].name);
			root_transposed = true;
		}

		if	(	(!bass_transposed)
			&&	(bass->Check())
			&&	(bass->str[0])
			&&	(	(!StringCompareInsensitive(bass->str,twelve[i].name))
				||	(!StringCompareInsensitive(bass->str,twelve[i].minor))
				)
			)
		{
			int new_value = ((i+SEMI_TONES_PER_OCTAVE+SEMI_TONES_PER_OCTAVE+by)%SEMI_TONES_PER_OCTAVE);
			bass->Set(twelve[new_value].name);
			bass_transposed = true;
		}
	}

	trans->Set(note->str);
	trans->Write(type->str);

	if	( bass && bass->Check() && bass->str[0] != 0 )
	{
		trans->Write("/");
		trans->Write(bass->str);
	}
	return 1;
}

int tab_music_theory::chordChangeRoot(const char * chord, const char * new_root, tab_filebuf *nu_chord, tab_filebuf * note, tab_filebuf * type, tab_filebuf * bass)
{
	nu_chord->Set(chord);

	if	(!chordRootTypeBass(chord,note,type,bass) )
	{
		nu_chord->Clear();
		return 1;
	}

	for ( int i = 0 ; i < SEMI_TONES_PER_OCTAVE ; i++ )
	{
		if	(!StringCompareInsensitive(new_root,twelve[i].name))
		{
			note->Set(twelve[i].name);
			nu_chord->Set(twelve[i].name);
			nu_chord->Write(type->str);
			if	( bass && bass->Check() && bass->str[0] != 0 )
			{
				nu_chord->Write("/");
				nu_chord->Write(bass->str);
			}
			return 1;
		}

		if	(!StringCompareInsensitive(new_root,twelve[i].minor))
		{
			note->Set(twelve[i].minor);
			nu_chord->Set(twelve[i].minor);
			nu_chord->Write(type->str);
			if	( bass && bass->Check() && bass->str[0] != 0 )
			{
				nu_chord->Write("/");
				nu_chord->Write(bass->str);
			}
			return 1;
		}
	}

	return 0;
}

int tab_music_theory::chordChangeBass(const char * chord, const char * new_bass, tab_filebuf *nu_chord, tab_filebuf * note, tab_filebuf * type, tab_filebuf * bass)
{
	nu_chord->Set(chord);

	if	(!chordRootTypeBass(chord,note,type,bass) )
		return 0;

	for ( int i = 0 ; i < SEMI_TONES_PER_OCTAVE ; i++ )
	{
		if	(!StringCompareInsensitive(new_bass,twelve[i].name))
		{
			bass->Set(twelve[i].name);
			nu_chord->Set(note->str);
			nu_chord->Write(type->str);
			if	( bass && bass->Check() && bass->str[0] != 0 )
			{
				nu_chord->Write("/");
				nu_chord->Write(bass->str);
			}
			return 1;
		}

		if	(!StringCompareInsensitive(new_bass,twelve[i].minor))
		{
			bass->Set(twelve[i].minor);
			nu_chord->Set(note->str);
			nu_chord->Write(type->str);
			if	( bass && bass->Check() && bass->str[0] != 0 )
			{
				nu_chord->Write("/");
				nu_chord->Write(bass->str);
			}
			return 1;
		}
	}

	bass->Clear();
	nu_chord->Set(note->str);
	nu_chord->Write(type->str);

	return 1;


}

int tab_music_theory::chordChangeType(const char * chord, const char * new_type, tab_filebuf *nu_chord, tab_filebuf * note, tab_filebuf * type, tab_filebuf * bass)
{
	nu_chord->Set(chord);

	if	(!chordRootTypeBass(chord,note,type,bass) )
		return 0;

	for ( int i = 0 ; tab_music_theory::chord[i].name != NULL && tab_music_theory::chord[i].noteCount != 0 ; i++ )
	{
		if	(!StringCompareInsensitive(new_type,tab_music_theory::chord[i].name))
		{
			type->Set(tab_music_theory::chord[i].name);
			nu_chord->Set(note->str);
			nu_chord->Write(tab_music_theory::chord[i].name);
			if	( bass && bass->Check() && bass->str[0] != 0 )
			{
				nu_chord->Write("/");
				nu_chord->Write(bass->str);
			}
			return 1;
		}
	}

	return 0;
}

tab_music_theory::twelve_step tab_music_theory::chordRootTone(const char * chord)
{
	tab_filebuf note;
	if	(!chordRootTypeBass(chord,&note) )
		return C;

	for ( int i = 0 ; i < SEMI_TONES_PER_OCTAVE ; i++ )
	{
		if	(!StringCompareInsensitive(note.str,twelve[i].name))
		{
			return (twelve_step) i;
		}
		if	(!StringCompareInsensitive(note.str,twelve[i].minor))
		{
			return (twelve_step) i;
		}
	}

	return C;
}

const tab_music_theory::chord_definition * tab_music_theory::chordExists(const char * ch)
{
	int offset = chordTypeOffset(ch);
	if	(	(offset == 0)
		)
		return NULL;

	for ( int i = 0 ; chord[i].name != NULL ; i++ )
	{
		if	(!StringCompareBeginningInsensitive(&ch[offset],chord[i].name,StringLength(chord[i].name)))
			return &chord[i];
	}

	return NULL;
}


const char * tab_music_theory::MINOR = "minor";
const char * tab_music_theory::MAJOR = "major";
const char * tab_music_theory::AUGMENTED = "augmented";
const char * tab_music_theory::DIMINISHED = "diminished";
const char * tab_music_theory::PERFECT = "perfect";

const char * tab_music_theory::TONIC = "tonic";
const char * tab_music_theory::SUPERTONIC = "supertonic";
const char * tab_music_theory::MEDIANT = "mediant";
const char * tab_music_theory::SUBDOMINANT = "subdominant";
const char * tab_music_theory::DOMINANT = "dominant";
const char * tab_music_theory::SUBMEDIANT = "submediant";
const char * tab_music_theory::LEADINGTONE = "leadingtone";

const double tab_music_theory::A4_FREQUENCY = 440.0;
const int tab_music_theory::A4_MIDINOTE = 69;
const int tab_music_theory::MIDDLE_C = 60;

const double tab_music_theory::SEMITONE_UP = pow(2.0,(1.0/12.0));

const int tab_music_theory::MIDI_NOTE_MIN = 21;
const int tab_music_theory::MIDI_NOTE_MAX = 108;

tab_music_theory::tab_music_theory()
{
}

tab_music_theory::~tab_music_theory()
{
}




