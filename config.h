/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const unsigned int gappih    = 12;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 12;       /* vert inner gap between windows */
static const unsigned int gappoh    = 12;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 12;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 0;        /* horizontal padding for statusbar */
static const int vertpadbar         = 6;        /* vertical padding for statusbar */
static const char *fonts[]          = { "OpenSans Semi-Bold:size=8" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_lightblue[]   = "#3355ff";
static const char col_black[]       = "#000000";
static const char col_gray5[]       = "#33333f";
static const char col_gray6[]       = "#161616";
static const char col_white[]       = "#ffffff";
static const char col_orange[]      = "#de8642";
static const unsigned int alpha0    = 0x00;
static const unsigned int alpha60   = 0x99;
static const unsigned int alpha80   = 0xCC;
static const unsigned int alphafull = 0xFF;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_black, col_gray2 },
	[SchemeSel]  = { col_white, col_gray6, col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg         bg         border     */
	[SchemeNorm] = { alphafull, alpha60, alphafull },
	[SchemeSel]  = { alphafull, alpha60, alphafull },
};

/* tagging */
static const char *tags[] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 ", " 7 ", " 8 ", " 9 " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,             1,           -1 },
	{ "feh",      NULL,       NULL,       0,            1,             1,           -1 },
	{ "mpv",      NULL,       NULL,       0,            1,             0,           -1 },
	{ "st",       NULL, "st (floating)",  0,            1,             1,           -1 },
	{ "sxiv",     NULL, "sxiv (floating)", 0,           1,             1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[D]",      deck },
	{ "[@]",      spiral },
 	{ "[\\]",     dwindle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "|C|",      centeredmaster },
	{ "TTT",      bstack },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* needed for media keys */
#include "X11/XF86keysym.h"

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_gray5, "-sf", col_lightblue, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *termfloat[]  = { "st", "-t", "st (floating)", NULL };
static const char *bklu[] = { "xbacklight", "-steps", "1", "-time", "0", "-inc", "5", NULL };
static const char *bkld[] = { "xbacklight", "-steps", "1", "-time", "0", "-dec", "5", NULL };
static const char *emacs[] = { "emacsclient", "-c",  NULL };
static const char *file[] = { "pcmanfm", NULL };
static const char *browser[] = { "firefox", NULL };

#include "selfrestart.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_x,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_Return, spawn,          {.v = termfloat } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_n,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_p,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_b,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_f,      setmfact,       {.f = +0.05} },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,       		XK_space,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ShiftMask,       	XK_space,  cyclelayout,    {.i = +1 } },
	{ MODKEY|ControlMask,           XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_F11,    togglefullscreen, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{0,                 XF86XK_AudioLowerVolume,    spawn,     SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5% && pkill -f ~/.local/bin/statusbar.sh && ~/.local/bin/statusbar.sh") },
	{0,                 XF86XK_AudioRaiseVolume,    spawn,     SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5% && pkill -f ~/.local/bin/statusbar.sh && ~/.local/bin/statusbar.sh") },
	{0,                 XF86XK_AudioMute,           spawn,     SHCMD("pactl set-sink-mute @DEFAULT-SINK@ toggle && pkill -f ~/.local/bin/statusbar.sh && ~/.local/bin/statusbar.sh") },
	{0,                 XF86XK_MonBrightnessUp,     spawn,     {.v = bklu } },
	{0,                 XF86XK_MonBrightnessDown,   spawn,     {.v = bkld } },
	{ MODKEY,                       XK_e,      spawn,          {.v = emacs } },
	{ MODKEY,                       XK_m,      spawn,          {.v = file } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = browser } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_r,      self_restart,   {0} },
	{ MODKEY,                       XK_Escape, spawn,          SHCMD("~/.local/bin/power.sh") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        cyclelayout,    {.i = -1 } },
	{ ClkLtSymbol,          0,              Button3,        cyclelayout,    {.i = +1 } },
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

