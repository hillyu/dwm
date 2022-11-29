/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>


/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 30;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 5;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
    "Fixedsys Excelsior MonoL:size=9",
    "PingFang SC:size=9",
    "FontAwesome:size=9",
    };
static const char dmenufont[]       = "monospace:size=10";
//static const char col_gray1[]       = "#222222";
static const char col_gray1[]       = "#2d303b";
//static const char col_gray2[]       = "#444444";
static const char col_gray2[]       = "#5294e2";
//static const char col_gray3[]       = "#bbbbbb";
static const char col_gray3[]       = "#c4cbd4";
//#7c818c
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#4084d6";
//#268BD2
static const char border[]          = "#1f75fe";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  border },
};

/* tagging */
static const char *tags[] = { "1.", "2.", "3.", "4.", "5.", "6.", "7.", "8.", "9." };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance       title   tags mask  iscentered isfloating   isterminal  noswallow  monitor */
    { "Gimp",         NULL,          NULL,   1 << 6,       1,         1,           0,           0,         -1 },
	{ "imv",          NULL,          NULL,   0,            1,         1,           0,           0,         -1 },
	{ "Nitrogen",     NULL,          NULL,   0,            1,         1,           0,           0,         -1 },
	{ "mpv",          NULL,          NULL,   0,            1,         1,           0,           0,         -1 },
	{ "feh",          NULL,          NULL,   0,            1,         1,           0,           0,         -1 },
	{ "dolphin-emu",  NULL,          NULL,   0,            1,         1,           0,           0,         -1 },
	{ "tabbed",       NULL,          NULL,   0,            0,         1,           0,           0,         -1 },
	{ "Sxiv",         NULL,          NULL,   0,            0,         1,           0,           0,         -1 },
    { NULL,          "ncmpcpp",      NULL,   1 << 8,       0,         1,           0,           0,           0 },
	{ "Sxiv",        "cover",        NULL,   1 << 8,       0,         1,           0,           0,         0 },
	{ NULL,           "owa",         NULL,   1 << 1,       0,         0,           0,           0,         1  },
	{ NULL,           "teams",       NULL,   1 << 1,       0,         0,           0,           0,         1  },
	{ NULL,           "onedrive",    NULL,   1 << 6,       0,         0,           0,           0,         1  },
	{ NULL,           "RapidBoard",  NULL,   1 << 2,       0,         0,           0,           0,         1  },
	{ NULL,           "display",     NULL,   1 << 3,       0,         0,           0,           0,         1  },
    { NULL,           "paper",       NULL,   1 << 3,       0,         0,           0,           0,         1  },
	{ NULL,           "kanbanflow",  NULL,   1 << 2,       0,         0,           0,           0,         1  },
	{ NULL,           "wechat",      NULL,   1 << 7,       1,         1,           0,           0,         1  },
	{ NULL,           "whatsapp",    NULL,   1 << 7,       1,         1,           0,           0,         1  },
    { NULL,    "merriam-webster",    NULL,   0,            1,         1,           0,           0,         -1  },
	{ "Firefox",      NULL,          NULL,   1 << 8,       0,         0,           0,           0,         -1 },
    { NULL,           "douban",      NULL,   1<<8,         1,         1,           0,           0,         0  },
    { "Pavucontrol",  NULL,          NULL,   0,            1,         1,           0,           0,         -1 },
    { "floating",       NULL,          NULL,   0,            1,         1,           1,          0,          -1 },
	{ NULL,           NULL,   "Event Tester",0,            0,         0,           0,          1,           -1 }, /* xev */
	//{ "Rofi",         "rofi",        NULL,   0,            0,         0,           0,          1,           -1 }, [> xev <]
	{ "st",           NULL,          NULL,   0,            0,         0,           1,          0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

//#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
     //{ "[@]",      spiral },
	{ "",      monocle },
     //{ "[\\]",      dwindle },
    { "",      NULL }
};

