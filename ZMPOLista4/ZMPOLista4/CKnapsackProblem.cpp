#include "pch.h"
#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"
#include <iostream>
#include <string>

using namespace std;

const string outOfRangeError = "Blad, wartosc musi byc liczba calkowita, wieksza od zera";
const string giveElementValue = "Podaj wartosc elementu nr:";
const string giveElementSize = "Podaj rozmiar elementu nr:";

CKnapsackProblem::CKnapsackProblem()
{
}

CKnapsackProblem::CKnapsackProblem(int elementsAmount, int maximalSize)
{
	this->elementsAmount = elementsAmount;
	this->maximalSize = maximalSize;

	this->sizeTable = new int[elementsAmount];
	this->valueTable = new int[elementsAmount];

	initiateTablesByHand();
}

void CKnapsackProblem::initiateTablesByHand()
{
	for (int i = 0; i < elementsAmount; i++)
	{
		int elementValue = 0, elementSize = 0;
		do
		{
			if (elementValue != 0)
			{
				cout << outOfRangeError << endl;
			}
			cout << giveElementValue << i << endl;
			cin >> elementValue;
		} while (elementValue <= 0);
		valueTable[i] = elementValue;

		do
		{
			if (elementSize != 0)
			{
				cout << outOfRangeError << endl;
			}
			cout << giveElementSize << i << endl;
			cin >> elementSize;
		} while (elementSize <= 0);
		sizeTable[i] = elementSize;
	}
}

void CKnapsackProblem::initiateTablesRandomly()
{
	for (int i = 0; i < elementsAmount; i++)
	{

	}
}

CKnapsackProblem::~CKnapsackProblem()
{
	delete sizeTable;
	delete valueTable;
}

int CKnapsackProblem::getElementsAmount()
{
	return elementsAmount;
}

int CKnapsackProblem::getMaximalSize()
{
	return maximalSize;
}

int *CKnapsackProblem::getSizeTable()
{
	return sizeTable;
}

int *CKnapsackProblem::getValueTable()
{
	return valueTable;
}

int CKnapsackProblem::countSolutionValue(bool &genotype)
{
	int fitness = 0;
	int size = 0;

	for (int i = 0; i < elementsAmount; i++)
	{
		if ((&genotype)[i])
		{
			fitness += valueTable[i];
			size += sizeTable[i];
		}
	}

	if (size > maximalSize)
	{
		fitness = 0;
	}

	return fitness;
}