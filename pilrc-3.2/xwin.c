
/*
 * @(#)xwin.c
 *
 * Copyright 1997-1999, Wes Cherry   (mailto:wesc@technosis.com)
 *           2000-2003, Aaron Ardiri (mailto:aaron@ardiri.com)
 * All rights reserved.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation;  either version 2, or (at your option)
 * any version.
 *
 * This program is distributed in the hope that it will be useful,  but
 * WITHOUT  ANY  WARRANTY;   without  even   the  implied  warranty  of 
 * MERCHANTABILITY  or FITNESS FOR A  PARTICULAR  PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You  should have  received a  copy of the GNU General Public License
 * along with this program;  if not,  please write to the Free Software 
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Revisions:
 * ==========
 *
 * pre 18-Jun-2000 <numerous developers>
 *                 creation
 *     18-Jun-2000 Aaron Ardiri
 *                 GNU GPL documentation additions
 *     28-Jun-2000 Tom Dyas <tdyas@vger.rutgers.edu>
 *                 Use GtkItemFactory and not the deprecated GtkMenuFactory.
 *                 Add some standard headers so malloc()/free() defined.
 *                 pilrc_reload() return type changed to void since no caller
 *                   actually checks its return value.
 *                 VERSION -> PILRCUI_VERSION to avoid automake's VERSION
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <gtk/gtk.h>

#include "pilrc.h"
#include "restype.h"

#define PILRCUI_VERSION "PilrcUI/X 0.12"

#define PEN_0 0                                  /* NULL, width = 0 */
#define PEN_1 1                                  /* SOLID, width = 1 */
#define PEN_2 2                                  /* SOLID, width = 2 */
#define PEN_3 3                                  /* SOLID, width = 3 */
#define PEN_4 4                                  /* DOTTED, width = 1 */

void pilrcui_open(GtkWidget *,
                  gpointer);
void pilrcui_reload(GtkWidget *,
                    gpointer);
void pilrcui_exit(GtkWidget *,
                  gpointer);
void create_file_selection();
void file_selection_ok(GtkWidget * w,
                       GtkFileSelection * fs);
void destroy_window(GtkWidget * widget,
                    GtkWidget ** window);
void pilrc_reload(char *);

static GtkWidget *pilrcui_menus_init(GtkWidget *);
static void pilrcui_toggle_autoid(GtkWidget * w,
                                  gpointer client_data);
static void pilrcui_toggle_quiet(GtkWidget * w,
                                 gpointer client_data);
static void pilrcui_about_create(GtkWidget * w,
                                 gpointer client_data);
static int pilrcui_about_hide(GtkWidget * w,
                              gpointer client_data);

static char *FileName = NULL;
static RCPFILE *vprcpfile;

static GtkWidget *MainWindow = NULL;
static GtkWidget *FileWindow = NULL;
static GtkWidget *FormArea = NULL;
static GtkWidget *FormMenu = NULL;

/*
 * Second entry is for an accelerator, don't have them yet 
 */
static GtkItemFactoryEntry menu_items[] = {
  {"/_File", NULL, NULL, 0, "<Branch>"},
  {"/File/_Open", "<control>O", pilrcui_open, 0, NULL},
  {"/File/_Reload", "<control>R", pilrcui_reload, 0, NULL},
  {"/File/sep1", NULL, NULL, 0, "<Separator>"},
  {"/File/E_xit", NULL, pilrcui_exit, 0, NULL},
  {"/_Options", NULL, NULL, 0, "<Branch>"},
  {"/Options/_Resize", NULL, NULL, 0, NULL},
  {"/Options/No _AutoID", NULL, pilrcui_toggle_autoid, 0, "<CheckItem>"},
  {"/Options/_Verbose", NULL, pilrcui_toggle_quiet, 0, "<CheckItem>"},
  {"/_Help", NULL, NULL, 0, "<LastBranch>"},
  {"/Help/_About", NULL, pilrcui_about_create, 0, NULL}
};

static int CurrentForm = -1;

void
pilrcui_open(GtkWidget * w,
             gpointer client_data)
{
  if (!FileWindow)
  {
    FileWindow = gtk_file_selection_new("Open File");
    gtk_window_position(GTK_WINDOW(FileWindow), GTK_WIN_POS_MOUSE);
    gtk_signal_connect(GTK_OBJECT(FileWindow), "destroy",
                       (GtkSignalFunc) destroy_window, &FileWindow);

    gtk_signal_connect(GTK_OBJECT
                       (GTK_FILE_SELECTION(FileWindow)->ok_button),
                       "clicked", (GtkSignalFunc) file_selection_ok,
                       FileWindow);

    gtk_signal_connect_object(GTK_OBJECT
                              (GTK_FILE_SELECTION(FileWindow)->
                               cancel_button), "clicked",
                              (GtkSignalFunc) gtk_widget_destroy,
                              GTK_OBJECT(FileWindow));
  }
  if (!GTK_WIDGET_VISIBLE(FileWindow))
    gtk_widget_show(FileWindow);
  else
    gtk_widget_destroy(FileWindow);
}

