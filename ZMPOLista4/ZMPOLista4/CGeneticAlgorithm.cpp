#include "pch.h"
#include "CGeneticAlgorithm.h"
#include "CIndividual.h"
#include <random>
#include <iostream>
#include <string>

const std::string endMessage = "Najlepszy znaleziony genotyp: ";



CGeneticAlgorithm::CGeneticAlgorithm()
{

}

CGeneticAlgorithm::CGeneticAlgorithm(CKnapsackProblem *knapsackProblem, int populationSize, int iterationAmount, int mutateProb, int crossProb, int eliteSize)
{
	this->knapsackProblem = knapsackProblem;
	this->populationSize = populationSize;
	this->iterationAmount = iterationAmount;
	this->mutateProb = mutateProb;
	this->crossProb = crossProb;
	this->eliteSize = eliteSize;
}

CGeneticAlgorithm::~CGeneticAlgorithm()
{/*
	for (int i = 0; i < polulationSize; i++)
	{
		delete &population[i];
	}

	delete population;*/
}

int CGeneticAlgorithm::getCrossProb()
{
	return crossProb;
}

int CGeneticAlgorithm::getMutateProb()
{
	return mutateProb;
}

void CGeneticAlgorithm::run()
{
	CIndividual **population = new CIndividual*[populationSize];

	std::random_device rd;
	std::mt19937 generatorOfGenotype(rd());
	std::uniform_int_distribution<int> distributionOfGenotype(0, 1);
	for (int i = 0; i < populationSize; i++)
	{
		bool *genotype = new bool[knapsackProblem->getElementsAmount()];
		for (int j = 0; j < knapsackProblem->getElementsAmount(); j++)
		{
			if (distributionOfGenotype(generatorOfGenotype)==1)
			{
				genotype[j] = true;
			}
			else
			{
				genotype[j] = false;
			}
		}
		population[i] = new CIndividual(genotype, this, knapsackProblem);
	}

	/*
	//wypisywanie genotypu naszej populacji
	for (int i = 0; i < populationSize; i++)
	{
		population[i]->printGenotype();
	}*/

	bool *bestGenotype = new bool[knapsackProblem->getElementsAmount()];
	for (int i = 0; i < knapsackProblem->getElementsAmount(); i++)
	{
		bestGenotype[i] = population[0]->getGenotype()[i];
	}
	int bestFitness = population[0]->countFitness();

	for (int i = 1; i < populationSize; i++)
	{
		if (bestFitness<population[i]->countFitness())
		{
			bestFitness = population[i]->countFitness();
			for (int j = 0; j < knapsackProblem->getElementsAmount(); j++)
			{
				bestGenotype[j] = population[i]->getGenotype()[j];
			}
		}
	}

	std::mt19937 generatorOfPopulation(rd());
	std::uniform_int_distribution<int> distributionOfPopulation(0, knapsackProblem->getElementsAmount());

	//selection and crossing
	
	CIndividual **newPopulation = new CIndividual*[populationSize];
	CIndividual **newbornCouple = new CIndividual*[populationSize];

	for (int iterationsDone = 0; iterationsDone < iterationAmount; iterationsDone++)
	{
		//sortowanie populacji w celu znalezienia elity
		for (int i = 0; i < populationSize - 1; i++)
		{
			for (int j = 0; j < populationSize - 1; j++)
			{
				if (population[j]->countFitness() < population[j + 1]->countFitness())
				{
					CIndividual *strongerIndividual = population[j + 1];
					population[j + 1] = population[j];
					population[j] = strongerIndividual;
				}
			}
		}

		for (int i = 0; i < eliteSize; i++)
		{
			newPopulation[i] = population[i];
		}

		for (int newPopulationSize = eliteSize; newPopulationSize < populationSize; newPopulationSize += 2)
		{
			int firstIndividualIndex = distributionOfPopulation(generatorOfPopulation);
			int secondIndividualIndex = distributionOfPopulation(generatorOfPopulation);
			int thirdIndividualIndex = distributionOfPopulation(generatorOfPopulation);
			int fourthIndividualIndex = distributionOfPopulation(generatorOfPopulation);

			if (population[firstIndividualIndex]->countFitness() > population[secondIndividualIndex]->countFitness())
			{
				if (population[thirdIndividualIndex]->countFitness() > population[fourthIndividualIndex]->countFitness())
				{
					newbornCouple = population[firstIndividualIndex]->cross(population[thirdIndividualIndex]);

					newPopulation[newPopulationSize] = newbornCouple[0];
					newPopulation[newPopulationSize + 1] = newbornCouple[1];
				}
				else
				{
					newbornCouple = population[firstIndividualIndex]->cross(population[fourthIndividualIndex]);

					newPopulation[newPopulationSize] = newbornCouple[0];
					newPopulation[newPopulationSize + 1] = newbornCouple[1];
				}
			}
			else
			{
				if (population[thirdIndividualIndex]->countFitness() > population[fourthIndividualIndex]->countFitness())
				{
					newbornCouple = population[secondIndividualIndex]->cross(population[thirdIndividualIndex]);

					newPopulation[newPopulationSize] = newbornCouple[0];
					newPopulation[newPopulationSize + 1] = newbornCouple[1];
				}
				else
				{
					newbornCouple = population[secondIndividualIndex]->cross(population[fourthIndividualIndex]);

					newPopulation[newPopulationSize] = newbornCouple[0];
					newPopulation[newPopulationSize + 1] = newbornCouple[1];
				}
			}
		}

		for (int i = 0; i < populationSize; i++)
		{
			if (bestFitness < newPopulation[i]->countFitness())
			{
				bestFitness = newPopulation[i]->countFitness();
				for (int j = 0; j < knapsackProblem->getElementsAmount(); j++)
				{
					bestGenotype[j] = newPopulation[i]->getGenotype()[j];
				}
			}
			
			if (i < eliteSize)
			{
				population[i] = newPopulation[i];
			}
			else
			{
				delete population[i];
				population[i] = newPopulation[i]->mutate();
			}
		}
		/*
		std::cout << "Wypisywanie genotypu populacji nr:" << iterationsDone << std::endl;
		//wypisywanie genotypu naszej populacji
		for (int i = 0; i < populationSize; i++)
		{
			population[i]->printGenotype();
		}*/
	}

	CIndividual bestIndividual(bestGenotype, this, knapsackProblem);
	std::cout << endMessage;
	bestIndividual.printGenotype();
}