#include <iostream>
#include <cstdlib>
#include <string.h>
#include <ctime>
#include <conio.h>
#include <stdio.h>
using namespace std;

#define C_NOTE 10
#define D_NOTE 9
#define E_NOTE 8
#define F_NOTE 7
#define G_NOTE 6
#define A_NOTE 5
#define H_NOTE 4

#define BLOCK_WIDTH 11
#define BLOCK_HEIGHT 11

#define BLOCK_LINE			"----------"
#define EMPTY_BLOCK_LINE	"          "
#define NOTE_LINE			"---(  )---"
#define EMPTY_NOTE_LINE		"   (  )   "


struct NoteBlock{
	char data[BLOCK_HEIGHT][BLOCK_WIDTH];
	int note;
	bool guessed = false;
};

struct NoteStats {
	int hits = 0 ;
	int correct_hits = 0;
};

struct Statistics {
	NoteStats notes[11];
};


void fill_block(NoteBlock* note_block) {
	for (int i = 0; i <=8 ; i++) {
		if (i % 2 == 0)
			strcpy(note_block->data[i], BLOCK_LINE);
		else
			strcpy(note_block->data[i], EMPTY_BLOCK_LINE);
	}
	strcpy(note_block->data[BLOCK_HEIGHT-2], EMPTY_BLOCK_LINE);
	strcpy(note_block->data[BLOCK_HEIGHT - 1], EMPTY_BLOCK_LINE);

	if (note_block->note % 2 == 0)
		strcpy(note_block->data[ note_block->note ], NOTE_LINE);
	else
		strcpy(note_block->data[ note_block->note ], EMPTY_NOTE_LINE);

}

void print_blocks(NoteBlock** blocks, int current_block, int active_blocks) {
	for (int i = 0; i < BLOCK_HEIGHT; i++) {

		int j= current_block;
		int printed_block_count = 0;

		while (printed_block_count < active_blocks && printed_block_count < 7) {
			if ( ! blocks[j % 10]->guessed ) {
				printf("%s", blocks[j % 10]->data[i]);
				printed_block_count++;
			}

			j++;
		}

		printf("\n");
	}
}


NoteBlock** create_blocks() {
	NoteBlock** blocks = new NoteBlock*[10];

	for (int i = 0; i < 10; i++) {
		NoteBlock* new_block = new NoteBlock;
		new_block->note = rand() % 7 + 4;

		fill_block(new_block);
		blocks[i] = new_block;
	}
	return blocks;
}

void destroy_blocks(NoteBlock** blocks) {
	for (int i = 0; i < 10; i++) {
		delete blocks[i];
	}
	delete[] blocks;
}


bool check_user_answer(NoteBlock* current_block, char pressed_key, Statistics* s) {

	if (pressed_key == 'c') {
		s->notes[C_NOTE].hits++;
		if (current_block->note == C_NOTE) {
			s->notes[C_NOTE].correct_hits++;
			return true;
		}
	}
	else if (pressed_key == 'd') {
        s->notes[D_NOTE].hits++;
		if (current_block->note == D_NOTE) {
		    s->notes[D_NOTE].correct_hits++;
			return true;
		}
	}
	else if (pressed_key == 'e') {
	    s->notes[E_NOTE].hits++;
		if (current_block->note == E_NOTE) {
		    s->notes[E_NOTE].correct_hits++;
			return true;
		}
	}
	else if (pressed_key == 'f') {
	    s->notes[F_NOTE].hits++;
		if (current_block->note == F_NOTE) {
		    s->notes[F_NOTE].correct_hits++;
			return true;
		}
	}
	else if (pressed_key == 'g') {
	    s->notes[G_NOTE].hits++;
		if (current_block->note == G_NOTE) {
		    s->notes[G_NOTE].correct_hits++;
			return true;
		}
	}
	else if (pressed_key == 'a') {
	    s->notes[A_NOTE].hits++;
		if (current_block->note == A_NOTE) {
		    s->notes[A_NOTE].correct_hits++;
			return true;
		}
	}
	else if (pressed_key == 'h') {
	    s->notes[H_NOTE].hits++;
		if (current_block->note == H_NOTE) {
		    s->notes[H_NOTE].correct_hits++;
			return true;
		}
	}
	return false;
}

void get_note_name(int note, char* name_buffer) {
	switch (note) {
	case C_NOTE:
		strcpy(name_buffer, "C");
		break;
	case D_NOTE:
		strcpy(name_buffer, "D");
		break;
	case E_NOTE:
		strcpy(name_buffer, "E");
		break;
	case F_NOTE:
		strcpy(name_buffer, "F");
		break;
	case G_NOTE:
		strcpy(name_buffer, "G");
		break;
	case A_NOTE:
		strcpy(name_buffer, "A");
		break;
	case H_NOTE:
		strcpy(name_buffer, "H");
		break;
	}
}

void show_statistics(Statistics* s) {
	printf("%s"  , "     ");
	printf("%s", "Liczba poprawnych odpowiedzi  ");
	printf("%s", "Liczba odpowiedzi  ");
	printf("%s", "Stosunek odpowiedzi prawidlowych do wszystkich  \n");
	for (int note = C_NOTE; note >= H_NOTE; note--) {
		char note_name[5];
		float hits = s->notes[note].hits;
		float correct_hits = s->notes[note].correct_hits;
		get_note_name(note, note_name);
		printf("%s    ", note_name);
		printf("%17d     ", (int)correct_hits);
		printf("%20d    ", (int)hits);
		if(hits > 0)
			printf("%20d%%", (int)((correct_hits / hits) * 100 ));
		else
			printf("%20d%%", 0);
		printf("\n");
		printf("------------------------------------------------------------------------------------------------------");
		printf("\n");
	}
	getch();
}

void reset_statistics(Statistics* s) {
	for (int note = C_NOTE; note >= H_NOTE; note--) {
		s->notes[note].correct_hits = 0;
		s->notes[note].hits = 0;
	}
}

int main() {
	srand(time(NULL));
	NoteBlock** blocks = create_blocks();
	Statistics stats;

	int current_block_offset = 0;
	int notes_to_guess = 10;
	printf("notes remaining: %d\n", notes_to_guess);
	print_blocks(blocks, current_block_offset, notes_to_guess);

	while (true) {
		//read user input
		char pressed_key = getch();

		bool current_block_guessed = false;
		//handle user input
		if (pressed_key == 'r') {
			destroy_blocks(blocks);
			blocks = create_blocks();
			reset_statistics(&stats);
			notes_to_guess = 10;

		}
		else if (pressed_key == 'q') {
			break;
		}
		else if (pressed_key == 's') {
			system("cls");
			show_statistics(&stats);
			continue;
		}
		else {
			current_block_guessed = check_user_answer(blocks[current_block_offset], pressed_key, &stats);
			if (current_block_guessed) {
				blocks[current_block_offset]->guessed = true;
				notes_to_guess--;
			}
		}

		//find next block to display
		if (notes_to_guess > 0) {
			do {
				current_block_offset += 1;
				current_block_offset %= 10;
			} while (blocks[current_block_offset]->guessed);
		}

		//print
		system("cls");
		if (notes_to_guess > 0) {
			printf("notes remaining: %d\n", notes_to_guess);
			print_blocks(blocks, current_block_offset, notes_to_guess);
			if (current_block_guessed) {
				printf("\n%c was the right guess!", pressed_key);
			}
			else {
				printf("\nmiss!");
			}
		}
		else {
			printf("GAME OVER! GOOD JOB");
		}
	}


	destroy_blocks(blocks);

	return 0;
}