void
file_selection_ok(GtkWidget * w,
                  GtkFileSelection * fs)
{
  char buf[256];
  char *s;

  if (FileName != NULL)
    free(FileName);
  FileName = strdup(gtk_file_selection_get_filename(GTK_FILE_SELECTION(fs)));
  gtk_widget_destroy(FileWindow);
  FileWindow = NULL;

  if ((s = strrchr(FileName, '/')))
    sprintf(buf, "PILRCUI: ...%s\n", s);
  else
    sprintf(buf, "PILRCUI: %s\n", FileName);
  gtk_window_set_title(GTK_WINDOW(MainWindow), buf);

  pilrc_reload(FileName);
}

void
pilrcui_reload(GtkWidget * w,
               gpointer client_data)
{
  pilrc_reload(FileName);
}

static void
pilrcui_toggle_autoid(GtkWidget * w,
                      gpointer client_data)
{
  vfAutoId = (vfAutoId ? 0 : 1);
}

static void
pilrcui_toggle_quiet(GtkWidget * w,
                     gpointer client_data)
{
  vfQuiet = (vfQuiet ? 0 : 1);
}

#define ptxLeft   0x0000
#define ptxCenter 0x0001
#define ptxInvert 0x0002
#define ptxNoExtent 0x0004
#define ptxCalcWidth 0x0008
#define ptxCalcHeight 0x0010

void
pilrcui_pilot_text(GtkDrawingArea * w,
                   char *s,
                   RCPOINT org,
                   RCRECT * prc,
                   int fontId,
                   int ptx)
{
  int x;
  int y;
  int sy;
  int sx;
  int cch;
  int rgdx[256];
  GdkFont *font;
  GdkGC *gc;

  switch (fontId)
  {
    case 0:
      font =
        gdk_font_load("-Adobe-Helvetica-Medium-R-Normal--*-80-*-*-*-*-*-*");
      break;
    case 1:
      font =
        gdk_font_load("-Adobe-Helvetica-Medium-R-Normal--*-100-*-*-*-*-*-*");
      break;
    case 2:
      font =
        gdk_font_load("-Adobe-Helvetica-Medium-R-Normal--*-120-*-*-*-*-*-*");
      break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
      font =
        gdk_font_load("-Adobe-Helvetica-Medium-R-Normal--*-140-*-*-*-*-*-*");
      break;
    default:
      g_print("pilrcui_pilot_text: Unknown fontId = %d\n", fontId);
      return;
      break;
  }

  cch = strlen(s);

  sx = gdk_string_width(font, s);

  sy = font->ascent;

  x = prc->topLeft.x;
  y = prc->topLeft.y;
  sx = DxCalcRgdx(s, fontId, rgdx);
  if (ptx & ptxCalcWidth)
    prc->extent.x = (short)sx;
  if (ptx & ptxCalcHeight)
    prc->extent.y = (short)sy;
  if (ptx & ptxCenter)
  {
    x += (prc->extent.x - sx + 1) / 2;
    y += (prc->extent.y - sy + 1) / 2;
  }

  /*
   * CLIPPED 
   */
  if (ptx & ptxNoExtent)
  {
    /* nothing */
  }

  /*
   * handle ptxNoExtent 
   */

  if (ptx & ptxInvert)
  {
    gc = GTK_WIDGET(w)->style->white_gc;
    gdk_draw_rectangle(GTK_WIDGET(w)->window,
                       GTK_WIDGET(w)->style->black_gc, TRUE,
                       org.x + prc->topLeft.x, org.y + prc->topLeft.y,
                       prc->extent.x, prc->extent.y);
  }
  else
    gc = GTK_WIDGET(w)->style->black_gc;

  gdk_draw_string(GTK_WIDGET(w)->window, font, gc, org.x + x,
                  org.y + y + font->ascent, s);

  gdk_font_unref(font);
}

