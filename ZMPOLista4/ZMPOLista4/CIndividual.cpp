#include "pch.h"
#include "CIndividual.h"
#include <random>
#include <iostream>
#include <string>

const std::string digitOne = "1";
const std::string digitZero = "0";
const std::string fitnessMessage = "	fitness: ";
const int maximalProbablity = 1000;

CIndividual::CIndividual()
{
}

CIndividual::CIndividual(bool *genotype, CGeneticAlgorithm *geneticAlgorithm, CKnapsackProblem *knapsackProblem)
{
	this->genotype = genotype;
	this->geneticAlgorithm = geneticAlgorithm;
	this->knapsackProblem = knapsackProblem;
}

CIndividual::~CIndividual()
{
	delete genotype;
}

int CIndividual::countFitness()
{
	int fitness = 0;
	int size = 0;

	for (int i=0; i<knapsackProblem->getElementsAmount(); i++)
	{
		if (genotype[i])
		{
			fitness += knapsackProblem->getValueTable()[i];
			size += knapsackProblem->getSizeTable()[i];
		}
	}

	if (size > knapsackProblem->getMaximalSize())
	{
		fitness = 0;
	}
	return fitness;
}

CIndividual *CIndividual::mutate()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(0, maximalProbablity);
	int mutateProbability = geneticAlgorithm->getMutateProb();
	
	if (distribution(generator) < mutateProbability)
	{
		for (int i = 0; i < knapsackProblem->getElementsAmount(); i++)
		{
			if (distribution(generator) < mutateProbability)
			{
				if (genotype[i])
				{
					genotype[i] = false;
				}
				else
				{
					genotype[i] = true;
				}
			}
		}
	}
	return this;
}

CIndividual **CIndividual::cross(CIndividual *otherIndividual)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distributionOfCuttingSpots(0, knapsackProblem->getElementsAmount()-1);
	std::uniform_int_distribution<int> distributionOfCrossProb(0, maximalProbablity);
	int cutIndex = distributionOfCuttingSpots(generator);
	int crossProbability = distributionOfCrossProb(generator);
	bool *firstChildGenotype = new bool[knapsackProblem->getElementsAmount()];
	bool *secondChildGenotype = new bool[knapsackProblem->getElementsAmount()];
	
	if (crossProbability > geneticAlgorithm->getCrossProb())
	{
		for (int i = 0; i < knapsackProblem->getElementsAmount(); i++)
		{
			if (i <= cutIndex)
			{
				firstChildGenotype[i] = genotype[i];
				secondChildGenotype[i] = (*otherIndividual).genotype[i];
			}
			else
			{
				firstChildGenotype[i] = (*otherIndividual).genotype[i];
				secondChildGenotype[i] = genotype[i];
			}
		}
	}
	else
	{
		for (int i = 0; i < knapsackProblem->getElementsAmount(); i++)
		{
			firstChildGenotype[i] = genotype[i];
			secondChildGenotype[i] = (*otherIndividual).genotype[i];
		}
	}
	CIndividual **newbornCouple = new CIndividual*[2];

	newbornCouple[0] = new CIndividual(firstChildGenotype, geneticAlgorithm, knapsackProblem);
	newbornCouple[1] = new CIndividual(secondChildGenotype, geneticAlgorithm, knapsackProblem);

	return newbornCouple;
}

void CIndividual::printGenotype()
{
	for (int i = 0; i < knapsackProblem->getElementsAmount(); i++)
	{
		if (genotype[i])
		{
			std::cout << digitOne;
		}
		else
		{
			std::cout << digitZero;
		}
	}
	std::cout<< fitnessMessage <<countFitness();
	std::cout << std::endl;
}

bool *CIndividual::getGenotype()
{
	return genotype;
}