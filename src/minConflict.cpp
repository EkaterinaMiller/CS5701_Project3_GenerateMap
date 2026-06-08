#include "minConflict.h"
#include <cstdlib>
#include <utility>
#include <iostream>

namespace
{
int at(const std::vector<int>& map, int size, int x, int y)
{
    return map[static_cast<std::size_t>(x * size + y)];
}

int& at(std::vector<int>& map, int size, int x, int y)
{
    return map[static_cast<std::size_t>(x * size + y)];
}
}

std::vector<int> generateMap(int minValue, int maxValue, int size)
{
    std::vector<int> map(static_cast<std::size_t>(size * size), 0);
    // Implement your map generation logic here using the min-conflicts algorithm
    // For demonstration purposes, we'll fill the map with random values between minValue and maxValue
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            at(map, size, i, j) = minValue + rand() % (maxValue - minValue + 1);
        }
    }
    return map;
}
/**
 * @brief Function to count the number of conflicts for a given tile value at position (x, y) in the map. 
 *      A conflict occurs when the newValue differs from its neighbors by more than 1. 
 *      The newValue, could be a curently assigned value or a potential value we want to assign to the tile.
 *      The function checks both orthogonal and diagonal neighbors based on the diagonal flag.
 * 
 * @param map 2D array of intages representing the map, where each integer corresponds to a terrain type.
 * @param x X-coordinate of the tile.
 * @param y Y-coordinate of the tile.
 * @param newValue Potential value to assign to the tile.
 * @param diagonal Flag indicating whether to check diagonal neighbors.
 * @return int Number of conflicts.
 */
int countConflicts(const std::vector<int>& map, int size, int x, int y, int newValue, bool diagonal)
{
    int conflicts = 0;

    // Check the four orthogonal neighbors
    if (x > 0 && abs(at(map, size, x - 1, y) -newValue)>1) conflicts++;
    if (x < size - 1 && abs(at(map, size, x + 1, y) -newValue)>1) conflicts++;
    if (y > 0 && abs(at(map, size, x, y - 1) -newValue)>1) conflicts++;
    if (y < size - 1 && abs(at(map, size, x, y + 1) -newValue)>1) conflicts++;

    // Optionally, check diagonal neighbors if needed
    if (diagonal) {
        if (x > 0 && y > 0 && abs(at(map, size, x - 1, y - 1) -newValue)>1) conflicts++;
        if (x > 0 && y < size - 1 && abs(at(map, size, x - 1, y + 1) -newValue)>1) conflicts++;
        if (x < size - 1 && y > 0 && abs(at(map, size, x + 1, y - 1) -newValue)>1) conflicts++;
        if (x < size - 1 && y < size - 1 && abs(at(map, size, x + 1, y + 1) -newValue)>1) conflicts++;
    }

    return conflicts;
}

bool lowerConflictValue(std::vector<int>& map, int size, int x, int y, int minValue, int maxValue, bool diagonal)
{
    bool madeLower=false;
    int curentValue = at(map, size, x, y);
    int curentConflicts = countConflicts(map, size, x, y, curentValue, diagonal);
    int lowestConflicts = curentConflicts;
    int bestValue = curentValue;

    for (int value = minValue; value <= maxValue; ++value) {
        int conflicts = countConflicts(map, size, x, y, value, diagonal);
            if (conflicts < lowestConflicts) {
                lowestConflicts = conflicts;
                bestValue = value;
                madeLower=true;
        }
    }
    at(map, size, x, y) = bestValue;

    return madeLower;
}
int countTotalConflicts(const std::vector<int>& map, int size, bool diagonal)
{
    int totalConflicts = 0;

    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            totalConflicts += countConflicts(map, size, x, y, at(map, size, x, y), diagonal);
        }
    }

    return totalConflicts;
}

int resolveConflictOnePass(std::vector<int>& map, int size, int minValue, int maxValue, bool diagonal)
{
    int totalConflicts = 0;
    // Find the cells with the highest conflict count.
    int maxConflicts = -1;
    std::vector<std::pair<int, int>> worstCells;

    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            int conflicts = countConflicts(map, size, x, y, at(map, size, x, y), diagonal);
            totalConflicts += conflicts;

            if (conflicts > maxConflicts) {
                //we found a new maximum, remove cels for the old one and add this one.
                maxConflicts = conflicts;
                worstCells.clear();
                worstCells.push_back({x, y});
            } else if (conflicts == maxConflicts && conflicts > 0) {
                worstCells.push_back({x, y});
            }
        }
    }

    if (maxConflicts <= 0 || worstCells.empty()) {
        return totalConflicts; // No conflicts to resolve
    }

    // Go throught the worst cells and try to lower their conflict count for every cell
    //untill we find one that can be improved. If we find one, we return immediately to start a new pass with the updated map.
    for (const auto& [x, y] : worstCells) {
        if (lowerConflictValue(map, size, x, y, minValue, maxValue, diagonal)) {
            return totalConflicts;
        }
    }
//std::cout << "Stuck at " << maxConflicts << " conflicts, trying to perturb the map..." << std::endl;
    // If none of the worst cells can be improved, perturb one of them to escape the local minimum.
    const std::size_t randomIndex = static_cast<std::size_t>(rand()) % worstCells.size();
    const auto& [x, y] = worstCells[randomIndex];
    at(map, size, x, y) = minValue + rand() % (maxValue - minValue + 1);//does not work on diagonals if numTerains >5
    //change its neighbors to the cell value
    makeNeighborValuesSame(map, size, x, y, diagonal);//did not work along. Worsth then just changing the cell value. 
    //but in combination with setting one "bad" cel to the random values, it seems to help escape the local minimum.
    return totalConflicts;
}
void makeNeighborValuesSame(std::vector<int>& map, int size, int x, int y, bool diagonal)
{
    int cellValue = at(map, size, x, y);
    if (x > 0) at(map, size, x - 1, y) = cellValue;
    if (x < size - 1) at(map, size, x + 1, y) = cellValue;
    if (y > 0) at(map, size, x, y - 1) = cellValue;
    if (y < size - 1) at(map, size, x, y + 1) = cellValue;
    if (diagonal) {
        if (x > 0 && y > 0) at(map, size, x - 1, y - 1) = cellValue;
        if (x > 0 && y < size - 1) at(map, size, x - 1, y + 1) = cellValue;
        if (x < size - 1 && y > 0) at(map, size, x + 1, y - 1) = cellValue;
        if (x < size - 1 && y < size - 1) at(map, size, x + 1, y + 1) = cellValue;
    }
}