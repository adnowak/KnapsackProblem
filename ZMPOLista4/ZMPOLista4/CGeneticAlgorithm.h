#pragma once
#include "pch.h"
#include "CKnapsackProblem.h"

class CGeneticAlgorithm
{
private:
	int iterationAmount;
	bool *bestGenotype;

	int eliteSize;
	int populationSize;
	int crossProb;
	int mutateProb;
	CKnapsackProblem *knapsackProblem;
public:
	CGeneticAlgorithm();
	CGeneticAlgorithm(CKnapsackProblem *knapsackProblem, int populationSize, int iterationAmount, int mutateProb, int crossProb, int eliteSize);
	~CGeneticAlgorithm();

	int getCrossProb();
	int getMutateProb();
	void run();
};