void
pilrcui_drawform(GtkDrawingArea * w)
{
  GtkStateType state;
  PLEXFORMOBJLIST *pplt;
  RCFormBA16Type *pform;
  FRM *pfrm;
  int ilt;
  static GdkGC *pens[5] = { NULL, NULL, NULL, NULL, NULL };
  GdkGCValues gcval;
  int pen;
  RCPOINT org;

  state = GTK_STATE_NORMAL;

  /*
   * clear the pixmap: 
   */
  gdk_draw_rectangle(GTK_WIDGET(w)->window, GTK_WIDGET(w)->style->white_gc,
                     TRUE, 0, 0, 160, 160);

  if (CurrentForm == -1)
    return;

  if (pens[0] == NULL)
  {
    gdk_gc_get_values(GTK_WIDGET(w)->style->black_gc, &gcval);
    pens[PEN_0] = gdk_gc_new_with_values(GTK_WIDGET(w)->window, &gcval,
                                         GDK_GC_FOREGROUND |
                                         GDK_GC_BACKGROUND | GDK_GC_FILL);
    gdk_gc_set_line_attributes(pens[PEN_0], 0, GDK_LINE_SOLID, 0, 0);
    pens[PEN_1] = gdk_gc_new_with_values(GTK_WIDGET(w)->window, &gcval,
                                         GDK_GC_FOREGROUND |
                                         GDK_GC_BACKGROUND | GDK_GC_FILL);
    gdk_gc_set_line_attributes(pens[PEN_1], 1, GDK_LINE_SOLID, 0, 0);
    pens[PEN_2] = gdk_gc_new_with_values(GTK_WIDGET(w)->window, &gcval,
                                         GDK_GC_FOREGROUND |
                                         GDK_GC_BACKGROUND | GDK_GC_FILL);
    gdk_gc_set_line_attributes(pens[PEN_2], 2, GDK_LINE_SOLID, 0, 0);
    pens[PEN_3] = gdk_gc_new_with_values(GTK_WIDGET(w)->window, &gcval,
                                         GDK_GC_FOREGROUND |
                                         GDK_GC_BACKGROUND | GDK_GC_FILL);
    gdk_gc_set_line_attributes(pens[PEN_3], 3, GDK_LINE_SOLID, 0, 0);
    pens[PEN_4] = gdk_gc_new_with_values(GTK_WIDGET(w)->window, &gcval,
                                         GDK_GC_FOREGROUND |
                                         GDK_GC_BACKGROUND | GDK_GC_FILL);
    gdk_gc_set_line_attributes(pens[PEN_4], 1, GDK_LINE_ON_OFF_DASH, 0, 0);
  }

  pfrm = (FRM *) PlexGetElementAt(&vprcpfile->plfrm, CurrentForm);

  pform = &pfrm->s16.form;
  pplt = &pfrm->s16.pllt;

  /*
   * Select pen based on pform->window.frameType.width 
   */
  pen = pform->window.frameType.width;
  if (pen)
  {
    if (pform->window.frameType.cornerDiam)
    {
      /*
       * This should be a round rectangle, use square corners for now 
       */
      gdk_gc_set_line_attributes(pens[pen], pen, GDK_LINE_SOLID,
                                 GDK_CAP_ROUND, GDK_JOIN_ROUND);
      gdk_draw_rectangle(GTK_WIDGET(w)->window, pens[pen], FALSE,
                         pform->window.windowBounds.topLeft.x,
                         pform->window.windowBounds.topLeft.y,
                         pform->window.windowBounds.extent.x,
                         pform->window.windowBounds.extent.y);
      /*
       * pform->window.frameType.cornerDiam 
       */
    }
    else
    {
      gdk_draw_rectangle(GTK_WIDGET(w)->window, pens[pen],
                         FALSE, pform->window.windowBounds.topLeft.x,
                         pform->window.windowBounds.topLeft.y,
                         pform->window.windowBounds.extent.x,
                         pform->window.windowBounds.extent.y);
    }
  }

  /*
   * BUG win.c changes the window origin to the inside of the frame, but
   * * I don't think there is something really easy to do that here,
   * * so we add another factor to every x,y coordinate we use below to 
   * * account for the difference.
   */
  org.x =
    pform->window.windowBounds.topLeft.x - pform->window.frameType.width;
  org.y =
    pform->window.windowBounds.topLeft.y - pform->window.frameType.width;
  /*
   * select pen 1 (SOLID, width = 1) 
   */
  pen = PEN_1;
  for (ilt = 0; ilt < pform->numObjects; ilt++)
  {
    RCFORMOBJLIST *plt;
    RCFORMOBJECT *pobj;
    RCFieldBA16Type field;
    RCFormLabelBA16Type label;
    RCRECT rc;
    char *pchText;
    int savepen;

    plt = (RCFORMOBJLIST *) PlexGetElementAt(pplt, ilt);
    pobj = &plt->s16.u.object;
    pchText = NULL;
    switch (plt->s16.objectType)
    {
      case frmFieldObj:
        field = pobj->field->s16;
        if (!field.attr.usable)
          break;
        if (field.attr.underlined)
        {
          int dyStep;

          /*
           * BUG! this is a guess on large font 
           */
          dyStep = field.fontID == 2 ? 14 : 10;

          /*
           * select pen 4 (dotted, width=1) 
           */
          savepen = pen;
          pen = PEN_4;
          if (field.attr.singleLine)
          {
            if (dyStep < field.rect.extent.y)
            {
              gdk_draw_line(GTK_WIDGET(w)->window, pens[pen],
                            org.x + field.rect.topLeft.x,
                            org.y + field.rect.topLeft.y + dyStep,
                            org.x + field.rect.topLeft.x +
                            field.rect.extent.x,
                            org.y + field.rect.topLeft.y + dyStep);
            }
          }
          else
          {
            int dy;

            for (dy = dyStep; dy < field.rect.extent.y; dy += dyStep)
            {
              gdk_draw_line(GTK_WIDGET(w)->window, pens[pen],
                            org.x + field.rect.topLeft.x,
                            org.y + field.rect.topLeft.y + dy,
                            org.x + field.rect.topLeft.x +
                            field.rect.extent.x,
                            org.y + field.rect.topLeft.y + dy);
            }
          }
          pen = savepen;
        }
        break;
      case frmControlObj:
        {
          RCControlBA16Type ctl;

          ctl = pobj->control->s16;
          if (!ctl.attr.usable)
            break;

          pchText = pobj->control->s16.text;
          switch (ctl.style)
          {
            case buttonCtl:
              savepen = pen;
              if (ctl.attr.frame == boldButtonFrame)
                pen = PEN_2;
              /*
               * Again, this isn't a rounded rectangle yet 
               */
              if (ctl.attr.frame != noButtonFrame)
                gdk_draw_rectangle(GTK_WIDGET(w)->window, pens[pen],
                                   FALSE, org.x + ctl.bounds.topLeft.x - 1,
                                   org.y + ctl.bounds.topLeft.y - 1,
                                   ctl.bounds.extent.x, ctl.bounds.extent.y);
              /*
               * corner diam = 7 
               */

              pilrcui_pilot_text(w, pchText, org, &ctl.bounds, ctl.font,
                                 ptxCenter);
              pen = savepen;
              break;
            case selectorTriggerCtl:
              /*
               * select pen 4, dotted width=1 
               */
              /*
               * save old pen to savepen 
               */
              /*
               * savepen = pen; 
               */
              pen = PEN_4;
              /*
               * fall thru 
               */
            case repeatingButtonCtl:
            case pushButtonCtl:
              if (ctl.attr.frame == boldButtonFrame)
                pen = PEN_2;
              /*
               * All frames are current rectangle, should be rounded 
               */
              if (ctl.attr.frame != noButtonFrame)
                gdk_draw_rectangle(GTK_WIDGET(w)->window, pens[pen],
                                   FALSE, org.x + ctl.bounds.topLeft.x,
                                   org.y + ctl.bounds.topLeft.y,
                                   ctl.bounds.extent.x, ctl.bounds.extent.y);

              pilrcui_pilot_text(w, pchText, org, &ctl.bounds, ctl.font,
                                 ptxCenter);

              /*
               * BUG set one then the other?  Copied from win.c 
               */
              /*
               * if (rglt[ilt].objectType == selectorTriggerCtl)
               * pen = savepen;
               */

              pen = PEN_1;
              break;
            case checkboxCtl:
              {
                int y;

#define dxyCheck 8

                y = ctl.bounds.topLeft.y + 2;
                if (ctl.font == 2)
                  y += 2;

                gdk_draw_rectangle(GTK_WIDGET(w)->window, pens[pen],
                                   FALSE, org.x + ctl.bounds.topLeft.x,
                                   org.y + y, dxyCheck, dxyCheck);
                ctl.bounds.topLeft.x += 14;
                ctl.bounds.extent.x -= 14;
                pilrcui_pilot_text(w, pchText, org, &ctl.bounds, ctl.font,
                                   ptxLeft);
                /*
                 * BUG! draw check 
                 */
              }
              break;

            case popupTriggerCtl:
              {
                int x;
                int y;
                int dy;

                x = ctl.bounds.topLeft.x + 3;
                y =
                  ctl.bounds.topLeft.y + (ctl.bounds.extent.y - 4) / 2 +
                  4 - 1;
                /*
                 * Draw down arrow 
                 */
                for (dy = 0; dy < 4; dy++)
                {
                  gdk_draw_rectangle(GTK_WIDGET(w)->window, pens[pen],
                                     TRUE, org.x + x, org.y + y - dy,
                                     dy * 2 + 1, 1);
                  x--;
                }
                ctl.bounds.topLeft.x += 10;
                ctl.bounds.extent.x -= 10;
                /*
                 * BUG! ANCHOR 
                 */
                pilrcui_pilot_text(w, pchText, org, &ctl.bounds, ctl.font,
                                   ptxLeft);
              }
              break;

            default:
              break;
          }
        }
        break;
      case frmListObj:
        {
          RCListBA16Type list;
          RCRECT rc;
          char *s;
          int x;

          list = pobj->list->s16;
          if (!list.attr.usable)
            break;
          gdk_draw_rectangle(GTK_WIDGET(w)->window, pens[pen], FALSE,
                             org.x + list.bounds.topLeft.x - 1,
                             org.y + list.bounds.topLeft.y - 1,
                             list.bounds.extent.x, list.bounds.extent.y);
          rc.topLeft.x = list.bounds.topLeft.x;
          rc.topLeft.y = list.bounds.topLeft.y;
          rc.extent.x = list.bounds.extent.x;
          rc.extent.y = list.bounds.extent.y;

          s = list.itemsText;
          for (x = 0; (x < list.numItems) &&
               (rc.topLeft.y < list.bounds.topLeft.y + list.bounds.extent.y)
               && s; x++)
          {
            /*
             * This should make only the first entry (0) inverted 
             */
            pilrcui_pilot_text(w, s, org, &rc, list.font,
                               (!x ? ptxInvert : 0) | ptxCalcHeight |
                               ptxLeft);
            rc.topLeft.y += rc.extent.y;
            /*
             * Hack: This visible number isn't being stored in RCLIST 
             */
            if (rc.topLeft.y + rc.extent.y >
                list.bounds.topLeft.y + list.bounds.extent.y)
              break;
            s = s + strlen(s) + 1;
          }

          /*
           * list.itemsText = (CharPtr *) IbOut()+cbLt;
           * SwapStruct(&list, "B12L1B12");
           */
        }
        break;
      case frmTableObj:
        {
          /*
           * RCTABLE table; 
           */
        }
        break;
      case frmBitmapObj:
        {
          RCFormBitMapBA16Type bitmap;

          bitmap = pobj->bitmap->s16;
          if (!bitmap.attr.usable)
            break;

        }
        break;
      case frmLineObj:
        break;
      case frmFrameObj:
        break;
      case frmRectangleObj:
        break;
      case frmLabelObj:
        label = pobj->label->s16;
        if (!label.attr.usable)
          break;
        pchText = pobj->label->s16.text;
        rc.topLeft = label.pos;
        pilrcui_pilot_text(w, pchText, org, &rc, label.fontID,
                           ptxLeft | ptxNoExtent);
        break;
      case frmTitleObj:
        {
          RCFORMTITLE title;

          title = *pobj->title;
          pchText = pobj->title->text;
          /*
           * rc = pform->window.windowBounds; 
           */
          rc.topLeft.x = pform->window.frameType.width;
          rc.topLeft.y = pform->window.frameType.width;
          rc.extent.x = pform->window.windowBounds.extent.x;
          rc.extent.y = 12;
          /*
           * dialogFrame 
           */
          if (pform->window.frameType.cornerDiam == 3 &&
              pform->window.frameType.width == 2)
          {
            rc.extent.x -= 1;
            pilrcui_pilot_text(w, pchText, org, &rc, 1,
                               ptxInvert | ptxCenter);
            gdk_draw_line(GTK_WIDGET(w)->window, pens[pen],
                          org.x + rc.topLeft.x,
                          org.y + rc.topLeft.y + rc.extent.y,
                          org.x + rc.topLeft.x + rc.extent.x,
                          org.y + rc.topLeft.y + rc.extent.y);
          }
          else
          {
            RCRECT rcT;

            rcT = rc;
            gdk_draw_rectangle(GTK_WIDGET(w)->window, pens[pen],
                               TRUE, org.x + rc.topLeft.x,
                               org.y + rc.topLeft.y + rc.extent.y,
                               rc.extent.x, 2);
            pilrcui_pilot_text(w, pchText, org, &rcT, 1,
                               ptxInvert | ptxLeft | ptxCalcWidth);
          }
        }
        break;
      case frmPopupObj:
        {
          RCFORMPOPUP popup;

          /*
           * no ui, ez 
           */
          popup = *pobj->popup;
        }
        break;
      case frmGraffitiStateObj:
        {
          RCFORMGRAFFITISTATE grfState;

          grfState = *pobj->grfState;
          rc.topLeft = grfState.pos;
          pilrcui_pilot_text(w, "Caps", org, &rc, 0, ptxLeft | ptxNoExtent);

          pen = PEN_2;
          gdk_draw_line(GTK_WIDGET(w)->window, pens[pen],
                        org.x + grfState.pos.x + 7,
                        org.y + grfState.pos.y + 4,
                        org.x + grfState.pos.x + 11, org.y + grfState.pos.y);

          gdk_draw_line(GTK_WIDGET(w)->window, pens[pen],
                        org.x + grfState.pos.x + 10,
                        org.y + grfState.pos.y,
                        org.x + grfState.pos.x + 14,
                        org.y + grfState.pos.y + 4);

          /*
           * body 
           */
          gdk_draw_line(GTK_WIDGET(w)->window, pens[pen],
                        org.x + grfState.pos.x + 11,
                        org.y + grfState.pos.y,
                        org.x + grfState.pos.x + 11,
                        org.y + grfState.pos.y + 10);

        }
        break;

      case frmGadgetObj:
        {
          RCFORMGADGET gadget;

          gadget = *pobj->gadget;
          if (!gadget.attr.usable)
            break;
        }
        break;

      default:
        g_print("Unknown object\n");
        break;
    }
  }
}

