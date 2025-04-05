//
// Created by Dominik on 05.04.2025.
//
// PCAlgorithm.cpp
#include "PCAlgorithm.hpp"

PCAlgorithm::PCAlgorithm(int numPieces, int numSquares)
    : numPieces(numPieces), numSquares(numSquares),
      P(numPieces, std::vector<double>(numSquares, 0.0))
{}

void PCAlgorithm::initialize(const std::vector<int>& startSquares) {
    for (int i = 0; i < numPieces; i++) {
        int sq = startSquares[i];
        if (sq >= 0 && sq < numSquares) {
            P[i][sq] = 1.0;
        }
    }
}

double PCAlgorithm::transitionProbability(int piece, int fromSquare, int toSquare, int /*time*/) {
    if (moveIsLegal(piece, fromSquare, toSquare)) {
        int moves = numberOfLegalMoves(piece, fromSquare);
        return (moves > 0) ? 1.0 / moves : 0.0;
    }
    return 0.0;
}

bool PCAlgorithm::moveIsLegal(int /*piece*/, int /*fromSquare*/, int /*toSquare*/) {
    // Insert specific move validation logic here based on piece types
    return true;
}

int PCAlgorithm::numberOfLegalMoves(int /*piece*/, int /*fromSquare*/) {
    // Return the number of legal moves for the piece from the given square
    return 1;
}

void PCAlgorithm::updatePieceMass(int time) {
    const int numThreads = 4;
    int piecesPerThread = numPieces / numThreads;
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; i++) {
        int start = i * piecesPerThread;
        int end = (i == numThreads - 1) ? numPieces : start + piecesPerThread;
        threads.emplace_back(&PCAlgorithm::updatePieceMassRange, this, time, start, end);
    }
    for (auto& t : threads) {
        t.join();
    }
}

void PCAlgorithm::updatePieceMassRange(int time, int start, int end) {
    for (int piece = start; piece < end; piece++) {
        std::vector<double> updatedSquares(numSquares, 0.0);
        for (int toSquare = 0; toSquare < numSquares; toSquare++) {
            double sum = 0.0;
            for (int fromSquare = 0; fromSquare < numSquares; fromSquare++) {
                double prob = P[piece][fromSquare];
                double transProb = transitionProbability(piece, fromSquare, toSquare, time);
                sum += prob * transProb;
            }
            updatedSquares[toSquare] = sum;
        }
        {
            std::lock_guard<std::mutex> lock(mtx);
            P[piece] = updatedSquares;
        }
    }
}

const std::vector<std::vector<double>>& PCAlgorithm::getProbabilities() const {
    return P;
}