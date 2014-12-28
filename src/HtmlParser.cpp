/*
 * HtmlParser.cpp
 *
 *  Created on: 2014年12月16日
 *      Author: lfr
 */

#include "HtmlParser.h"

HtmlParser::HtmlParser() {
	// TODO Auto-generated constructor stub

}

HtmlParser::~HtmlParser() {
	// TODO Auto-generated destructor stub
}


/* parse an html page */
void HtmlParser::parseHtml () {
  while ((posParse=strchr(posParse, '<')) != NULL) {
    if (posParse[1] == '!') {
      if (posParse[2] == '-' && posParse[3] == '-') {
        posParse += 4;
        parseComment();
      } else {
        // nothing...
        posParse += 2;
      }
    } else {
      posParse++;
      parseTag();
    }
  }
}

/* skip a comment */
void HtmlParser::parseComment() {
  while ((posParse=strchr(posParse, '-')) != NULL) {
    if (posParse[1] == '-' && posParse[2] == '>') {
      posParse += 3;
      return;
    } else {
      posParse++;
    }
  }
  posParse = buffer+pos;
}

/* macros used by the following functions */
#define skipSpace() \
  while (*posParse == ' ' || *posParse == '\n' \
         || *posParse == '\r' || *posParse == '\t') { \
    posParse++; \
  }
#define skipText() \
  while (*posParse != ' ' && *posParse != '\n' && *posParse != '>' \
         && *posParse != '\r' && *posParse != '\t' && *posParse != 0) { \
    posParse++; \
  }
#define nextWord() skipText(); skipSpace()
#define thisCharIs(i, c) (c == (posParse[i]|32))
#define isTag(t, p, a, i) if (t) { \
      param = p; \
      action = a; \
      posParse += i; \
    } else { \
      posParse++; \
      return; \
    }

/** Try to understand this tag */
void HtmlParser::parseTag () {
  skipSpace();
  char *param=NULL; // what parameter are we looking for
  int action=-1;
  // read the name of the tag
  if (thisCharIs(0, 'a')) { // a href
    param = "href";
    action = LINK;
    posParse++;
  } else if (thisCharIs(0, 'l')) {
    isTag(thisCharIs(1, 'i') && thisCharIs(2, 'n') && thisCharIs(3, 'k'),
          "href", LINK, 4);
  } else if (thisCharIs(0, 'b')) { // base href
    isTag(thisCharIs(1, 'a') && thisCharIs(2, 's') && thisCharIs(3, 'e'),
          "href", BASE, 4);
  } else if (thisCharIs(0, 'f')) { // frame src
    isTag(thisCharIs(1, 'r') && thisCharIs(2, 'a')
          && thisCharIs(3, 'm') && thisCharIs(4, 'e'),
          "src", LINK, 5);
#ifdef IMAGES
  } else if (thisCharIs(0, 'i')) { // img src
    isTag(thisCharIs(1, 'm') && thisCharIs(2, 'g'), "src", LINK, 3);
#endif // IMAGES
  } else {
    return;
  }
  // now find the parameter
  assert(param != NULL);
  skipSpace();
  for (;;) {
    int i=0;
    while (param[i]!=0 && thisCharIs(i, param[i])) i++;
    posParse += i;
    if (posParse[i]=='>' || posParse[i]==0) return;
    if (param[i]==0) {
      parseContent(action);
      return;
    } else {
      // not the good parameter
      nextWord();
    }
  }
}

/** read the content of an interesting tag */
void HtmlParser::parseContent (int action) {
  posParse++;
  while (*posParse==' ' || *posParse=='=') posParse++;
  if (*posParse=='\"' || *posParse=='\'') posParse++;
  area = posParse;
  char *endItem = area + maxUrlSize;
  if (endItem > buffer + pos) endItem = buffer + pos;
  while (posParse < endItem && *posParse!='\"' && *posParse!='\''
         && *posParse!='\n' && *posParse!=' ' && *posParse!='>'
         && *posParse!='\r' && *posParse!='\t' && notCgiChar(*posParse)) {
    if (*posParse == '\\') *posParse = '/';    // Bye Bye DOS !
    posParse++;
  }
  if (posParse == buffer + pos) {
    // end of file => content may be truncated => forget it
    return;
  } else if (posParse < endItem && notCgiChar(*posParse)) {
    // compute this url (not too long and not cgi)
    char oldchar = *posParse;
    *posParse = 0;
    switch (action) {
    case LINK:
      // try to understand this new link
      manageUrl(new url(area, here->getDepth()-1, base), false);
      break;
    case BASE:
      // This page has a BASE HREF tag
      {
        uint end = posParse - area - 1;
        while (end > 7 && area[end] != '/') end--; // 7 because http://
        if (end > 7) { // this base looks good
          end++;
          char tmp = area[end];
          area[end] = 0;
          url *tmpbase = new url(area, 0, (url *) NULL);
          area[end] = tmp;
          delete base;
          if (tmpbase->isValid()) {
            base = tmpbase;
          } else {
            delete tmpbase;
            base = NULL;
          }
        }
      }
      break;
    default: assert(false);
    }
    *posParse = oldchar;
  }
  posParse++;
}
