/* === S Y N F I G ========================================================= */
/*!	\file skeleton.h
**	\brief Automatic skeleton influence value node
**
**	\legal
**	Copyright (c) 2017 caryoscelus
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

#ifndef __SYNFIG_VALUENODES_LIST_INTERPOLATION
#define __SYNFIG_VALUENODES_LIST_INTERPOLATION

#include <synfig/valuenode.h>

namespace synfig {
namespace valuenodes {

/**
 * Applies skeleton influence to a path.
 */
class SkeletonInfluence : public LinkableValueNode {
public:
	SkeletonInfluence(ValueBase const& value);
	virtual ~SkeletonInfluence() {}

public:
	static bool check_type(Type& type);
	static SkeletonInfluence* create(ValueBase const& value=ValueBase()) { return new SkeletonInfluence(value); }

public:
	virtual ValueBase operator()(Time time) const override;

public:
	virtual String get_name() const override;
	virtual String get_local_name() const override;

protected:
	virtual LinkableValueNode* create_new() const override { return new SkeletonInfluence(get_type()); }

	virtual ValueNode::LooseHandle get_link_vfunc(int i) const override;
	virtual bool set_link_vfunc(int i, ValueNode::Handle value) override;
	virtual Vocab get_children_vocab_vfunc() const override;

private:
	ValueNode::RHandle path_;
	ValueNode::RHandle skeleton_;
}; // END of class SkeletonInfluence

} // END of namespace valuenodes
} // END of namespace synfig

#endif