static int
pilrcui_expose(GtkWidget * w,
               GdkEventExpose * event)
{
  pilrcui_drawform(GTK_DRAWING_AREA(w));
  return TRUE;
}

void
pilrcui_form_select(GtkWidget * w,
                    gpointer ifrm)
{
  CurrentForm = (p_int) ifrm;

  pilrcui_drawform(GTK_DRAWING_AREA(FormArea));
}

void
pilrc_reload(char *fn)
{
  char directory[_POSIX_PATH_MAX];
  char cwd[_POSIX_PATH_MAX];
  char *s;
  int ifrm;
  GtkWidget *menu;
  GSList *group = NULL;
  int ifrmMac;

  if ((s = strrchr(fn, '/')))
  {
    *s = '\0';
    strcpy(directory, fn);
    *s = '/';
  }
  else
    strcpy(directory, ".");

  /*
   * Save current directory 
   */
  getcwd(cwd, sizeof(cwd));
  /*
   * chdir (directory); 
   */
  FreeRcpfile(vprcpfile);
  /*
   * vfErr = fFalse; 
   */

  AddAccessPath(directory);

  vprcpfile = ParseFile(fn, directory, NULL, NULL, fontDefault);
  ifrmMac = PlexGetCount(&vprcpfile->plfrm);
  if (CurrentForm == -1)
    CurrentForm = 0;
  if (CurrentForm >= ifrmMac)
    CurrentForm = 0;

  menu = gtk_menu_new();

  for (ifrm = 0; ifrm < ifrmMac; ifrm++)
  {
    char buf[256];
    GtkWidget *menuitem;

    sprintf(buf, "Form %04x",
            (int)((FRM *) PlexGetElementAt(&vprcpfile->plfrm, ifrm))->s16.
            form.formId);
    menuitem = gtk_radio_menu_item_new_with_label(group, buf);
    group = gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(menuitem));
    gtk_signal_connect(GTK_OBJECT(menuitem), "activate",
                       (GtkSignalFunc) pilrcui_form_select,
                       (gpointer) (p_int) ifrm);
    gtk_menu_append(GTK_MENU(menu), menuitem);
    gtk_widget_show(menuitem);
  }
  gtk_option_menu_set_history(GTK_OPTION_MENU(FormMenu), CurrentForm);
  gtk_option_menu_remove_menu(GTK_OPTION_MENU(FormMenu));
  gtk_option_menu_set_menu(GTK_OPTION_MENU(FormMenu), menu);
  pilrcui_drawform(GTK_DRAWING_AREA(FormArea));

  FreeAccessPathsList();
  /*
   * chdir (cwd); 
   */
}

