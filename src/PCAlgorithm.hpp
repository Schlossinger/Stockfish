//
// Created by Dominik on 05.04.2025.
//

// PCAlgorithm.hpp
#ifndef PCALGORITHM_HPP
#define PCALGORITHM_HPP

#include <vector>
#include <thread>
#include <mutex>

class PCAlgorithm {
public:
    PCAlgorithm(int numPieces = 32, int numSquares = 64);

    // Initializes each piece at its starting square (probability 1.0)
    void initialize(const std::vector<int>& startSquares);

    // Calculates the transition probability for a given move
    double transitionProbability(int piece, int fromSquare, int toSquare, int time);

    // Placeholder: Checks if a move is legal based on piece type
    bool moveIsLegal(int piece, int fromSquare, int toSquare);

    // Placeholder: Returns the number of legal moves for a piece from the given square
    int numberOfLegalMoves(int piece, int fromSquare);

    // Updates the piece probability mass for a move step (time -> time+1)
    void updatePieceMass(int time);

    // Returns current probability distributions
    const std::vector<std::vector<double>>& getProbabilities() const;

private:
    int numPieces;
    int numSquares;
    std::vector<std::vector<double>> P;
    std::mutex mtx;

    // Helper method: updates probability mass for pieces in range [start, end)
    void updatePieceMassRange(int time, int start, int end);
};

#endif // PCALGORITHM_HPP