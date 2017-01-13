/* === S Y N F I G ========================================================= */
/*!	\file timecurve.cpp
**	\brief Simple Catch tests of Time Curve node
**
**	\legal
**	Copyright (c) 2016-2017 caryoscelus
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
**	\endlegal
*/

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "../timecurve.h"

#include <synfig/valuenodes/valuenode_dynamiclist.h>
#include <synfig/valuenodes/valuenode_const.h>
#include <synfig/blinepoint.h>

using namespace synfig;
using namespace synfig::valuenodes;

// this is used to get meaningful error messages in Catch REQUIRE
// when dealing with ValueBase
#define TO_DOUBLE(x) x.get(0.0)

TEST_CASE("Time curve value node", "[valuenodes]") {
	Type::initialize_all();
	auto timecurve = TimeCurve::create(ValueBase(0.0));

	SECTION("Zero by default", "[valuenodes]") {
		REQUIRE((*timecurve)(0) == 0.0);
	}
	SECTION("Actual curve", "[valuenodes]") {
		auto list = std::vector<ValueNode*>();

		auto point = BLinePoint();
		point.set_vertex(Point(0, 0));
		point.set_tangent(Point(3, 30));
		list.push_back(ValueNode_Const::create(point));

		point.set_vertex(Point(3, 0));
		point.set_tangent(Point(3, -30));
		list.push_back(ValueNode_Const::create(point));

		point.set_vertex(Point(4, 10));
		list.push_back(ValueNode_Const::create(point));

		auto dlist = ValueNode_DynamicList::create_from_list(std::begin(list), std::end(list));
		timecurve->set_link("path", dlist);
		REQUIRE(TO_DOUBLE((*timecurve)(3)) == 0.0);
		REQUIRE(TO_DOUBLE((*timecurve)(1.5))-7.5 < 1.0/256);
		SECTION("Out of bounds check") {
			REQUIRE(TO_DOUBLE((*timecurve)(10)) == 10.0);
		}
	}
	// TODO: check error handling
}