void
destroy_window(GtkWidget * widget,
               GtkWidget ** window)
{
  *window = NULL;
}

void
pilrcui_exit(GtkWidget * widget,
             gpointer client_data)
{
  gtk_exit(0);
}

static GtkWidget *
pilrcui_menus_init(GtkWidget * window)
{
  GtkItemFactory *item_factory;
  GtkAccelGroup *accel_group;
  GtkWidget *menubar;
  int num_menu_items = sizeof(menu_items) / sizeof(menu_items[0]);

  accel_group = gtk_accel_group_new();
  item_factory = gtk_item_factory_new(GTK_TYPE_MENU_BAR,
                                      "<main>", accel_group);

  gtk_item_factory_create_items(item_factory, num_menu_items, menu_items, 0);
  gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);

  menubar = gtk_item_factory_get_widget(item_factory, "<main>");
  return menubar;
}

int
create_main_window()
{
  GtkWidget *menubar;
  GtkWidget *vbox;
  GtkWidget *hbox;
  GtkWidget *other;
  GtkWidget *menuitem;
  GtkWidget *vbox2;

  MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_signal_connect(GTK_OBJECT(MainWindow), "destroy",
                     (GtkSignalFunc) destroy_window, &MainWindow);
  gtk_window_set_title(GTK_WINDOW(MainWindow), "PILRCUI");
  gtk_widget_set_uposition(MainWindow, 20, 20);

  gtk_container_border_width(GTK_CONTAINER(MainWindow), 0);

  vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(MainWindow), vbox);
  gtk_widget_show(vbox);

  menubar = pilrcui_menus_init(MainWindow);
  gtk_box_pack_start(GTK_BOX(vbox), menubar, TRUE, TRUE, 0);
  gtk_widget_show(menubar);

  vbox2 = gtk_vbox_new(FALSE, 0);
  gtk_container_border_width(GTK_CONTAINER(vbox2), 10);
  gtk_box_pack_start(GTK_BOX(vbox), vbox2, TRUE, TRUE, 0);
  gtk_widget_show(vbox2);

  other = gtk_menu_new();
  menuitem = gtk_radio_menu_item_new_with_label(NULL, "none");
  gtk_menu_append(GTK_MENU(other), menuitem);
  gtk_widget_show(menuitem);

  FormMenu = gtk_option_menu_new();
  gtk_option_menu_set_menu(GTK_OPTION_MENU(FormMenu), other);
  gtk_option_menu_set_history(GTK_OPTION_MENU(FormMenu), 0);
  gtk_box_pack_start(GTK_BOX(vbox2), FormMenu, FALSE, TRUE, 0);
  gtk_widget_show(FormMenu);

  other = gtk_hseparator_new();
  gtk_box_pack_start(GTK_BOX(vbox), other, TRUE, TRUE, 0);
  gtk_widget_show(other);

  hbox = gtk_hbox_new(FALSE, 0);
  gtk_container_border_width(GTK_CONTAINER(hbox), 10);
  gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);
  gtk_widget_show(hbox);

  FormArea = gtk_drawing_area_new();
  gtk_signal_connect(GTK_OBJECT(FormArea), "expose_event",
                     (GtkSignalFunc) pilrcui_expose, NULL);
  gtk_drawing_area_size(GTK_DRAWING_AREA(FormArea), 160, 160);
  gtk_widget_set_events(FormArea, GDK_EXPOSURE_MASK);
  gtk_box_pack_start(GTK_BOX(hbox), FormArea, FALSE, FALSE, 0);
  gtk_widget_show(FormArea);
  gtk_widget_realize(FormArea);
  gdk_window_set_background(FormArea->window, &FormArea->style->black);
  if (FileName)
  {
    char *s;
    char buf[_POSIX_PATH_MAX];

    if ((s = strrchr(FileName, '/')))
      sprintf(buf, "PILRCUI: ...%s\n", s);
    else
      sprintf(buf, "PILRCUI: %s\n", FileName);
    gtk_window_set_title(GTK_WINDOW(MainWindow), buf);
    pilrc_reload(FileName);
  }
  else
    pilrcui_drawform(GTK_DRAWING_AREA(FormArea));

  gtk_widget_show(MainWindow);
  return 0;
}

