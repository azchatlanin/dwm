/* appearance */
static const unsigned int borderpx            = 3;        /* border pixel of windows */
static const unsigned int snap                = 37;       /* snap pixel */
static const int showbar                      = 1;        /* 0 means no bar */
static const int topbar                       = 1;        /* 0 means bottom bar */
static const int gappx                        = 12;       /* gaps between windows */

static const char *fonts[]                    = { "Monospace Regular:size=10" };        /* шрифт бара*/
static const char dmenufont[]                 = "Monospace Regular:size=10";            /* шрифт dmenu*/

static const char col_gray1[]                 = "#23252e";   
static const char col_gray2[]                 = "#e6e6e6";    
static const char col_gray3[]                 = "#e6e6e6";     
static const char col_gray4[]                 = "#23252e";      
static const char col_cyan[]                  = "#304969";       
static const char border_color[]              = "#2a8058";        
static const char border_color_no_select[]    = "#30455e";        
static const char *colors[][3]                = {
                                                  /*               fg         bg         border   */
                                                  [SchemeNorm] = { col_gray2, col_gray1, border_color_no_select },
                                                  [SchemeSel]  = { col_gray4, col_cyan,  border_color  },
                                                };

/* tagging */
static const char *tags[] = { "www", "chat", "worker", "helper", "terminal", "server", "3D graphics", "cads", "zoom", "dbeaver", "postman" };

static const Rule rules[] = {
	/* xprop(1): */
	/* class               instance                 title       tags mask          isfloating      monitor */
  { "Google-chrome",    "google-chrome",          NULL,       1 << 0,            False,          -1 },
  { "TelegramDesktop",   NULL,                    NULL,       1 << 1,            False,          -1 },
  { "worker",           "tilix",                  NULL,       1 << 2,            False,          -1 },
  { "helper",           "tilix",                  NULL,       1 << 3,            False,          -1 },
  { "zoom",              NULL,                    NULL,       1 << 8,            False,          -1 },
  { "DBeaver",           NULL,                    NULL,       1 << 9,            False,          -1 },
  { "Postman",           NULL,                    NULL,       1 << 10,           False,          -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static Layout layouts[] = {
	/* symbol               function */
	{ "|||",                tcl },
	{ "><>",                NULL },
	{ "[]=",                tile }, /* first entry is default */
};

// static const Layout layouts[] = {
// 	/* symbol     arrange function */
// 	{ "[]=",      tile },    /* first entry is default */
// 	{ "><>",      NULL },    /* no layout function means floating behavior */
// 	{ "[M]",      monocle },
// };

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { "tilix", NULL };
static const char *googl_chrome_stable[]  = { "googl-chrome-stable", NULL };
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", color_1, "-nf", "#568e75", "-sb", "#002b36", "-sf", "#268bd2", NULL };
//static const char *roficmd[] = { "rofi", "-show", "drun", "-show-icons", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          { .v = dmenucmd } },                   // run dmenu
	{ MODKEY|ShiftMask,             XK_Return, spawn,          { .v = termcmd } },                    // run terminal
	{ MODKEY,                       XK_a,      spawn,          { .v = googl_chrome_stable } },        // run google-chrome

	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },              // change focus
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },              // change focus
  { MODKEY,                       XK_e,      view_adjacent,  {.i = +1 } },              // perv tag
  { MODKEY,                       XK_q,      view_adjacent,  {.i = -1 } },              // next tag
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.01} },            // resize
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.01} },            // resize
	{ MODKEY,                       XK_Tab,    view,           {0} },                     // show previus teg
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },                     // kill window
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },                     // toogle flating
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },             // look all tags
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	// { MODKEY|ShiftMask,             XK_q,      quit,           {0} }, you need uncommment row 1249 in file dwm.c and 189
  // { MODKEY,                       XK_b,      togglebar,      {0} }, you  need uncomment 1701 in file dwm.c and 212
  // { MODKEY,                       XK_Return, zoom,           {0} }, you  need uncomment 2114 in file dwm.c and 235
  // { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } }, you  need uncomment 967 in file dwm.c and 177
  // { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } }, you  need uncomment 967 in file dwm.c and 177
  // { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } }, you  need uncomment 818 in file dwm.c and 170
  // { MODKEY,                       XK_period, focusmon,       {.i = +1 } }, you  need uncomment 818 in file dwm.c and 170
  // { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, you  need uncomment 1666 in file dwm.c and 210
  // { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, you  need uncomment 1666 in file dwm.c and 210
  // { MODKEY,                       XK_space,  setlayout,      {2} },
  { MODKEY,                       XK_c,      setlayout,      {.v = &layouts[0]} },      // set full window
  /* ==================================================================================================================== 
   THIS CAN USE, IT FREE !!!
  { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
  { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },      // set tiling
  { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
  */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {2} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[0]} },
	//{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
