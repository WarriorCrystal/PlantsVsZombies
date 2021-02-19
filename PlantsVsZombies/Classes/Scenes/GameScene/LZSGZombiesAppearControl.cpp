/**
 *Copyright (c) 2020 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.1.28
 *Email: 2117610943@qq.com
 */

#include "LZSGZombiesAppearControl.h"

unsigned int ZombiesAppearControl::zombiesPosition[] = { 130,268,406,544,682 };
unsigned int ZombiesAppearControl::zombiesPositionBigMap[] = { 255,391,527,663,799,935,1071,1207,1343,1479 };

ZombiesAppearControl::ZombiesAppearControl() :
  _zombiesAppearFrequency(0)
, _lastFrequencyZombiesWasDeath(false)
, _isBegin(false)
, _isShowWords(false)
, _time(0)
, _openLevelData(OpenLevelData::getInstance())
{
	_random.seed(time(nullptr));
}

ZombiesAppearControl::~ZombiesAppearControl()
{
}

ZombiesType ZombiesAppearControl::createDifferentTypeZombies(const unsigned int& zombiesAppearFrequency)
{
	int number = rand() % 100;
	int sum = 0, i = -1;
	auto zombiesTypeProbability = _openLevelData->readLevelData(
		_openLevelData->getLevelNumber())->getZombiesTypeProbabilityFrequency().at(zombiesAppearFrequency);
	for (auto& probability : zombiesTypeProbability)
	{
		++i;
		sum += probability;
		if (number < sum)
		{
			return static_cast<ZombiesType>(
				_openLevelData->readLevelData(_openLevelData->getLevelNumber())->getZombiesType().at(i));
		}
	}
	return ZombiesType::None;
}

ZombiesType ZombiesAppearControl::createDifferentTypeZombies()
{
	return ZombiesType();
}

int ZombiesAppearControl::getZombiesNumbersForAppearFrequency(const unsigned int& ZombiesAppearFrequency)
{
	const unsigned int number = _openLevelData->readLevelData(
		_openLevelData->getLevelNumber())->getZombiesNumbers().at(ZombiesAppearFrequency);
	return number + rand() % number;
}

int ZombiesAppearControl::getZombiesAppearFrequency() const
{
	return _zombiesAppearFrequency;
}

bool ZombiesAppearControl::getLastFrequencyZombiesWasDeath() const
{
	return _lastFrequencyZombiesWasDeath;
}

bool ZombiesAppearControl::getIsBegin() const
{
	return _isBegin;
}

bool ZombiesAppearControl::getIsShowWords() const
{
	return _isShowWords;
}

double ZombiesAppearControl::getTime() const
{
	return _time;
}

int ZombiesAppearControl::getEqualProbabilityForRow(int maxRow)
{
	uniform_int_distribution<unsigned>number(0, maxRow);

	if (_judgeZombieRow.size() == maxRow + 1)
	{
		_judgeZombieRow.clear();
	}

	unsigned int row = 0;
	do
	{
		row = number(_random);
	} while (_judgeZombieRow.count(row));

	_judgeZombieRow.insert(row);

	return row;
}

void ZombiesAppearControl::setZombiesAppearFrequency(const unsigned int zombiesAppearFrequency)
{
	_zombiesAppearFrequency = zombiesAppearFrequency;
}

void ZombiesAppearControl::setZombiesAppearFrequency()
{
	++_zombiesAppearFrequency;
}

void ZombiesAppearControl::setLastFrequencyZombiesWasDeath(bool lastFrequencyZombiesWasDeath)
{
	_lastFrequencyZombiesWasDeath = lastFrequencyZombiesWasDeath;
}

void ZombiesAppearControl::setTimeClear()
{
	_time = 0;
}

void ZombiesAppearControl::setTimeAdd()
{
    ++_time;
}

void ZombiesAppearControl::setTimeAdd(const double t)
{
	_time = t;
}

void ZombiesAppearControl::setIsBegin(const bool isBegin)
{
	_isBegin = isBegin;
}

void ZombiesAppearControl::setIsShowWords(const bool isShowWords)
{
	_isShowWords = isShowWords;
}
