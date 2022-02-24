//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
  {"", "/mnt/develop/application/dwm/scripts/dwmcpu",					  30,		0},
	{"", "/mnt/develop/application/dwm/scripts/dwmmemory",			  	30,		0},
	{"", "/mnt/develop/application/dwm/scripts/dwmdisk",				    30,		0},
	{"", "/mnt/develop/application/dwm/scripts/dwmkeyboard",		  	01,		0},
	{"", "/mnt/develop/application/dwm/scripts/dwmclock",				  30,		0}
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 20;
