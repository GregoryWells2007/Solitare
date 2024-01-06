#include "multi2.h"

float get_distance(vector2 v1, vector2 v2) { return sqrt(((v2.x - v1.x) * (v2.x - v1.x)) + ((v2.y - v2.y) * (v2.y - v2.y))); }