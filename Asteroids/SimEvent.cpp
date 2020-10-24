#include "SimEvent.h"

SimEvent::SimEvent(EvType eventType) : evType(eventType) {}

SimEvent::SimEvent(EvType eventType, int eventUnitId) : evType(eventType), unitId(eventUnitId){}

SimEvent::SimEvent(EvType eventType, int eventUnitId, int targetUnitId) : evType(eventType), unitId(eventUnitId), targetId(targetUnitId) {}