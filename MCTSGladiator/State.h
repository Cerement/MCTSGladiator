#pragma once
#include <BWAPI.h>
#include <stdexcept>
#include "Unit.h"
#include "UnitData.h"
#include "Action.h"

namespace MCTSG
{
	class State
	{

		int _time; // current frame count
		Unitset _allUnits;

	public:

		State();
		State(const int t, const BWAPI::Unitset &units);
		~State();

		void clear();
		void set(const int t, const BWAPI::Unitset &units);
		void update(const int t, const BWAPI::Unitset &units);
		void makeMove(const Move move);
		void doAction(const Action &action);

		bool isEnd() const;

		// getters
		int getTimeCount() const { return _time; };
		int getUnitsNum() const { return _allUnits.size(); };
		int getAllyUnitsNum() const;
		int getEnemyUnitsNum() const;
		Unit getUnit(const int ID) const; // get unit (pointer) by ID
		Unitset getUnits() const { return _allUnits; };
		Unitset getAllyUnits() const;
		Unitset getEnemyUnits() const;
	};
}