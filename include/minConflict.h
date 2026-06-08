/**
 * @file minConflict.h
 * @author Ekaterina Miller
 * @brief Functions for generating a map and using the min-conflicts algorithm.
 * @date 2026-06-08
 * 
 */
#ifndef MINCONFLICT_H
#define MINCONFLICT_H   

#include <vector>
std::vector<int> generateMap(int minValue, int maxValue, int size);
int countConflicts(const std::vector<int>& map, int size, int x, int y, int newValue, bool diagonal = false);
bool lowerConflictValue(std::vector<int>& map, int size, int x, int y, int minValue, int maxValue, bool diagonal = false);
int countTotalConflicts(const std::vector<int>& map, int size, bool diagonal = false);
int resolveConflictOnePass(std::vector<int>& map, int size, int minValue, int maxValue, bool diagonal = false);
void makeNeighborValuesSame(std::vector<int>& map, int size, int x, int y, bool diagonal = false);
#endif