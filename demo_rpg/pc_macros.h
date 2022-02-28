#pragma once

#define PCCONSTRUCT \
HP = std::make_unique<PointWell>(BASEHP, BASEHP); \
HP->SetMax(BASEHP);\
HP->IncreaseCurrent(BASEHP);\
if (MP) { \
  MP->SetMax(BASEMP); \
  MP->IncreaseCurrent(BASEMP); \
}\
increase_stats(BASESTR, BASEINT, BASEAGI)

#define LEVELUP \
HP->SetMax((welltype)((BASEHP / 2.f) + HP->GetMax()));\
HP->IncreaseCurrent((welltype)(BASEHP / 2.f));\
if (MP) {\
  MP->SetMax((welltype)((BASEMP / 2.f) + MP->GetMax()));\
  MP->IncreaseCurrent((welltype)(BASEMP / 2.f));\
}\
increase_stats((stattype)((BASESTR + 1u) / 2.f), (stattype)((BASEINT + 1u) / 2.f), (stattype)((BASEAGI + 1u) / 2.f))
