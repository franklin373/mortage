


/* TrustCenter Utilities */

#ifndef _UTILS_H
#define _UTILS_H 1

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#ifdef __cplusplus
extern "C" {
#endif
  

extern char achStrUpChar  [];

  /**
    Funktion : Liefert zu einem Klein- den zugehörigen Großbuchstaben.
    Ergebnis : Groábuchstabe.
    MT_LEVEL : safe
  */
#define StrUpChar(c)	((char) achStrUpChar [(unsigned char) (c)])

/** liest Werte aus einer Konfigurationdatei
    Aufbau:
     [Sektion]
      Name = Wert

   @param ConfigFilename Name der Konfigurationsdatei
   @param Section        Name des relevanten Abschnittes
   @param FieldName      Name des Feldes
   @param Value          (output) Wert
   @param MaxValueLen    maximale Laenge von Value
   @param NormalizeNames true: convert all string to upper case
   @return
    0: OK
    1 oder 2: ConfgiFilename nicht gefunden
    3: Section nicht gefunden
    4: FieldName nicht gefunden 

   @example
     TCU_GetProfileString("tccrypt.cfg", "email-listener", "req_no_id", buf, 255, 0);
*/
int TCU_GetProfileString( const char *ConfigFilename, const char *Section, const char *FieldName,
                          char *Value, int MaxValueLen, BOOL NormalizeNames );
int TCU_SetProfileString(char szFileName[],char section[],char field[],char value[]);


/** wrapper for strtok_r. 
* Unter Solaris muss das Macro _REENTRANT defininiert sein.
* @param s1 list of token, to be NULL for subsequent calls
* @param s2 string of seperation characters
* @param lastst handle to remaining substring of tokens.
* @return token
*/
char *TC_strtok_r(char* s1, const char* s2, char** lasts);


#ifdef __cplusplus
}
#endif

#endif /* _UTILS_H */

