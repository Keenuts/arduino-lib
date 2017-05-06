#include <avr/io.h>
#include <time.h>
#include <util/delay.h>

#include "digital.h"
#include "lcd.h"
 
uint32_t my_strlen(const char* str) {
	uint32_t len = 0;
	while(str[len] != 0)
		len++;
	return len;
}

int main (void)
{
	power_on();
	
	int index = 0;
	const char *text[] = {
		"Ooh whoa, ooh whoa,      ooh whoa",
		"I know you love me, I know you care",
		"Just shout whenever and I'll be there",
		"  You want my love,   you want my heart",
		" And we will never,  ever, ever be apart",
		"Are we an item? Girl    quit playin'",
		"We're just friends, what are you sayin'",
		"Said there's anotherlook right in mine",
		"My first love, broke       my heart",
		" And I was like baby   baby, baby oh",
		"  Like baby, baby,         baby no",
		"  Like baby, baby,         baby oh",
		"   I thought you'd       always be mine",
		" Baby, baby, baby oh",
		"  Like baby, baby,         baby no",
		"  Like baby, baby,         baby ooh",
		" I thought you'd     always be mine",
		"Oh for you, I would have done whatever",
		"And I just can't    believe we together",
		"And I wanna play it         cool",
		"But I'm losin' you",
		"   I'll buy you            anything",
		"   I'll buy you            any ring",
		"And I'm in pieces,     baby fix me",
	};

	while (1) {
		clear();
		set_mode(WRITE);

		for (uint32_t i = 0; i < my_strlen(text[index]); i++)
			write_char(text[index][i]); 
		index = (index + 1) % (sizeof(text) / sizeof(uint8_t));

		set_mode(READ);

		_delay_ms(3000);
	}


	_delay_ms(5000);
	clear();
	power_off();
}
