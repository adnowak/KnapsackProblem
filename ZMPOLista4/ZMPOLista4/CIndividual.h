#pragma once
#include "pch.h"
#include "CGeneticAlgorithm.h"
#include "CKnapsackProblem.h"

class CIndividual
{
private:
	bool *genotype;
	CGeneticAlgorithm *geneticAlgorithm;
	CKnapsackProblem *knapsackProblem;
public:
	CIndividual();
	CIndividual(bool *genotype, CGeneticAlgorithm *geneticAlgorithm, CKnapsackProblem *knapsackProblem);
	~CIndividual();

	int countFitness();
	CIndividual *mutate();
	CIndividual **cross(CIndividual *otherIndividual);
	void printGenotype();
	bool *getGenotype();
};