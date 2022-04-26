/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx        = 1;        /* border pixel of windows */
static const Gap default_gap              = {.isgap = 1, .realgap = 10, .gappx = 10};
static const unsigned int snap            = 32;       /* snap pixel */
static const int showbar                  = 0;        /* 0 means no bar */
static const int topbar                   = 1;        /* 0 means bottom bar */
static const char *fonts[]                = { "FiraCode Nerd Font:pixelsize=11:antialias=true:autohint=true", "CaskaydiaCove Nerd Font Mono:pixelsize=10:antialias=true:autohint=true", "monospace:size=8" };
static const char dmenufont[]             = "FiraCode Nerd Font:pixelsize=11:antialias=true:autohint=true";
//static char *font = "FiraCode Nerd Font:pixelsize=12:antialias=true:autohint=true";
static const char col_matrix_green[]      = "#00FF41";
static const char col_matrix_green_dark[] = "#008F11";
static const char col_matrix_black[]      = "#222222";
static const char *colors[][3]            = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_matrix_green_dark, col_matrix_black, col_matrix_black},
	[SchemeSel]  = { col_matrix_green,      col_matrix_black, col_matrix_black },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };


// https://dwm.suckless.org/customisation/rules/
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance       title            tags mask     iscentered     isfloating   monitor */
	{ "Gimp",        NULL,          NULL,            0,            0,             1,           -1 },
	{ "st-256color", "st-256color", "pulsemixer",    0,            1,             1,           -1 },
	{ "st-256color", "st-256color", "bc",            0,            1,             1,           -1 },
	{ "mpv",         "mpv",         "mpvfloat",      0,            1,             1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask //Mod4Mask = windows key
#define CTLSFT ControlMask|ShiftMask
#define HYPER Mod4Mask|ControlMask|ShiftMask|Mod1Mask
#define MEH ControlMask|ShiftMask|Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2]            = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *calccmd[]       = { "st", "-e", "bc -l", NULL };
static const char *camtogglecmd[]  = { "camtoggle", NULL };
static const char *dmenucmd[]      = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_matrix_black, "-nf", col_matrix_green_dark, "-sb", col_matrix_black, "-sf", col_matrix_green, NULL };
static const char *pulsemixercmd[] = { "st", "-e", "pulsemixer", NULL };
static const char *taskmgrcmd[]    = { "st", "-n", "top", "-e", "htop", NULL };
static const char *termcmd[]       = { "st", NULL };
static const char *timecmd[]       = { "popinfo2", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

	/* bens keys */
	{ MEH,                          XK_c,      spawn,          {.v = camtogglecmd } },
	{ MEH,                          XK_n,      spawn,          {.v = calccmd } },
	{ MEH,                          XK_m,      spawn,          {.v = pulsemixercmd } },
	{ MEH,                          XK_Escape, spawn,          {.v = taskmgrcmd } },
	{ MEH,                          XK_t,      spawn,          {.v = timecmd } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

