#pragma once

#define PCCONSTRUCT \
HP->setMax(BASEHP);\
HP->increaseCurrent(BASEHP);\
if (MP) { \
  MP->setMax(BASEMP); \
  MP->increaseCurrent(BASEMP); \
}\
increaseStats(BASESTR, BASEINT, BASEAGI);

#define LEVELUP \
HP->setMax((welltype)((BASEHP / 2.f) + HP->getMax()));\
HP->increaseCurrent((welltype)(BASEHP / 2.f));\
if (MP) {\
  MP->setMax((welltype)((BASEMP / 2.f) + MP->getMax()));\
  MP->increaseCurrent((welltype)(BASEMP / 2.f));\
}\
increaseStats((stattype)((BASESTR + 1u) / 2.f), (stattype)((BASEINT + 1u) / 2.f), (stattype)((BASEAGI + 1u) / 2.f));