/* key definitions */
#define MODKEY Mod5Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show", "combi", "-m", "-4", NULL};
static const char *clip[] = { "clipmenu", "-p", "clipboard", NULL};
/* static const char *tmux[]  = { "st", "-c", "floating", "-g", "130x38", "tmux_run.sh", NULL}; */
static const char *tmux[]  = { "alacritty", "--class", "floating", "-e", "tmux_run.sh", NULL};
static const char *termcmd[]  = { "alacritty", NULL};
static const char *snapshot_full[]  = { "flameshot", "full", "-c", "-p", "/home/hill/Pictures/screenshot/" , NULL};
static const char *snapshot[]  = { "flameshot", "gui" , NULL};
static const char *brightness_minus[]  = { "brightness", "1%-" , NULL};
static const char *brightness_plus[]  = { "brightness", "1%+" , NULL};
static const char *volume_down[]  = {"volume", "-5%" , NULL};
static const char *volume_up[]  = {"volume", "+5%" , NULL};
static const char *mute[]  = {"volume", "mute", NULL};
static const char *micmute[]  = {"micmute", NULL, NULL};
static const char *activityMon[]  = {"st", "-c", "floating", "gotop", NULL};
/* static const char *conf[]  = {"st", "-c", "floating", "vim", "/home/hill/src/dwm/config.h", NULL}; */
static const char *conf[]  = {"alacritty", "--class", "floating", "-e", "vim", "/home/hill/src/dwm/config.h", NULL};
static const char *diary[]  = {"st", "-c", "floating", "vim", "-c" ":VimwikiDiaryIndex", NULL};
static const char *arandr[]  = {"autorandr", "-c", NULL};
static const char *syncpackage[]  = {"st_hold", "yay", "-Syu", NULL};
static const char *nnn[]  = {"st", "-g", "150x43", "-c", "floating", "n", NULL};
static const char *errjournal[]  = {"st", "-c", "floating", "journalctl", "-xe", NULL};
static const char *reddit[]  = {"st", "-c", "floating", "rtv", NULL};
static const char *m_prev[]  = {"mpc", "prev", NULL };
static const char *m_play[]  = {"mpc", "toggle", NULL};
static const char *m_next[]  = {"mpc", "next", NULL};
static const char *mail[]  = {"st", "-c", "floating", "neomutt", NULL};



#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ ControlMask,                  XK_space,  spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_t, spawn,          {.v = tmux } },
    { ControlMask|ShiftMask,        XK_3,      spawn,          {.v = snapshot_full } },
    { ControlMask|ShiftMask,        XK_4,      spawn,          {.v = snapshot } },
    { 0,        XF86XK_AudioRaiseVolume,       spawn,          {.v = volume_up } },
    { 0,        XF86XK_AudioLowerVolume,       spawn,          {.v = volume_down } },
    { 0,        XF86XK_AudioMute,              spawn,          {.v = mute } },
    { 0,        XF86XK_AudioPlay,              spawn,          {.v = m_play } },
    { 0,        XF86XK_AudioNext,              spawn,          {.v = m_next } },
    { 0,        XF86XK_AudioPrev,              spawn,          {.v = m_prev } },
    { 0,        XF86XK_AudioMicMute,           spawn,          {.v = micmute } },
    { 0,        XF86XK_MonBrightnessDown,      spawn,          {.v = brightness_minus } },
    { 0,        XF86XK_MonBrightnessUp,        spawn,          {.v = brightness_plus } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_h,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_l,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_u,      setmfact,       {.f = -0.01} },
	{ MODKEY,                       XK_i,      setmfact,       {.f = +0.01} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ ControlMask,                  XK_Tab,    view,           {0} },
	{ ControlMask,                  XK_q,      killclient,     {0} },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|ControlMask,           XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_equal,  incrgaps,       {.i = +2 } },
	{ MODKEY,                       XK_minus,  incrgaps,       {.i = -2 } },
	{ MODKEY|ControlMask,           XK_equal,  incrigaps,      {.i = +2 } },
	{ MODKEY|ControlMask,           XK_minus,  incrigaps,      {.i = -2 } },
	{ MODKEY|ShiftMask,             XK_equal,  incrogaps,      {.i = +2 } },
	{ MODKEY|ShiftMask,             XK_minus,  incrogaps,      {.i = -2 } },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +2 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -2 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +2 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -2 } },
	{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +2 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -2 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +2 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -2 } },
	{ MODKEY,                       XK_e,      cyclelayout,    {.i = +1 } },
    { MODKEY,                       XK_d,      spawn,          {.v = diary } },
    { MODKEY,                       XK_c,      spawn,          {.v = conf } },
    { MODKEY,                       XK_a,      spawn,          {.v = activityMon } },
    { MODKEY,                       XK_x,      spawn,          {.v = errjournal } },
    { MODKEY,                       XK_p,      spawn,          {.v = arandr } },
    { MODKEY,                       XK_r,      spawn,          {.v = reddit } },
    { MODKEY,                       XK_s,      spawn,          {.v = syncpackage } },
    { MODKEY,                       XK_n,      spawn,          {.v = nnn } },
    { MODKEY,                       XK_m,      spawn,          {.v = mail } },
    { MODKEY,                       XK_v,      spawn,          {.v = clip } },
	//{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	//{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_f,      togglefullscr,     {0} },
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
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

