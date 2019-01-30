#pragma once
#include "pch.h"

class CKnapsackProblem
{
private:
	int maximalSize;
	int elementsAmount;
	int *sizeTable;
	int *valueTable;
	void initiateTablesByHand();
	void initiateTablesRandomly();

public:
	CKnapsackProblem();
	CKnapsackProblem(int elementsAmount, int maximalSize);
	~CKnapsackProblem();

	int countSolutionValue(bool &genotype);
	int getElementsAmount();
	int getMaximalSize();
	int *getSizeTable();
	int *getValueTable();
};