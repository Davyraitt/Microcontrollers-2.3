#ifndef LCDH
#define LCDH
	void init();
	void display_text(char *str);
	void cmdSend(char cmd);
	void charSend(char character);
	void displaySend(char bytes, int rs);
	void blinkE();
	void return_home();
	void set_cursor(int position);
	void clear();
#endif