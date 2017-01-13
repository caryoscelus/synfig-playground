/* === S Y N F I G ========================================================= */
/*!	\file timecurve.h
**	\brief Header file for TimeCurve node
**
**	Time curve is a value node that uses curve in time/value space to
**	interpolate its values.
**
**	\legal
**	Copyright (c) 2016 caryoscelus
**
**	This package is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License as
**	published by the Free Software Foundation; either version 2 of
**	the License, or (at your option) any later version.
**
**	This package is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
**	General Public License for more details.
**	\endlegal
*/

/* === S T A R T =========================================================== */

#ifndef __SYNFIG_VALUENODES_TIMECURVE_H
#define __SYNFIG_VALUENODES_TIMECURVE_H

/* === H E A D E R S ======================================================= */

#include <synfig/valuenode.h>
#include <synfig/localization.h>

#include <2geom/path.h>

#include <memory>

/* === C L A S S E S & S T R U C T S ======================================= */

namespace synfig {
namespace valuenodes {

/**
 * TimeCurve value node: interpolate value in time using curves.
 */
class TimeCurve : public LinkableValueNode
{
public:
	TimeCurve(const ValueBase& value);
	virtual ~TimeCurve() {}

public:
	static bool check_type(Type &type);

public:
	virtual ValueBase operator()(Time time) const;

public:
	virtual String get_name() const;
	virtual String get_local_name() const;

public:
	static TimeCurve* create(const ValueBase &value=ValueBase()) { return new TimeCurve(value); }

protected:
	virtual LinkableValueNode* create_new() const { return new TimeCurve(get_type()); }

	virtual ValueNode::LooseHandle get_link_vfunc(int i) const;
	virtual bool set_link_vfunc(int i,ValueNode::Handle x);
	virtual Vocab get_children_vocab_vfunc() const;

protected:
	void sync_path(Time time) const;

private:
	mutable Geom::Path curve_cached;
	ValueNode::RHandle curve_;

public:
	// temporary public for testing
	Geom::Path const& get_curve(Time time) const;
};

}; // END of namespace valuenodes
}; // END of namespace synfig

/* === E N D =============================================================== */

#endif
