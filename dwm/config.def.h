/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrains Mono:size=10:antialias=true:autohint=true" };
static const char dmenufont[]       = "JetBrains Mono:size=10:antialias=true:autohint=true";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
//static const char col_cyan[]        = "#005577";
static const char col_cyan[]        = "#B78900";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "🐧", "🔎", "⌨️", "💬", "📺", "🎵", "♟️", "💻", "🎮"};
static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const int momentaryalttags = 0; /* 1 means alttags will show only when key is held down*/

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           2,         0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
//static const char *termcmd[]  = { "st & disown", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *browser[]  = { "firefox", NULL };
static const char *pbrowser[]  = { "firefox", "--private-window", "https://www.startpage.com/do/mypage.pl?prfe=155c682fb27c65dc4a30ef3f9e32b063eb9ea7ab67076ab761b82d50e8ba66f1e4db668416d0ca4a6673abdfc5a317efa745b1caffde684040c09e8aa0b6e9221b22dd461d6500f109ca8f8b2925", NULL};
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

#include<X11/XF86keysym.h> /* needed for multimedia keys */
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,	                XK_b, 	   spawn,          {.v = browser } },
	{ MODKEY|ShiftMask,	        XK_p, 	   spawn,          {.v = pbrowser } },
	{ MODKEY,                       XK_s,      togglebar,      {0} },
	{ MODKEY,                       XK_l,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_h,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_j,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_k,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_n,      togglealttag,   {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_c,      quit,           {0} },

	{ MODKEY,		        XK_e, 	   spawn,          SHCMD("dmenukaomoji")},
	{ MODKEY,		        XK_Print,  spawn,          SHCMD("screenshot full")},
	{ MODKEY|ShiftMask,		XK_Print,  spawn,          SHCMD("screenshot select")},
	{ MODKEY|ControlMask,		XK_l, 	   spawn,          {.v = (const char*[]){"st", "-e", "lf", NULL} } },
	{ MODKEY|ControlMask,		XK_m, 	   spawn,          {.v = (const char*[]){"st", "-e", "ncspot", NULL} } },
	{ MODKEY|ShiftMask,	        XK_s, 	   spawn,          SHCMD("doas /sbin/poweroff")},
	{ MODKEY|ShiftMask,	        XK_h, 	   spawn,          SHCMD("doas /usr/sbin/zzz")},
	{ MODKEY|ShiftMask,	        XK_r, 	   spawn,          SHCMD("doas /sbin/reboot")},
	{ ShiftMask,	                XK_F1, 	   spawn,          SHCMD("mixer -s vol toggle")},
	{ ShiftMask,	                XK_F2, 	   spawn,          SHCMD("mixer -s vol -5")},
	{ ShiftMask,	                XK_F3, 	   spawn,          SHCMD("mixer -s vol +5")},
	{ ShiftMask,	                XK_F5, 	   spawn,          SHCMD("intel_backlight decr 20")},
	{ ShiftMask,	                XK_F6, 	   spawn,          SHCMD("intel_backlight incr 20")},
	{ ShiftMask,	                XK_F7, 	   spawn,          SHCMD("redshift -P -O 3500K && intel_backlight 20")},
	{ ShiftMask,	                XK_F8, 	   spawn,          SHCMD("redshift -x && intel_backlight 100")},
	{ ShiftMask,	                XK_F9, 	   spawn,          SHCMD("redshift -P -O 3500K")},
	{ ShiftMask,	                XK_F10,    spawn,          SHCMD("playerctl --player=ncspot play-pause")},
	{ ShiftMask,	                XK_F11,	   spawn,          SHCMD("playerctl --player=ncspot previous")},
	{ ShiftMask,	                XK_F12,	   spawn,          SHCMD("playerctl --player=ncspot next")},
	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("mixer -s vol toggle") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("mixer -s vol +5") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("mixer -s vol -5") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("intel_backligt incr 20") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("intel_backlight decr 20") },

	{ MODKEY|ShiftMask,	                XK_l, 	  spawn,           SHCMD("/usr/local/bin/slock &")},

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

