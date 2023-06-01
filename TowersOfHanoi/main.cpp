#include <iostream>

void find_shortest_solution(int n, char from_rod, char to_rod, char aux_rod) {
    if (n == 0) {
        return;
    }

    find_shortest_solution(n - 1, from_rod, aux_rod, to_rod);
    std::cout << "Move disk " << n << " from rod " << from_rod << " to rod " << to_rod << std::endl;
    find_shortest_solution(n - 1, aux_rod, to_rod, from_rod);
}

// Driver code
int main() {
    int N = 3;

    // A, B and C are names of rods
    find_shortest_solution(N, 'A', 'C', 'B');
    return 0;
}