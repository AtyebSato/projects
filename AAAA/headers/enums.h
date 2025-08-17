#ifndef ENUMS_H
#define ENUMS_H

enum class state {inworld, inwave, inmenu, indeath, inloading};
enum class Portaltype {castleport, red};
enum class weapons{pistol,rifle};

extern state currentstate;
extern Portaltype currentPortal;
extern weapons currentweapon;

#endif
