/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */

static const char col_matrix_green[]      = "#00FF41"; //bm4cs
static const char col_matrix_green_dark[] = "#008F11"; //bm4cs
static const char col_matrix_black[]      = "#0D0208"; //bm4cs

/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
    "CaskaydiaCove Nerd Font Mono:pixelsize=10:antialias=true:autohint=true",
    "monospace:size=8"
};

static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
	[SchemeNorm] = { col_matrix_green_dark, col_matrix_black },
	[SchemeSel] = { col_matrix_green, col_matrix_black },
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
