/* Config file */

/* Appearance */
static const char *fonts[] = {
    "Sans:size=10.5",
    "VL Gothic:size=10.5",
    "WenQuanYi Micro Hei:size=10.5",
};
static const char dmenufont[]       = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*";
static const unsigned int borderpx  = 1;        /* Border pixel of windows */
static const unsigned int snap      = 32;       /* Snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char color_black[]     = "#000000";
static const char color_green[]     = "#228B22";
static const char color_white[]     = "#FFFFFF";
static const char *colors[][3]      = {
	/*               fg           bg            border   */
	[SchemeNorm] = { color_white, color_black,  color_green },
	[SchemeSel]  = { color_green, color_black,  color_green },
};

/* Tagging */
static const char *tags[] = { "Vignemale", "Marboré", "Perdiguère", "Long", "Schrader", "Taillon", "Balaïtous", "Estats", "Munia" };

static const Rule rules[] = {
	/* class          instance    title       tags mask          isfloating    monitor */
	{ "Chromium",     NULL,       NULL,       1 << 1,            False,        -1 },
	{ "MPlayer",      NULL,       NULL,       1 << 4,            False,        -1 },
};

/* Layout */
static const float mfact     = 0.55; /* Factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* Number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* First entry is default */
	{ "[F]",      NULL },    /* No layout function means floating behavior */
	{ "[M]",      monocle },
};

/* Key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* Helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Commands */
static char dmenumon[2] = "0"; /* Component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", color_black, "-nf", color_white, "-sb", color_black, "-sf", color_green, NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char *scrotcmd[]  = { "scrot", "-e", "mv $f ~/image/scrot/", NULL };
static const char *mutecmd[] = { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *kbacklightupcmd[] = { "sbacklight", "+", NULL };
static const char *kbacklightdowncmd[] = { "sbacklight", "-", NULL };
static const char *voldowncmd[] = { "amixer", "-q", "sset", "Master", "3-", "unmute", NULL };
static const char *volupcmd[] = { "amixer", "-q", "sset", "Master", "3+", "unmute", NULL };

static Key keys[] = {
	/* modifier                     key                         function        argument */
    { 0,                            XF86XK_MonBrightnessDown,   spawn,          {.v = kbacklightdowncmd } },
    { 0,                            XF86XK_MonBrightnessUp,     spawn,          {.v = kbacklightupcmd } },
    { 0,                            XF86XK_AudioMute,           spawn,          {.v = mutecmd } },
    { 0,                            XF86XK_AudioLowerVolume,    spawn,          {.v = voldowncmd } },
    { 0,                            XF86XK_AudioRaiseVolume,    spawn,          {.v = volupcmd } },
	{ 0,                            XK_Print,                   spawn,          {.v = scrotcmd } },
	{ MODKEY,                       XK_p,                       spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,                  spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,                       togglebar,      {0} },
	{ MODKEY,                       XK_j,                       focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                       focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                       incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                       incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                       setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                       setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,                  zoom,           {0} },
	{ MODKEY,                       XK_Tab,                     view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,                       killclient,     {0} },
	{ MODKEY,                       XK_t,                       setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                       setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                       setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                   setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                   togglefloating, {0} },
	{ MODKEY,                       XK_agrave,                  view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_agrave,                  tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                  tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_q,                       quit,           {0} },
    { MODKEY|ControlMask,           XK_q,                       halt,           {0} },
    { MODKEY|ControlMask,           XK_r,                       reboot,         {0} },

      TAGKEYS(                      XK_ampersand,                                0)
      TAGKEYS(                      XK_eacute,                                   1)
      TAGKEYS(                      XK_quotedbl,                                 2)
      TAGKEYS(                      XK_apostrophe,                               3)
      TAGKEYS(                      XK_parenleft,                                4)
      TAGKEYS(                      XK_minus,                                    5)
      TAGKEYS(                      XK_egrave,                                   6)
      TAGKEYS(                      XK_underscore,                               7)
      TAGKEYS(                      XK_ccedilla,                                 8)
};

/* Button definitions */
/* Click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