static GtkWidget *about_dialog = NULL;

static void
pilrcui_about_create(GtkWidget * w,
                     gpointer client_data)
{
  GtkStyle *style;
  GtkWidget *vbox;
  GtkWidget *frame;
  GtkWidget *label;
  GtkWidget *alignment;
  gint max_width;

  if (!about_dialog)
  {
    about_dialog = gtk_window_new(GTK_WINDOW_DIALOG);
    gtk_window_set_title(GTK_WINDOW(about_dialog), "About PilrcUI/X");
    gtk_window_set_policy(GTK_WINDOW(about_dialog), FALSE, FALSE, FALSE);
    gtk_window_position(GTK_WINDOW(about_dialog), GTK_WIN_POS_CENTER);
    gtk_signal_connect(GTK_OBJECT(about_dialog), "destroy",
                       (GtkSignalFunc) destroy_window, NULL);
    gtk_signal_connect(GTK_OBJECT(about_dialog), "delete_event",
                       (GtkSignalFunc) destroy_window, NULL);
    gtk_signal_connect(GTK_OBJECT(about_dialog), "button_press_event",
                       (GtkSignalFunc) pilrcui_about_hide, NULL);
    gtk_widget_set_events(about_dialog, GDK_BUTTON_PRESS_MASK);
    /*
     * if (!about_dialog_load_logo (about_dialog))
     * {
     * gtk_widget_destroy (about_dialog);
     * about_dialog = NULL;
     * return;
     * }
     */

    vbox = gtk_vbox_new(FALSE, 1);
    gtk_container_border_width(GTK_CONTAINER(vbox), 3);
    gtk_container_add(GTK_CONTAINER(about_dialog), vbox);
    gtk_widget_show(vbox);

    frame = gtk_frame_new(NULL);
    gtk_container_border_width(GTK_CONTAINER(frame), 3);
    gtk_box_pack_start(GTK_BOX(vbox), frame, TRUE, TRUE, 0);
    gtk_widget_show(frame);

    /*
     * logo_area = gtk_drawing_area_new ();
     * gtk_signal_connect (GTK_OBJECT (logo_area), "expose_event",
     * (GtkSignalFunc) about_dialog_logo_expose, NULL);
     * gtk_drawing_area_size (GTK_DRAWING_AREA (logo_area), logo_width, logo_height);
     * gtk_widget_set_events (logo_area, GDK_EXPOSURE_MASK);
     * gtk_container_add (GTK_CONTAINER (frame), logo_area);
     * gtk_widget_show (logo_area);
     * 
     * gtk_widget_realize (logo_area);
     * gdk_window_set_background (logo_area->window, &logo_area->style->black);
     * gtk_widget_realize (logo_area);
     * gdk_window_set_background (logo_area->window, &logo_area->style->black);
     */

    style = gtk_style_new();
    gdk_font_unref(style->font);
    style->font =
      gdk_font_load("-Adobe-Helvetica-Medium-R-Normal--*-140-*-*-*-*-*-*");
    gtk_widget_push_style(style);

    label = gtk_label_new(PILRCUI_VERSION);
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, TRUE, 0);
    gtk_widget_show(label);

    gtk_widget_pop_style();

    label = gtk_label_new("by");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, TRUE, 0);
    gtk_widget_show(label);

    label = gtk_label_new("Brandon Long (blong@fiction.net)");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, TRUE, 0);
    gtk_widget_show(label);

    label = gtk_label_new("Based on PilrcUI/Win32 by");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, TRUE, 0);
    gtk_widget_show(label);

    label = gtk_label_new("Wes Cherry (wesc@ricochet.net)");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, TRUE, 0);
    gtk_widget_show(label);

    alignment = gtk_alignment_new(0.5, 0.5, 0.0, 0.0);
    gtk_box_pack_start(GTK_BOX(vbox), alignment, FALSE, TRUE, 0);

    gtk_widget_show(alignment);

    /*
     * frame = gtk_frame_new (NULL);
     * gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);
     * gtk_container_border_width (GTK_CONTAINER (frame), 0);
     * gtk_container_add (GTK_CONTAINER (alignment), frame);
     * gtk_widget_show (frame);
     */

    max_width = 0;

  }

  if (!GTK_WIDGET_VISIBLE(about_dialog))
  {
    gtk_widget_show(about_dialog);
  }
}

static int
pilrcui_about_hide(GtkWidget * w,
                   gpointer client_data)
{
  gtk_widget_hide(about_dialog);

  return FALSE;
}

void
usage(char *argv0)
{
  printf("%s  by  Brandon Long (blong@fiction.net)\n", PILRCUI_VERSION);
  printf("\nUsage:\n");
  printf("%s [-v] <filename>\n", argv0);
  printf("\t -v        Version/Usage Information\n");
  printf("\t filename  Optional startup filename\n");

  exit(0);
}

int
main(int argc,
     char *argv[])
{
  int x;

  vfQuiet = TRUE;
  vfAutoId = TRUE;
  vfWinGUI = TRUE;

  gtk_set_locale();

  gtk_init(&argc, &argv);

  for (x = 1; x < argc; x++)
  {
    if (!strcmp(argv[x], "-v") || !strcmp(argv[x], "-h"))
      usage(argv[0]);
    else
    {
      if (FileName)
        free(FileName);
      FileName = strdup(argv[x]);
    }
  }

  /*
   * what is this rc stuff? 
   */
  /*
   * gtk_rc_parse ("filerc"); 
   */

  ResTypeInit();
  CbInit();
  create_main_window();

  gtk_main();

  return 0;
}
