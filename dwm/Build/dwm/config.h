/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Ubuntu:size=10", "Font Awesome 6 Free Solid:size=10" };
static const char dmenufont[]       = "Ubuntu:size=10";
static const char col_gray1[]       = "#080802";
static const char col_gray2[]       = "#f9f8fe";
static const char col_gray3[]       = "#f9f8fe";
static const char col_gray4[]       = "#090902";
static const char col_cyan[]        = "#ffd86e";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
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
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };

static const char *flameshot[] = { "/usr/bin/flameshot", "gui", NULL };
static const char *blueman[] = { "/usr/bin/blueman-manager", NULL };
static const char *telegram[] = { "/usr/bin/telegram-desktop", NULL };
static const char *spotify[] = { "/usr/bin/spotify", NULL };
static const char *firefox[] = { "/usr/bin/firefox", NULL };

static const char *volraise[] = { "/usr/bin/pamixer", "-i", "5", NULL };
static const char *vollower[] = { "/usr/bin/pamixer", "-d", "5", NULL };
static const char *audiomute[] = { "/usr/bin/pamixer", "-t", NULL };
static const char *micmute[] = { "/usr/bin/pamixer", "--source", "easyeffects_source", "-t", NULL };

static const char *lighta[] = { "/usr/bin/light", "-A", "5", NULL };
static const char *lightu[] = { "/usr/bin/light", "-U", "5", NULL };

static const char *playerplay[] = { "/usr/bin/playerctl", "play-pause", NULL };
static const char *playernext[] = { "/usr/bin/playerctl", "next", NULL };
static const char *playerprev[] = { "/usr/bin/playerctl", "previous", NULL };
static const char *playerstop[] = { "/usr/bin/playerctl", "stop", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
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

	{ 0,                            XK_Print,  spawn,          {.v = flameshot } },
	{ MODKEY,                       XK_F1,     spawn,          {.v = blueman } },
	{ MODKEY,                       XK_F2,     spawn,          {.v = telegram } },
	{ MODKEY,                       XK_F3,     spawn,          {.v = spotify } },
	{ MODKEY,                       XK_F4,     spawn,          {.v = firefox } },

	{ 0,                            XF86XK_AudioRaiseVolume,      spawn,          {.v = volraise } },
	{ 0,                            XF86XK_AudioLowerVolume,      spawn,          {.v = vollower } },
	{ 0,                            XF86XK_AudioMute,             spawn,          {.v = audiomute } },
	{ 0,                            XF86XK_AudioMicMute,          spawn,          {.v = micmute } },
	
    { 0,                            XF86XK_MonBrightnessUp,       spawn,          {.v = lighta } },
    { 0,                            XF86XK_MonBrightnessDown,     spawn,          {.v = lightu } },
    
    { 0,                            XF86XK_AudioPlay,             spawn,          {.v = playerplay } },
    { 0,                            XF86XK_AudioNext,             spawn,          {.v = playernext } },
    { 0,                            XF86XK_AudioPrev,             spawn,          {.v = playerprev } },
    { 0,                            XF86XK_AudioStop,             spawn,          {.v = playerstop } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

