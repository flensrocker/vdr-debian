/*
 * keys.h: Remote control Key handling
 *
 * See the main source file 'vdr.c' for copyright information and
 * how to reach the author.
 *
 * $Id: keys.h 1.1 2002/09/29 09:55:52 kls Exp $
 */

#ifndef __KEYS_H
#define __KEYS_H

#include "config.h"
#include "tools.h"

enum eKeys { // "Up" and "Down" must be the first two keys!
             kUp,
             kDown,
             kMenu,
             kOk,
             kBack,
             kLeft,
             kRight,
             kRed,
             kGreen,
             kYellow,
             kBlue,
             k0, k1, k2, k3, k4, k5, k6, k7, k8, k9,
             kPower,
             kVolUp,
             kVolDn,
             kMute,
             kNone,
             k_Setup,
             // The following flags are OR'd with the above codes:
             k_Repeat  = 0x8000,
             k_Release = 0x4000,
             k_Flags   = k_Repeat | k_Release,
           };

// This is in preparation for having more key codes:
#define kMarkToggle      k0
#define kMarkMoveBack    k4
#define kMarkMoveForward k6
#define kMarkJumpBack    k7
#define kMarkJumpForward k9
#define kEditCut         k2
#define kEditTest        k8

#define RAWKEY(k)    (eKeys((k) & ~k_Flags))
#define ISRAWKEY(k)  ((k) != kNone && ((k) & k_Flags) == 0)
#define NORMALKEY(k) (eKeys((k) & ~k_Repeat))

struct tKey {
  eKeys type;
  char *name;
  };

class cKey : public cListObject {
private:
  char *remote;
  char *code;
  eKeys key;
public:
  cKey(void);
  cKey(const char *Remote, const char *Code, eKeys Key);
  ~cKey();
  const char *Remote(void) { return remote; }
  const char *Code(void) { return code; }
  eKeys Key(void) { return key; }
  bool Parse(char *s);
  bool Save(FILE *f);
  static eKeys FromString(const char *Name);
  static const char *ToString(eKeys Key);
  };

class cKeys : public cConfig<cKey> {
public:
  bool KnowsRemote(const char *Remote);
  eKeys Get(const char *Remote, const char *Code);
  const char *GetSetup(const char *Remote);
  void PutSetup(const char *Remote, const char *Setup);
  };

extern cKeys Keys;

#endif //__KEYS_H